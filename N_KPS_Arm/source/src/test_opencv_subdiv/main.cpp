
#include <opencv2/opencv.hpp>  
//#include <opencv2/xfeatures2d/nonfree.hpp>  
#include <opencv2/imgproc.hpp>

#include <atlstr.h> // use STL string instead, although not as convenient...
#include <atltrace.h>
#include <iostream>
#include <fstream>
#include <string>
#include<time.h>

using namespace std;
using namespace cv;

#if 0
/*
pts��Ҫ�ʷֵ�ɢ�㼯,in
img,�ʷֵĻ���,in
tri,�洢������ʾ����任������,out
*/

// used for doing delaunay trianglation with opencv function
//�ú���������ֹ����ػ�����ȥ���������ε� ����
bool isGoodTri( Vec3i &v, vector<Vec3i> & tri ) 
{
	int a = v[0], b = v[1], c = v[2];
	v[0] = min(a,min(b,c));//v[0]�ҵ��������Ⱥ�˳��0....N-1��NΪ��ĸ���������Сֵ
	v[2] = max(a,max(b,c));//v[2]�洢���ֵ.
	v[1] = a+b+c-v[0]-v[2];//v[1]Ϊ�м�ֵ
	if (v[0] == -1) return false;

	vector<Vec3i>::iterator iter = tri.begin();//��ʼʱΪ��
	for(;iter!=tri.end();iter++)
	{
		Vec3i &check = *iter;//�����ǰ��ѹ��ĺʹ洢���ظ��ˣ���ֹͣ����false��
		if (check[0]==v[0] &&
			check[1]==v[1] &&
			check[2]==v[2])
		{
			break;
		}
	}
	if (iter == tri.end())
	{
		tri.push_back(v);
		return true;
	}
	return false;
}
/*
pts��Ҫ�ʷֵ�ɢ�㼯,in
img,�ʷֵĻ���,in
tri,�洢������ʾ����任������,out
*/
void TriSubDiv( vector<Point2f> &pts, Mat &img, vector<Vec3i> &tri ) 
{
	cv::Subdiv2D * subdiv;
	CvMemStorage* storage = cvCreateMemStorage(0); //�����洢��
	Rect rc = Rect(0,0, img.cols, img.rows);//������ͼ��Ĵ�С

	subdiv = cv::Subdiv2D ( CV_SEQ_KIND_SUBDIV2D, sizeof(*subdiv),
		sizeof(CvSubdiv2DPoint),
		sizeof(CvQuadEdge2D),
		storage );//Ϊ�ʷ����ݷ���ռ�
	cvInitSubdivDelaunay2D( subdiv, rc );
	for (size_t i = 0; i < pts.size(); i++)
	{
		CvSubdiv2DPoint *pt = cvSubdivDelaunay2DInsert( subdiv, pts[i] );//���ò��뷨�����ʷ�
		pt->id = i;//Ϊÿһ���������һ��id

	}

	CvSeqReader reader;//����CvSeqReader����
	int total = subdiv->edges->total;//�ߵ�����
	int elem_size = subdiv->edges->elem_size;//�ߵĴ�С

	cvStartReadSeq( (CvSeq*)(subdiv->edges), &reader, 0 );
	Point buf[3];
	const Point *pBuf = buf;
	Vec3i verticesIdx;
	Mat imgShow = img.clone();

	srand( (unsigned)time( NULL ) );   
	for( int i = 0; i < total; i++ ) 
	{   
		CvQuadEdge2D* edge = (CvQuadEdge2D*)(reader.ptr);   

		if( CV_IS_SET_ELEM( edge )) 
		{
			CvSubdiv2DEdge t = (CvSubdiv2DEdge)edge; 
			int iPointNum = 3;
			Scalar color = CV_RGB(rand()&255,rand()&255,rand()&255);
			//Scalar color=CV_RGB(255,0,0);
			//bool isNeg = false;
			int j;
			for(j = 0; j < iPointNum; j++ )
			{
				CvSubdiv2DPoint* pt = cvSubdiv2DEdgeOrg( t );//��ȡt�ߵ�Դ��
				if( !pt ) break;
				buf[j] = pt->pt;//����洢����
				//if (pt->id == -1) isNeg = true;
				verticesIdx[j] = pt->id;//��ȡ�����Id�ţ����������id�洢��verticesIdx��
				t = cvSubdiv2DGetEdge( t, CV_NEXT_AROUND_LEFT );//��ȡ��һ����
			}
			if (j != iPointNum) continue;
			if (isGoodTri(verticesIdx, tri))
			{
				//tri.push_back(verticesIdx);
				polylines( imgShow, &pBuf, &iPointNum, 
					1, true, color,
					1, CV_AA, 0);//����������
				//printf("(%d, %d)-(%d, %d)-(%d, %d)\n", buf[0].x, buf[0].y, buf[1].x, buf[1].y, buf[2].x, buf[2].y);
				//printf("%d\t%d\t%d\n", verticesIdx[0], verticesIdx[1], verticesIdx[2]);
				//imshow("Delaunay", imgShow);
				//waitKey();
			}

			t = (CvSubdiv2DEdge)edge+2;//�෴��Ե reversed e

			for(j = 0; j < iPointNum; j++ )
			{
				CvSubdiv2DPoint* pt = cvSubdiv2DEdgeOrg( t );
				if( !pt ) break;
				buf[j] = pt->pt;
				verticesIdx[j] = pt->id;
				t = cvSubdiv2DGetEdge( t, CV_NEXT_AROUND_LEFT );
			}   
			if (j != iPointNum) continue;
			if (isGoodTri(verticesIdx, tri))
			{
				//tri.push_back(verticesIdx);
				polylines( imgShow, &pBuf, &iPointNum, 
					1, true, color,
					1, CV_AA, 0);
				//printf("(%d, %d)-(%d, %d)-(%d, %d)\n", buf[0].x, buf[0].y, buf[1].x, buf[1].y, buf[2].x, buf[2].y);
				//printf("%d\t%d\t%d\n", verticesIdx[0], verticesIdx[1], verticesIdx[2]);
				//imshow("Delaunay", imgShow);
				//waitKey();
			}

		}

		CV_NEXT_SEQ_ELEM( elem_size, reader );

	}

	//RemoveDuplicate(tri);
	char title[100];
	sprintf_s(title, 100, "Delaunay: %d Triangles", tri.size());//tri�洢��Ϊ3������Ϊһ��vec3i����tri.size()��ʾ�����εĸ�����
	imshow(title, imgShow);
	waitKey();
}
#endif
// 
// void draw_subdiv_facet(
// 	cv::Mat& img,
// 	cv::Subdiv2D& subdiv,
// 	int edge
// 	) {
// 		int t = edge;
// 		int i, count = 0;
// 		vector<cv::Point> buf;
// 		// Count number of edges in facet
// 		do{
// 			count++;
// 			t = subdiv.getEdge( t, cv::Subdiv2D::NEXT_AROUND_LEFT );
// 		} while (t != edge );
// 		// Gather points
// 		//
// 		buf.resize(count);
// 		t = edge;
// 		for( i = 0; i < count; i++ ) {
// 			cv::Point2f pt;
// 			if( subdiv.edgeOrg(t, &pt) <= 0 )
// 				break;
// 			buf[i] = cv::Point(cvRound(pt.x), cvRound(pt.y));
// 			t = subdiv.getEdge( t, cv::Subdiv2D::NEXT_AROUND_LEFT );
// 		}
// 		// Around we go
// 		//
// 		if( i == count ){
// 			cv::Point2f pt;
// 			subdiv.edgeDst(subdiv.rotateEdge(edge, 1), &pt);
// 			fillConvexPoly(
// 				img, buf,
// 				cv::Scalar(rand()&255,rand()&255,rand()&255),
// 				8, 0
// 				);
// 			vector< vector<cv::Point> > outline;
// 			outline.push_back(buf);
// 			polylines(img, outline, true, cv::Scalar(), 1, cv::LINE_AA, 0);
// 			draw_subdiv_point( img, pt, cv::Scalar(0,0,0) );
// 		}
// }

void main(int argc, char* argv[])

{
 	Mat imgL(600,600,CV_8UC3);
// 	/************************************************************************/
// 	/* Delaunay triangulation                                               */
// 	/************************************************************************/
// 	cout<<"doing triangulation..."<<endl;
// 	vector<Vec3i> tri;
// 
// 	vector<Point2f> vec_points;
// 	for(int  i = 0; i < 60; i++ )  
// 	{  
// 		Point2f fp = cvPoint2D32f( (float)(rand()%(imgL.cols-10)),//ʹ��Լ���ھ���߿�10����֮�ڡ�  
// 			(float)(rand()%(imgL.rows-10)));  
// 		vec_points.push_back(fp);  
// 	}
// 
// 	TriSubDiv(vec_points, imgL, tri);
	cv::Rect rect(-10, -20, 600, 600); // Our outer bounding box
	cv::Subdiv2D subdiv(rect); // Create the initial subdivision


	cv::Point2f fp; //This is our point holder
	std::vector<Point2f> v_point;
	v_point.push_back(Point2f(-5,-5));
	v_point.push_back(Point2f(100,200));
	v_point.push_back(Point2f(300,100));

	for( std::vector<Point2f>::iterator it = v_point.begin() ; it != v_point.end() ; ++it ) {
		
		subdiv.insert(*it);
	}

	vector<cv::Vec6f> triangles;
	subdiv.getTriangleList(triangles);

	vector<Point> pt(3);
	cv::RNG rng(time(0));
	// �����ʷ�������
	for (size_t i = 0; i < triangles.size(); i++)
	{
		Vec6f t = triangles[i];
		pt[0] = Point(cvRound(t[0]), cvRound(t[1]));
		pt[1] = Point(cvRound(t[2]), cvRound(t[3]));
		pt[2] = Point(cvRound(t[4]), cvRound(t[5]));

		// ʹ�������ɫ������������
		if (rect.contains(pt[0]) && rect.contains(pt[1]) && rect.contains(pt[2]))
		{
			line(imgL, pt[0], pt[1], Scalar(rng.uniform(0, 256), rng.uniform(0, 256), rng.uniform(0, 256)), 1, LINE_AA, 0);
			line(imgL, pt[1], pt[2], Scalar(rng.uniform(0, 256), rng.uniform(0, 256), rng.uniform(0, 256)), 1, LINE_AA, 0);
			line(imgL, pt[2], pt[0], Scalar(rng.uniform(0, 256), rng.uniform(0, 256), rng.uniform(0, 256)), 1, LINE_AA, 0);
		}
	}
	imshow("subdiv", imgL);
	waitKey();

	vector<vector<cv::Point2f> > facets;
	vector<cv::Point2f> centers;
	subdiv.getVoronoiFacetList(vector<int>(), facets, centers);

	int id_n = 0;
	int id_e = 0;
	int ires = subdiv.locate(fp,id_e,id_n);
	if ( ires == cv::Subdiv2D::PTLOC_INSIDE ){
		//cv::Subdiv2D::PTLOC_ON_EDGE
		//cv::Subdiv2D::PTLOC_VERTEX
		//cv::Subdiv2D::PTLOC_OUTSIDE_RECT
		//cv::Subdiv2D::PTLOC_ERROR
	}
}
//
//void locate_point(
//	cv::Subdiv2D& subdiv,
//	const cv::Point2f& fp,
//	...
//	) {
//		int e;
//		int e0 = 0;
//		int vertex = 0;
//		subdiv.locate( fp, e0, vertex );
//		if( e0 > 0 ) {
//			e = e0;
//			do // Always 3 edges -- this is a triangulation, after all.
//			{
//				// [Insert your code here]
//				//
//				// Do something with e ...
//				e = subdiv.getEdge( e, cv::Subdiv2D::NEXT_AROUND_LEFT );
//			}
//			while( e != e0 );
//		}
//}
//
