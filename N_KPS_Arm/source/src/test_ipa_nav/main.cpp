#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include <Eigen/Core>
#include <Eigen/Geometry>

#include "robot/RobotStruct.h"
#include "mapserver/MapServer.h"
#include "ipa_exploration/msg.hpp"
#include "ipa_exploration/boustrophedon_explorator.h"
//#include <chrono>



class ipa_exploration
{
public:
	ipa_exploration();
	~ipa_exploration(){};
	
	bool init(GridMap* p_grid_map);
	bool init(std::string str_file);
	bool exploreRoom(const SPos &starting_pos);

protected:
private:

	bool gmap2mat( cv::Mat &mt_map , GridMap* p_grid_map );
	bool removeUnconnectedRoomParts(cv::Mat& room_map);
	cv::Mat mat_map_;
	//# Applies a closing operation to neglect inaccessible areas and map errors/artifacts if the map_correction_closing_neighborhood_size parameter is larger than 0.
	//# The parameter then specifies the iterations (or neighborhood size) of that closing operation.
	float map_correction_closing_neighborhood_size_;
	float grid_spacing_in_meter_;
	float coverage_radius_;
	float map_resolution_;
	float grid_obstacle_offset_;
	//# min distance between two points in the created coverage path[pixel]
	float path_eps_;
	//# cell visiting order
	//#   1 = the optimal visiting order of the cells is determined as TSP problem
	//#   2 = alternative ordering from left to right (measured on y-coordinates of the cells), visits the cells in a more obvious fashion to the human observer (though it is not optimal)
	int cell_visiting_order_;
	//min area a boustrophedon cell (i.e. a boustrophedon region of the map) must have to be determined for the path generation
	int min_cell_area_;
	//# maximal allowed shift off the ideal boustrophedon track to both sides for avoiding obstacles on track
	//# setting max_deviation_from_track=grid_spacing is usually a good choice
	//# for negative values (e.g. max_deviation_from_track: -1) max_deviation_from_track is automatically set to grid_spacing
	//# in [pixel]
	int max_deviation_from_track_;

	GridMap* p_grid_map_;
private:

	BoustrophedonExplorer boustrophedon_explorer_;
};


ipa_exploration::ipa_exploration()
{
	p_grid_map_ = 0;
	map_correction_closing_neighborhood_size_ = 5;
	grid_spacing_in_meter_ = 0;
	coverage_radius_= 0;

	grid_obstacle_offset_ = 0.251;
	path_eps_ = 6;

	cell_visiting_order_ = 2;
	min_cell_area_ = 200;

	max_deviation_from_track_ = 0;
}

bool ipa_exploration::init(GridMap* p_grid_map)
{
	map_resolution_ = p_grid_map->Get_resolution();
	p_grid_map_ = p_grid_map;
	mat_map_ = cv::Mat(p_grid_map->Get_grid_height(),p_grid_map->Get_grid_width(), CV_8U);
	
	return gmap2mat(mat_map_,p_grid_map);
}


bool ipa_exploration::init(std::string str_file)
{
	mat_map_ = cv::imread(str_file.c_str(),0);


	int grid_height = mat_map_.size().height;
	int grid_width = mat_map_.size().width;
	for(int gy = 0 ; gy < grid_height; ++gy){
		for(int gx = 0; gx < grid_width; ++gx){

			//#define GRID_IDX( c , x , y ) ( (c) * (y) + (x))
			int index = grid_width*gy + gx;
			//S8 value  = *((S8*)p_grid_map->Get_data() + index);
			S8 value  = mat_map_.at<int8_t>(gy,gx);


			if (value == -1 ){
				mat_map_.at<int8_t>((gy),gx) = 255 ;
			}else if (value == -51 ){
				mat_map_.at<int8_t>((gy),gx) = 0 ;
			}else{
				mat_map_.at<int8_t>((gy),gx) = 0 ;
			}
		}
	}
	cv::namedWindow("ori", 1);
	cv::imshow("ori",mat_map_);

	p_grid_map_ = CREATE_MEM_GMAP("tmp");
	p_grid_map_->map_anchor_.origin_g_x_ = 0 ;
	p_grid_map_->map_anchor_.origin_g_y_ = 0 ;
	p_grid_map_->map_anchor_.origin_x_ = 0;
	p_grid_map_->map_anchor_.origin_y_ = 0;
	p_grid_map_->grid_width_ = mat_map_.size().width;
	p_grid_map_->grid_height_ = mat_map_.size().height;
	p_grid_map_->width_ = p_grid_map_->resolution_*p_grid_map_->grid_width_;
	p_grid_map_->height_ = p_grid_map_->resolution_*p_grid_map_->grid_height_;
	map_resolution_ = 0.05;
	//cv::imwrite("d://ori1.jpg",mat_map_);
	return true;
}

bool ipa_exploration::exploreRoom(const SPos &starting_pos)
{
	U32 gx = 0;
	U32 gy = 0;
	
	p_grid_map_->world2grid(starting_pos.x_,starting_pos.y_,gx,gy);
	const cv::Point starting_position(gx,gy);
	std::cout << "starting point: (" << starting_pos.x_ << ", " << starting_pos.y_ << ") m   (" << starting_position << " px)" << std::endl;

	
	const cv::Point2d map_origin(p_grid_map_->map_anchor_.origin_x_,p_grid_map_->map_anchor_.origin_y_);

	// ***************** I. read the given parameters out of the goal *****************
	// todo: this is only correct if the map is not rotated

	coverage_radius_ = 0.6;

 	cv::Mat element = getStructuringElement(cv::MORPH_ELLIPSE,cv::Size(5, 5));
 	//开运算，去除小白点
 	cv::morphologyEx(mat_map_, mat_map_, cv::MORPH_OPEN,element);
 	cv::namedWindow("open", cv::WINDOW_NORMAL);
 	cv::imshow("open",mat_map_);

	element = getStructuringElement(cv::MORPH_ELLIPSE,cv::Size(2, 2));
	//闭运算，去除小黑点
	cv::morphologyEx(mat_map_, mat_map_, cv::MORPH_CLOSE,element);
	cv::namedWindow("close", cv::WINDOW_NORMAL);
	cv::imshow("close",mat_map_);

	//cv::waitKey(3000);

	const bool room_not_empty = removeUnconnectedRoomParts(mat_map_);
	if (room_not_empty == false)
	{
		std::cout<<"room to small!!"<<std::endl;
		return false;
	}


	grid_spacing_in_meter_ = coverage_radius_*std::sqrt(2.0);


	const double grid_spacing_in_pixel = grid_spacing_in_meter_ / map_resolution_;		// is the square grid cell side length that fits into the circle with the robot's coverage radius or fov coverage radius, multiply with sqrt(2) to receive the whole working width
	std::cout << "grid size: " << grid_spacing_in_meter_ << " m   (" << grid_spacing_in_pixel << " px)" << std::endl;

	// ***************** II. plan the path using the wanted planner *****************
	// todo: consider option to provide the inflated map or the robot radius to the functions instead of inflating with half cell size there
	Eigen::Matrix<float, 2, 1> zero_vector;
	zero_vector << 0, 0;
	std::vector<geometry_msgs::Pose2D> exploration_path;
	boustrophedon_explorer_.getExplorationPath(mat_map_, exploration_path, map_resolution_, starting_position, map_origin, grid_spacing_in_pixel, grid_obstacle_offset_, path_eps_, cell_visiting_order_, true, zero_vector, min_cell_area_, max_deviation_from_track_);


	// display finally planned path
	if ( 1 )
	{
		U32 gx = 0;
		U32 gy = 0;
		std::cout << "printing path" << std::endl;
		cv::Mat fov_path_map;
		for(size_t step=1; step<exploration_path.size(); ++step)
		{
			fov_path_map = mat_map_.clone();
			cv::resize(fov_path_map, fov_path_map, cv::Size(), 2, 2, cv::INTER_LINEAR);
			if (exploration_path.size() > 0){
				p_grid_map_->world2grid(exploration_path[0].x,exploration_path[0].y,gx,gy);
				//cv::circle(fov_path_map, 2*cv::Point((exploration_path[0].x-map_origin.x)/map_resolution, (exploration_path[0].y-map_origin.y)/map_resolution), 2, cv::Scalar(150), CV_FILLED);
				cv::circle(fov_path_map, 2*cv::Point(gx,gy), 2, cv::Scalar(150), CV_FILLED);
			}
			for(size_t i=1; i<=step; ++i)
			{
				p_grid_map_->world2grid(exploration_path[i-1].x,exploration_path[i-1].y,gx,gy);
				cv::Point p1(gx, gy);
				p_grid_map_->world2grid(exploration_path[i].x,exploration_path[i].y,gx,gy);
				cv::Point p2(gx,gy);
				cv::circle(fov_path_map, 2*p2, 2, cv::Scalar(200), CV_FILLED);
				cv::line(fov_path_map, 2*p1, 2*p2, cv::Scalar(150), 1);
				cv::Point p3(p2.x+5*cos(exploration_path[i].theta), p2.y+5*sin(exploration_path[i].theta));
				if (i==step)
				{
					cv::circle(fov_path_map, 2*p2, 2, cv::Scalar(80), CV_FILLED);
					cv::line(fov_path_map, 2*p1, 2*p2, cv::Scalar(150), 1);
					cv::line(fov_path_map, 2*p2, 2*p3, cv::Scalar(50), 1);
				}
			}
			//			cv::imshow("cell path", fov_path_map);
			//			cv::waitKey();
		}
		cv::imshow("cell path", fov_path_map);
		cv::waitKey();
	}
}


bool ipa_exploration::gmap2mat(cv::Mat &mt_map , GridMap* p_grid_map)
{
	mt_map = cv::Mat(p_grid_map->Get_grid_height(), p_grid_map->Get_grid_width(), CV_8U);
	
	int grid_height = p_grid_map->Get_grid_height();
	int grid_width = p_grid_map->Get_grid_width();
	for(int gy = 0 ; gy < grid_height; ++gy){
		for(int gx = 0; gx < grid_width; ++gx){
		
			//#define GRID_IDX( c , x , y ) ( (c) * (y) + (x))
			int index = grid_width*gy + gx;
			S8 value  = *((S8*)p_grid_map->Get_data() + index);
			if (value == MAP_EMPTY){
				mt_map.at<int8_t>((grid_height - gy -1),gx) = 255 ;
			}else{
				mt_map.at<int8_t>((grid_height - gy -1),gx) = 0 ;
			}
		}
	}
	//cv::imwrite("d://ori1.jpg",mat_map_);
	return true;

}

bool ipa_exploration::removeUnconnectedRoomParts(cv::Mat& room_map)
{
	// create new map with segments labeled by increasing labels from 1,2,3,...
	cv::Mat room_map_int(room_map.rows, room_map.cols, CV_32SC1);
	for (int v=0; v<room_map.rows; ++v)
	{
		for (int u=0; u<room_map.cols; ++u)
		{
			if (room_map.at<uchar>(v,u) == 255)
				room_map_int.at<int32_t>(v,u) = -100;
			else
				room_map_int.at<int32_t>(v,u) = 0;
		}
	}
	

	std::map<int, int> area_to_label_map;	// maps area=number of segment pixels (keys) to the respective label (value)
	int label = 1;
	for (int v=0; v<room_map_int.rows; ++v)
	{
		for (int u=0; u<room_map_int.cols; ++u)
		{
			if (room_map_int.at<int32_t>(v,u) == -100)
			{
				const int area = cv::floodFill(room_map_int, cv::Point(u,v), cv::Scalar(label), 0, 0, 0, 8 | cv::FLOODFILL_FIXED_RANGE);
				area_to_label_map[area] = label;
				++label;
			}
		}
	}
	// abort if area_to_label_map.size() is empty
	if (area_to_label_map.size() == 0)
		return false;

	// remove all room pixels from room_map which are not accessible
	const int label_of_biggest_room = area_to_label_map.rbegin()->second;
	std::cout << "label_of_biggest_room=" << label_of_biggest_room << std::endl;
	for (int v=0; v<room_map.rows; ++v)
		for (int u=0; u<room_map.cols; ++u)
			if (room_map_int.at<int32_t>(v,u) != label_of_biggest_room)
				room_map.at<uchar>(v,u) = 0;

	//cv::imwrite("d://area3.jpg",room_map_int);
	//cv::imwrite("d://work4.jpg",room_map);
	return true;
}

int main ( int argc, char** argv )
{
	//GridMap* p_grid_map = MAP_SERVER.LoadPgmMap("d://407.pgm",map_data_base::MEM,"");

	ipa_exploration ipa_exp;
	//ipa_exp.init(p_grid_map);
	ipa_exp.init("d://408.pgm");
	SPos starting_pos;
	starting_pos.x_ = 20;
	starting_pos.y_ = 10;
	starting_pos.th_ = 0;
	ipa_exp.exploreRoom(starting_pos);

}
   
#if 0
	cv::Mat element = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));   //针对高亮部分
	erode(mat_map_, mat_map_, element);
	cv::imshow("腐蚀", mat_map_);
	cv::waitKey(3000);

	int size = 5;
	// 提取连通区域，并剔除小面积联通区域
	std::vector<std::vector<cv::Point>> contours;           //二值图像轮廓的容器
	std::vector<cv::Vec4i> hierarchy;                  //4个int向量，分别表示后、前、父、子的索引编号
	cv::findContours(mat_map_, contours, hierarchy,cv::RETR_LIST, cv::CHAIN_APPROX_NONE);             //检测所有轮廓
	//contours.erase(remove_if(contours.begin(), contours.end(),[](const vector<Point>& c) {return contourArea(c) < 800; }), contours.end());  //vector.erase 删除元素
	// 显示图像并保存
	/*imgHSVMask.setTo(0);
	drawContours(imgHSVMask, contours, -1, Scalar(255), FILLED);
	imshow("处理图", imgHSVMask); */
 
	cv::Mat ImageContours = cv::Mat::zeros(mat_map_.size(), CV_8UC1);  //绘制
	cv::Mat ImgContours= cv::Mat::zeros(mat_map_.size(), CV_8UC1);
 
	std::vector<std::vector<cv::Point>>::iterator k;                    //迭代器，访问容器数据
 
	for (k = contours.begin(); k != contours.end();)      //遍历容器,设置面积因子
	{
		if (cv::contourArea(*k, false) < size)
		{//删除指定元素，返回指向删除元素下一个元素位置的迭代器
			k = contours.erase(k);
		}
		else
			++k;
	}
 
	//contours[i]代表第i个轮廓，contours[i].size()代表第i个轮廓上所有的像素点
	for (int i = 0; i < contours.size(); i++)
	{
		for (int j = 0; j < contours[i].size(); j++)
		{
			if (cv::contourArea(contours[i]) > 20){
				//获取轮廓上点的坐标
				cv::Point P = cv::Point(contours[i][j].x, contours[i][j].y);
				ImgContours.at<uchar>(P) = 255;
			}
			
		}
		drawContours(ImageContours, contours,i, cv::Scalar(255), -1, 8);
	}

	cv::imshow("轮廓", ImageContours);
	cv::imshow("轮廓点集合", ImgContours);
	cv::waitKey(3000);


	cv::Mat temp;
	cv::erode(mat_map_, temp, cv::Mat(), cv::Point(-1, -1), map_correction_closing_neighborhood_size_);
	cv::dilate(temp, mat_map_, cv::Mat(), cv::Point(-1, -1), map_correction_closing_neighborhood_size_);
	cv::namedWindow("mat", 1);
	cv::imshow("mat",mat_map_);
	cv::waitKey(3000);
#endif