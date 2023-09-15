#include <fstream>
#include <string.h>

#include "Comm/Comm.h"
#include "Geometry.h"

#include "tf_2d_server.h"

#include "polygon_ex.h"

//#define POLYGON_DEBUG 1

polygon_ex::polygon_ex()
{

}

polygon_ex::~polygon_ex()
{

}

/*void polygon_ex::init(F32 fangle,F32 fdis)
{


	clean();

	F32 tmp = 0;
	F32 tmp2 = fdis*sin(Deg2Rad(fangle));
	
	//std::ofstream of("polygen.txt",std::ios::out);
	for( int i = 0 ; i < POLYGON_COUNT ; ++i){
		tmp = POLYGON_ANGLE_START + POLYGON_ANGLE_DIFF*i;

		if(fabs(tmp) < fangle){
			angle_list_[i] = tmp;
			range_list_[i] = fdis;
		}else{
			angle_list_[i] = tmp;
			range_list_[i] = fabs(tmp2 / sin(Deg2Rad(tmp))) ;
		}
		VecPosition vp(range_list_[i],angle_list_[i],POLAR);
		//of<<"vp x:"<<vp.getX()<<" y:"<<vp.getY()<<std::endl;
	}
 	//of.flush();
 	//of.close();
}
*/
void polygon_ex::init_shape( const std::string &str_shape ){

	std::vector<Sxy> shape;

	std::vector<std::string> vres;
	cComm::SplitString(str_shape,";",vres);
	std::vector<std::string>::iterator it = vres.begin();
	for ( ; it !=  vres.end() ; ++it)
	{
		std::string str = *it;
		std::vector<std::string> vpos;
		cComm::SplitString(str,",",vpos);

		if (vpos.size() > 1)
		{
			Sxy xy;
			cComm::ConvertToNum(xy.x_,vpos[0]);
			cComm::ConvertToNum(xy.y_,vpos[1]);
			shape.push_back(xy);
		}
	}
	init_shape(shape);
}
void polygon_ex::init_shape( const std::vector<Sxy> &shape )
{
	std::cout<<"begin init polygon para pos size:"<<shape.size()<<std::endl;
	if (shape.size() < 4)
	{
		Sxy xy;
		xy.x_ = 0.5;
		xy.y_ = 0.4;
		shape_list_.push_back(xy);

		xy.x_ = -0.3;
		xy.y_ = 0.4;
		shape_list_.push_back(xy);

		xy.x_ = -0.3;
		xy.y_ = -0.4;
		shape_list_.push_back(xy);

		xy.x_ = 0.5;
		xy.y_ = -0.4;
		shape_list_.push_back(xy);

		xy.x_ = 0.5;
		xy.y_ = 0.4;
		shape_list_.push_back(xy);
	}else
	{
		shape_list_ = shape;
	}
	
	std::vector<Sxy> shape_new;

	//recalculate the shape
	//1 find robot head in which shape range
	//2 redefine the shape_list,make sure the robot head is the first shape point
	//  find robot head ray line intersection with the shape range
	//  add first shape point to the list 
	//  add last shape point to the list

	std::vector<Sxy>::iterator it1 = shape_list_.begin();
	std::vector<Sxy>::iterator it2 = shape_list_.begin();
	it2++;

	VecPosition vhead(1.0,0);
	bool b_find_line = false;
	for ( ; it2 != shape_list_.end() ;  )
	{
		VecPosition v1(it1->x_,it1->y_);
		VecPosition v2(it2->x_,it2->y_);

		F32 a1 = VecPosition::IntersectionAngle(v1,vhead);
		F32 a2 = VecPosition::IntersectionAngle(v2,vhead);

		std::cout<<"x1:"<<it1->x_<<"y1:"<<it1->y_<<std::endl;
		std::cout<<"x2:"<<it2->x_<<"y2:"<<it2->y_<<std::endl;
		std::cout<<"a1:"<<a1<<" a2:"<<a2<<std::endl;
	
		if (  (a1 < 0) && (a2 > 0))
		{

			b_find_line = true;
			break;
			
		}

		it1++;
		it2++;
	}
	if (!b_find_line)
	{
		std::cout<<"shape define err!"<<std::endl;
		return;
	}
	VecPosition vl1(it1->x_,it1->y_);
	VecPosition vl2(it2->x_,it2->y_);
	Line ln1 = Line::makeLineFromTwoPoints(vl1,vl2);
	Line ln2 = Line::makeLineFromPositionAndAngle(VecPosition(0,0),0);
	VecPosition line_line_intersection(0,0);
	ln1.getIntersection(ln2,line_line_intersection);
	Sxy llint;
	llint.x_ = line_line_intersection.getX();
	llint.y_ = line_line_intersection.getY();
		 
	shape_new.push_back(llint);
	for (  ; it2 != shape_list_.end(); ++it2 )
	{
		shape_new.push_back(*it2);
	}
	for ( it2 = shape_list_.begin(); it2 != it1;  )
	{
		++it2;
		shape_new.push_back(*it2);
	}
	shape_new.push_back(llint);

	shape_list_ = shape_new;

	it1 = shape_list_.begin();
	for ( ; it1 != shape_list_.end() ; ++it1 )
	{
		std::cout<<"init shape list x:"<<it1->x_<<" y:"<<it1->y_<<std::endl;
	}

	//create_angle_range();
	
}

void polygon_ex::get_range(SLaser_Ex &min_range,F32 dx,F32 dy){
	std::cout<<"get range begin!"<<std::endl;
	//clear all data
	memset(min_range.data_,0,sizeof(F32)*LASER_COUNT_EX);
	memset(min_range.intensities_,0,sizeof(U32)*LASER_COUNT_EX);
	memset(min_range.seg_,0,sizeof(U8)*LASER_COUNT_EX);
	//set base laser to base odom
	TF_SERVER.set_base_laser_in_base_link(dx,dy,0);

	print_shape();

	//1 transfer shape list to laser base
	//2 find every ray of laser beems intersection to the shape
	std::vector<Sxy> shape_laser_;
	std::vector<Sxy>::iterator it = shape_list_.begin();
	for ( ; it != shape_list_.end();  ++it)
	{
		VecPosition v(it->x_,it->y_);
		TF_SERVER.tf_base_link_to_base_laser(v);
		Sxy xy;
		xy.x_ = v.getX();
		xy.y_ = v.getY();
		shape_laser_.push_back(xy);
	}

	shape_list_ = shape_laser_;

	print_shape();
	
#ifdef POLYGON_DEBUG
	std::ofstream of("polygen_dx.txt",std::ios::out);
#endif

	assert(min_range.used_ray_ <= LASER_COUNT_EX);

	F32 start_a = Rad2Deg(min_range.start_angle_);
	F32 diff_a = Rad2Deg(min_range.resolution_);
	F32 angle = 0 ;
	for ( int i = 0 ; i < min_range.used_ray_ ; ++i )
	{
		angle = start_a + diff_a*i;

		VecPosition ray(1.0,angle,POLAR);
		
		Line seg_line;
		Line ray_line = Line::makeLineFromPositionAndAngle(VecPosition(0,0),ray.getDirection());

		if (getCrossLine2(seg_line,ray))
		{
			VecPosition intersection;
			ray_line.getIntersection(seg_line,intersection);
			min_range.data_[i] = intersection.getMagnitude();
			min_range.seg_[i] = 255;
#ifdef POLYGON_DEBUG
			of<<"vp x y:"<<intersection.getX()<<" "<<intersection.getY()<<std::endl;
#endif
		}
	}

	//fix err
	F32 last_range = 0;
 	for( int i = 0 ; i < min_range.used_ray_ ; ++i){

 		if( fabs(min_range.data_[i]) < 1e-6){
 			min_range.data_[i] = last_range;
			min_range.seg_[i] = 254;
 		}
		if ( min_range.data_[i] < min_range.range_min_){

			F32 angle  = angle = start_a + diff_a*i;

			//std::cout<<"err filter:"<<angle<<"range:"<<min_range.data_[i]<<std::endl;

			min_range.data_[i] = min_range.range_min_;
			min_range.seg_[i] = 253;
		}
		last_range = min_range.data_[i];
	}

#ifdef POLYGON_DEBUG
 	of.flush();
 	of.close();
#endif

 	std::cout<<"get range ex end!"<<std::endl;
}

void polygon_ex::clean()
{
	memset(angle_list_,0,sizeof(F32)*POLYGON_EX_COUNT);
	memset(range_list_,0,sizeof(F32)*POLYGON_EX_COUNT);
}
bool polygon_ex::getCrossLine(Line &ln,VecPosition ray,std::vector<Sxy>::iterator &seg_end){
	
	if (seg_end == shape_list_.end())
	{
		return false;
	}
	VecPosition vend(seg_end->x_,seg_end->y_);
	F64 angle = VecPosition::IntersectionAngle(vend,ray);
	//if current ray is in next segment
	if (angle < 0)
	{
		seg_end++;
	}
	std::vector<Sxy>::iterator seg_begin = seg_end;
	seg_begin--;
	if ( (seg_begin == shape_list_.end()) || (seg_end == shape_list_.end()))
	{
		return false;
	}
	VecPosition vbegin(seg_begin->x_,seg_begin->y_);
	vend = VecPosition(seg_end->x_,seg_end->y_);

	ln = Line::makeLineFromTwoPoints(vbegin,vend);

	return true;
}
bool polygon_ex::find_ray_in_seg(std::vector<Sxy>::iterator &it_begin,std::vector<Sxy>::iterator &it_end,const VecPosition& ray){

	it_begin = shape_list_.begin();
	it_end = shape_list_.begin();
	it_end++;

	for ( ; it_end != shape_list_.end(); ++it_end)
	{
		VecPosition v1(it_begin->x_,it_begin->y_);
		VecPosition v2(it_end->x_,it_end->y_);

		F32 a1 = VecPosition::IntersectionAngle(v1,ray);
		F32 a2 = VecPosition::IntersectionAngle(v2,ray);


		if (  (a1 < 0) && (a2 > 0))
		{
			return true;
		}
		it_begin++;
	}
	return false;
}
bool polygon_ex::getCrossLine2( Line &ln,VecPosition ray )
{
	std::vector<Sxy>::iterator seg_begin = shape_list_.end();
	std::vector<Sxy>::iterator seg_end = shape_list_.end();
	
	if (find_ray_in_seg(seg_begin,seg_end,ray))
	{
		VecPosition vb(seg_begin->x_,seg_begin->y_);
		VecPosition ve(seg_end->x_,seg_end->y_);
		ln = Line::makeLineFromTwoPoints(vb,ve);
		return true;
	}
	
	return false;
}

void polygon_ex::print_shape()
{
	std::cout<<"print_shape"<<std::endl;
	std::vector<Sxy>::iterator it = shape_list_.begin();
	for ( ; it != shape_list_.end();  ++it)
	{
		std::cout<<"shape x y:"<<it->x_<<" "<<it->y_<<std::endl;
	}
}

