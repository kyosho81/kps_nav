//
//
// FLIRTLib - Fast Laser Interesting Region Transform Library
// Copyright (C) 2009-2010 Gian Diego Tipaldi and Kai O. Arras
//
// This file is part of FLIRTLib.
//
// FLIRTLib is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// FLIRTLib is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with FLIRTLib.  If not, see <http://www.gnu.org/licenses/>.
//

#include "flirt/feature/Detector.h"
#include "flirt/feature/ShapeContext.h"
#include "flirt/feature/BetaGrid.h"
#include "flirt/feature/RangeDetector.h"
#include "flirt/feature/CurvatureDetector.h"
#include "flirt/feature/NormalBlobDetector.h"
#include "flirt/feature/NormalEdgeDetector.h"
#include "flirt/feature/RansacFeatureSetMatcher.h"
#include "flirt/feature/RansacMultiFeatureSetMatcher.h"
#include "flirt/sensorstream/CarmenLog.h"
#include "flirt/sensorstream/LogSensorStream.h"
#include "flirt/sensorstream/SensorStream.h"
#include "flirt/utils/SimpleMinMaxPeakFinder.h"
#include "flirt/utils/HistogramDistances.h"

#include <math.h>
#include <iostream>
#include <string>
#include <string.h>
#include <sstream>
#include <utility>

#include "DBoW3/DBoW3.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/features2d/features2d.hpp>

//#include <sys/time.h>

LogSensorStream m_sensorReference(NULL,NULL);

CurvatureDetector *m_detectorCurvature = NULL;
NormalBlobDetector *m_detectorNormalBlob = NULL;
NormalEdgeDetector *m_detectorNormalEdge = NULL;
RangeDetector *m_detectorRange = NULL;
Detector* m_detector = NULL;

BetaGridGenerator *m_betaGenerator = NULL;
ShapeContextGenerator *m_shapeGenerator = NULL;
DescriptorGenerator *m_descriptor = NULL;

RansacFeatureSetMatcher *m_ransac = NULL;

double angErrorTh = 0.2;
double linErrorTh = 0.5;

std::vector< std::vector<InterestPoint *> > m_pointsReference;
std::vector< OrientedPoint2D > m_posesReference;

unsigned int corresp[] = {0, 3, 5, 7, 9, 11, 13, 15};

double m_error[8] = {0.}, m_errorC[8] = {0.}, m_errorR[8] = {0.};
unsigned int m_match[8] = {0}, m_matchC[8] = {0}, m_matchR[8] = {0};
unsigned int m_valid[8] = {0};

//struct timeval detectTime, describeTime, ransacTime;

unsigned int m_localSkip = 1;

DBoW3::Vocabulary vocab;
DBoW3::Database db;
std::vector<std::vector<cv::Mat> > descriptors;

void help(){
	std::cerr << "FLIRTLib version 0.9b - authors Gian Diego Tipaldi and Kai O. Arras" << std::endl
			  << "Usage: ransacLoopClosureTest -filename <logfile> [options] " << std::endl
			  << "Options:" << std::endl

			  << " -filename          \t The logfile in CARMEN format to process (mandatory)." << std::endl
			  << " -scale             \t The number of scales to consider (default=5)." << std::endl
			  << " -dmst              \t The number of spanning tree for the curvature detector (deafult=2)." << std::endl
			  << " -window            \t The size of the local window for estimating the normal signal (default=3)." << std::endl
			  << " -detectorType      \t The type of detector to use. Available options are (default=0):" << std::endl
			  << "                    \t     0 - Curvature detector;" << std::endl
			  << "                    \t     1 - Normal edge detector;" << std::endl
			  << "                    \t     2 - Normal blob detector;" << std::endl
			  << "                    \t     3 - Range detector." << std::endl
			  << " -descriptorType    \t The type of descriptor to use. Available options are (default=0):" << std::endl
			  << "                    \t     0 - Beta - grid;" << std::endl
			  << "                    \t     1 - Shape context." << std::endl
			  << " -distanceType      \t The distance function to compare the descriptors. Available options are (default=2):" << std::endl
			  << "                    \t     0 - Euclidean distance;" << std::endl
			  << "                    \t     1 - Chi square distance;" << std::endl
			  << "                    \t     2 - Symmetric Chi square distance;" << std::endl
			  << "                    \t     3 - Bhattacharyya distance;" << std::endl
			  << "                    \t     4 - Kullback Leibler divergence;" << std::endl
			  << "                    \t     5 - Jensen Shannon divergence." << std::endl
			  << " -baseSigma         \t The initial standard deviation for the smoothing operator (default=0.2)." << std::endl
			  << " -sigmaStep         \t The incremental step for the scales of the smoothing operator. (default=1.4)." << std::endl
			  << " -minPeak           \t The minimum value for a peak to be detected (default=0.34)." << std::endl
			  << " -minPeakDistance   \t The minimum difference with the neighbors for a peak to be detected (default=0.001)." << std::endl
			  << " -acceptanceSigma   \t The standard deviation of the detection error (default=0.1)." << std::endl
			  << " -success           \t The success probability of RANSAC (default=0.95)." << std::endl
			  << " -inlier            \t The inlier probability of RANSAC (default=0.4)." << std::endl
			  << " -matchingThreshold \t The threshold two descriptors are considered matched (default=0.4)." << std::endl
			  << " -strategy          \t The strategy for matching two descriptors. Available options are (default=0):" << std::endl
			  << "                    \t     0 - Nearest Neighbour. Only the closest match above the threshold is considered;" << std::endl
			  << "                    \t     1 - Threshold. All the matches above the threshold are considered." << std::endl
			  << std::endl
			  << "The program computes matches every scan with all the others in the logfile. To work properly, the logfile must"  << std::endl
			  << "be corrected by a SLAM algorithm beforehand (the provided logfiles are already corrected). The program writes" << std::endl
			  << "the following matching statistics in the following files:" << std::endl
			  << "    correct matches: <logfile>_<detector>_<descriptor>_<distance>_match.dat" << std::endl
			  << "    matching error : <logfile>_<detector>_<descriptor>_<distance>_error.dat" << std::endl
			  << "    matching time  : <logfile>_<detector>_<descriptor>_<distance>_time.dat" << std::endl
			  << std::endl
			  << std::endl;
}

void match(unsigned int position, std::ofstream &log_match)
{
    m_sensorReference.seek(position);
    //pointsLocal current laser interest point 
	//reset interest point pos
    std::vector<InterestPoint *> pointsLocal(m_pointsReference[position].size());
    const LaserReading* lreadReference = dynamic_cast<const LaserReading*>(m_sensorReference.current());
    for(unsigned int j = 0; j < m_pointsReference[position].size(); j++){
		InterestPoint * point = new InterestPoint(*m_pointsReference[position][j]);
		point->setPosition(lreadReference->getLaserPose().ominus(point->getPosition()));
// 		SDelete(pointsLocal[j]);
 		pointsLocal[j] = point;

// 		const BetaGrid *betaGrid = dynamic_cast<const BetaGrid *>(point->getDescriptor());
// 		std::vector< std::vector< double > > m_mat = betaGrid->getHistogram();
    }
    std::cout<<std::endl;
	std::cout<<"ref pos:"<<position<<" "<<m_posesReference[position].x<<" "<<m_posesReference[position].y<<" "<<m_posesReference[position].theta<<std::endl;
	log_match<<"ref id:"<<position<<" match id:";
//     unsigned int* inliers = new unsigned int[m_pointsReference.size()];
//     double* results = new double[m_pointsReference.size()];
//     double* linearErrors = new double[m_pointsReference.size()];
//     double* angularErrors = new double[m_pointsReference.size()];
	std::vector<int> inliers;
	std::vector<double> results;
	std::vector<double> linearErrors;
	std::vector<double> angularErrors;
	inliers.resize(m_pointsReference.size());
	results.resize(m_pointsReference.size());
	linearErrors.resize(m_pointsReference.size());
	angularErrors.resize(m_pointsReference.size());


    //struct timeval start, end, diff, sum;
    for(unsigned int i = 0; i < m_pointsReference.size(); i++){
		//pointsLocal match all scan

		if(fabs(double(i) - double(position)) < m_localSkip) {
			results[i] = 1e17;
			inliers[i] = 0;
			linearErrors[i] = 1e17;
			angularErrors[i] = 1e17;
			continue;
		}
		OrientedPoint2D transform;
		std::vector< std::pair<InterestPoint*, InterestPoint* > > correspondences;
		//gettimeofday(&start,NULL);
	// 	std::cout << m_pointsReference[i].size() << " vs. " << pointsLocal.size() << std::endl;
		results[i] = m_ransac->matchSets(m_pointsReference[i], pointsLocal, transform, correspondences);
	
		//gettimeofday(&end,NULL);
		//timersub(&end, &start, &diff);
		//timeradd(&ransacTime, &diff, &sum);

		//ransacTime = sum;
		inliers[i] = correspondences.size();
		OrientedPoint2D delta = m_posesReference[position] - transform;
		//if((correspondences.size() > 9) && (abs(int(i - position)) > 10)){
		if((correspondences.size() > 9) ){
			log_match<<i<<" ";
			std::cout<<"match pos:"<<i<<"-"<<correspondences.size()<<"-"<<transform.x<<" "<<transform.y<<" "<<transform.theta<<std::endl;
		}

		linearErrors[i] = correspondences.size() ? delta * delta : 1e17;
		angularErrors[i] = correspondences.size() ? delta.theta * delta.theta : 1e17;
    }
    
	for(unsigned int c = 0; c < 8; c++){
		unsigned int maxCorres = 0;
		double maxResult = 1e17;
		double linError = 1e17, angError = 1e17;
		double linErrorC = 1e17, angErrorC = 1e17;
		double linErrorR = 1e17, angErrorR = 1e17;
		bool valid = false;

		for(unsigned int i = 0; i < m_pointsReference.size(); i++){
			if(linError + angError > linearErrors[i] + angularErrors[i]) {
				linError = linearErrors[i];
				angError = angularErrors[i];
			}
			if(maxCorres < inliers[i]){
				linErrorC = linearErrors[i];
				angErrorC = angularErrors[i];
				maxCorres = inliers[i];
			}
			if(maxResult > results[i]){
				linErrorR = linearErrors[i];
				angErrorR = angularErrors[i];
				maxResult = results[i];
			}
			valid = valid || inliers[i] >= corresp[c];
		}
	
	
		if(valid){
			m_match[c] += (linError <= (linErrorTh * linErrorTh) && angError <= (angErrorTh * angErrorTh) );
			m_matchC[c] += (linErrorC <= (linErrorTh * linErrorTh) && angErrorC <= (angErrorTh * angErrorTh) );
			m_matchR[c] += (linErrorR <= (linErrorTh * linErrorTh) && angErrorR <= (angErrorTh * angErrorTh) );
	    
			m_error[c] += sqrt(linError + angError);
			m_errorC[c] += sqrt(linErrorC + angErrorC);
			m_errorR[c] += sqrt(linErrorR + angErrorR);
	    
			m_valid[c]++;
		}
    }

	std::vector<InterestPoint *>::iterator it = pointsLocal.begin();
	for ( ; it != pointsLocal.end(); ++it )
	{
		InterestPoint *p = *it;
		if (p)
		{
			delete p;
		}
		
	}
	
// 	if(inliers){
// 		delete[] inliers;
// 		inliers = 0;
// 	}
// 	if (results)
// 	{
// 		delete[] results;
// 		results = 0;
// 	}
// 	if (linearErrors)
// 	{
// 		delete[] linearErrors;
// 		linearErrors = 0;
// 	}
// 	if (angularErrors)
// 	{
// 		delete[] angularErrors;
// 		angularErrors = 0;
// 	}
}

void detectLog(){
    unsigned int i = 0;
    unsigned int position = m_sensorReference.tell();
    m_sensorReference.seek(0,END);
    unsigned int last = m_sensorReference.tell();
    m_sensorReference.seek(0);
    
    std::string bar(51, ' ');
    bar[0] = '#';
    unsigned int progress = 0;
    
    //struct timeval start, end;
    //gettimeofday(&start, NULL);
    while(!m_sensorReference.end()){
	unsigned int currentProgress = (m_sensorReference.tell()*100)/last;
	if (progress < currentProgress){
	    progress = currentProgress;
	    bar[progress/2] = '#';
	    std::cout << "\rDetecting points  [" << bar << "] " << (m_sensorReference.tell()*100)/last << "%" << std::flush;
	}
	const LaserReading* lreadReference = dynamic_cast<const LaserReading*>(m_sensorReference.next());
	if (lreadReference){
	    m_detector->detect(*lreadReference, m_pointsReference[i]);
	    m_posesReference[i] = lreadReference->getLaserPose();
	    i++;
	}
    }
    //gettimeofday(&end,NULL);
    //timersub(&end,&start,&detectTime);
    m_sensorReference.seek(position);
    std::cout << " done." << std::endl;
}

void countLog(){
    double flirtNum = 0.;
    unsigned int count = 0;
    
    std::string bar(51, ' ');
    bar[0] = '#';
    
    unsigned int progress = 0;
    for(unsigned int i = 0; i < m_pointsReference.size(); i++){
		unsigned int currentProgress = (i*100)/(m_pointsReference.size() - 1);
		if (progress < currentProgress){
			progress = currentProgress;
			bar[progress/2] = '#';
			std::cout << "\rCounting points  [" << bar << "] " << progress << "%" << std::flush;
		}
		if(m_pointsReference[i].size()){
			flirtNum += m_pointsReference[i].size();
			count++;
		}
    }
    flirtNum=count?flirtNum/double(count):0.;
    std::cout << " done.\nFound " << flirtNum << " FLIRT features per scan." << std::endl;
}

void describeLog(){

	
	//std::vector<cv::Mat> descriptors;
	//DBoW3::Database db( vocab, false, 0);

	

    unsigned int i = 0;
    unsigned int position = m_sensorReference.tell();
    m_sensorReference.seek(0,END);
    unsigned int last = m_sensorReference.tell();
    m_sensorReference.seek(0);

    std::string bar(51, ' ');
    bar[0] = '#';
    //struct timeval start, end;
    //gettimeofday(&start, NULL);
    unsigned int progress = 0;
    
	//for each scan
	while(!m_sensorReference.end()){
		unsigned int currentProgress = (m_sensorReference.tell()*100)/last;
		if (progress < currentProgress){
			progress = currentProgress;
			bar[progress/2] = '#';
			std::cout << "\rDescribing points  [" << bar << "] " << progress << "%" << std::flush;
		}
		std::vector<cv::Mat> dec_point_list;
		//cv::Mat M4 = cv::Mat_<double>::zeros( m_pointsReference[i].size(), 48);
		double max_d = 0;
		double min_d = 1e17;
		const LaserReading* lreadReference = dynamic_cast<const LaserReading*>(m_sensorReference.next());
		if (lreadReference){


			//for each describer point
			for(unsigned int j = 0; j < m_pointsReference[i].size(); j++){
				Descriptor* descriptor = m_descriptor->describe(*m_pointsReference[i][j], *lreadReference);
				m_pointsReference[i][j]->setDescriptor(descriptor);
				const BetaGrid *betaGrid = dynamic_cast<const BetaGrid *>(descriptor);
				//every dec has 12*4 = 48 (double)
				std::vector< std::vector< double > > m_mat = betaGrid->getHistogram();
				//std::cout<<"m_mat:"<<m_mat<<std::endl;
				cv::Mat M4 = cv::Mat_<double>::zeros( 1, 48);

				for ( int k = 0 ; k < m_mat.size() ; ++k )
				{
					for ( int l = 0 ; l < m_mat[k].size() ; ++l )
					{
						int index = k*m_mat[k].size() + l;
// 						if (index > 31)
// 						{
// 							break;
// 						}
						max_d = std::max(max_d,m_mat[k][l]);
						min_d = std::min(min_d,m_mat[k][l]);
						M4.at<double>(0,index) = m_mat[k][l];
					}
				}
				cv::Mat M5 ;
				M4.convertTo(M5,CV_8U,255.0/(max_d-min_d));
				//M4.convertTo(M5,CV_32F);

				dec_point_list.push_back(M5);
				//std::cout<<M5<<std::endl;
				//cv::Mat des_list;
			}
//			descriptors.push_back(M4);
// 			DBoW3::BowVector v2;
// 			vocab.transform( M4, v2 );
// 			db.add(v2);
			//std::cout<<M4<<std::endl;
			i++;
		}
		descriptors.push_back(dec_point_list);

    }
	
	//db.add(descriptors[0]);
	vocab.create(descriptors);
	db.setVocabulary(vocab);
	for (int i = 0 ; i < descriptors.size() ; ++i )
	{
		db.add(descriptors[i]);
	}

	
    //gettimeofday(&end,NULL);
    //timersub(&end,&start,&describeTime);
     m_sensorReference.seek(position);
    std::cout << " done." << std::endl;
}

int main(int argc, char **argv){

	

    std::string filename("");
    unsigned int scale = 5, dmst = 2, window = 3, detectorType = 0, descriptorType = 0, distanceType = 2, strategy = 0;
    double baseSigma = 0.2, sigmaStep = 1.4, minPeak = 0.34, minPeakDistance = 0.001, acceptanceSigma = 0.1, success = 0.95, inlier = 0.4, matchingThreshold = 0.4;
	bool useMaxRange = false;
    
    int i = 1;
    while(i < argc){
		if(strncmp("-filename", argv[i], sizeof("-filename")) == 0 ){
			filename = argv[++i];
			i++;
		} else if(strncmp("-detector", argv[i], sizeof("-detector")) == 0 ){
			detectorType = atoi(argv[++i]);
			i++;
		} else if(strncmp("-descriptor", argv[i], sizeof("-descriptor")) == 0 ){
			descriptorType = atoi(argv[++i]);
			i++;
		} else if(strncmp("-distance", argv[i], sizeof("-distance")) == 0 ){
			distanceType = atoi(argv[++i]);
			i++;
		} else if(strncmp("-strategy", argv[i], sizeof("-strategy")) == 0 ){
			strategy = atoi(argv[++i]);
			i++;
		} else if(strncmp("-baseSigma", argv[i], sizeof("-baseSigma")) == 0 ){
			baseSigma = strtod(argv[++i], NULL);
			i++;
		} else if(strncmp("-sigmaStep", argv[i], sizeof("-sigmaStep")) == 0 ){
			sigmaStep = strtod(argv[++i], NULL);
			i++;
		} else if(strncmp("-minPeak", argv[i], sizeof("-minPeak")) == 0 ){
			minPeak = strtod(argv[++i], NULL);
			i++;
		} else if(strncmp("-minPeakDistance", argv[i], sizeof("-minPeakDistance")) == 0 ){
			minPeakDistance = strtod(argv[++i], NULL);
			i++;
		} else if(strncmp("-scale", argv[i], sizeof("-scale")) == 0 ){
			scale = atoi(argv[++i]);
			i++;
		} else if(strncmp("-dmst", argv[i], sizeof("-dmst")) == 0 ){
			dmst = atoi(argv[++i]);
			i++;
		} else if(strncmp("-window", argv[i], sizeof("-window")) == 0 ){
			window = atoi(argv[++i]);
			i++;
		} else if(strncmp("-acceptanceSigma", argv[i], sizeof("-acceptanceSigma")) == 0 ){
			acceptanceSigma = strtod(argv[++i], NULL);
			i++;
		} else if(strncmp("-success", argv[i], sizeof("-success")) == 0 ){
			success = strtod(argv[++i], NULL);
			i++;
		} else if(strncmp("-inlier", argv[i], sizeof("-inlier")) == 0 ){
			inlier = strtod(argv[++i], NULL);
			i++;
		} else if(strncmp("-matchingThreshold", argv[i], sizeof("-matchingThreshold")) == 0 ){
			matchingThreshold = strtod(argv[++i], NULL);
			i++;
		} else if(strncmp("-localSkip", argv[i], sizeof("-localSkip")) == 0 ){
			m_localSkip = atoi(argv[++i]);
			i++;
		} else if(strncmp("-help", argv[i], sizeof("-localSkip")) == 0 ){
			help();
			exit(0);
		} else {
			i++;
		}
    }
    
    if(!filename.size()){
		help();
		exit(-1);
    }
    
    
    CarmenLogWriter writer;
    CarmenLogReader reader;
    
    m_sensorReference = LogSensorStream(&reader, &writer);
    
    m_sensorReference.load(filename);
    
    SimpleMinMaxPeakFinder *m_peakMinMax = new SimpleMinMaxPeakFinder(minPeak, minPeakDistance);
    
    
    std::string detector("");
    switch(detectorType){
	case 0:
	    m_detectorCurvature = new CurvatureDetector(m_peakMinMax, scale, baseSigma, sigmaStep, dmst);
		m_detectorCurvature->setUseMaxRange(useMaxRange);
	    m_detector = m_detectorCurvature;
	    detector = "curvature";
	    break;
	case 1:
	    m_detectorNormalEdge = new NormalEdgeDetector(m_peakMinMax, scale, baseSigma, sigmaStep, window);
	    m_detectorNormalEdge->setUseMaxRange(useMaxRange);
		m_detector = m_detectorNormalEdge;
	    detector = "edge";
	    break;
	case 2:
	    m_detectorNormalBlob = new NormalBlobDetector(m_peakMinMax, scale, baseSigma, sigmaStep, window);
		m_detectorNormalBlob->setUseMaxRange(useMaxRange);
	    m_detector = m_detectorNormalBlob;
	    detector = "blob";
	    break;
	case 3:
	    m_detectorRange = new RangeDetector(m_peakMinMax, scale, baseSigma, sigmaStep);
		m_detectorRange->setUseMaxRange(useMaxRange);
	    m_detector = m_detectorRange;
	    detector = "range";
	    break;
	default:
	    std::cerr << "Wrong detector type" << std::endl;
	    exit(-1);
    }
    
    HistogramDistance<double> *dist = NULL;
    
    std::string distance("");
    switch(distanceType){
	case 0:
	    dist = new EuclideanDistance<double>();
	    distance = "euclid";
	    break;
	case 1:
	    dist = new Chi2Distance<double>();
	    distance = "chi2";
	    break;
	case 2:
	    dist = new SymmetricChi2Distance<double>();
	    distance = "symchi2";
	    break;
	case 3:
	    dist = new BatthacharyyaDistance<double>();
	    distance = "batt";
	    break;
	case 4:
	    dist = new KullbackLeiblerDistance<double>();
	    distance = "kld";
	    break;
	case 5:
	    dist = new JensenShannonDistance<double>();
	    distance = "jsd";
	    break;
	default:
	    std::cerr << "Wrong distance type" << std::endl;
	    exit(-1);
    }
    
    std::string descriptor("");
    switch(descriptorType){
	case 0:
	    m_betaGenerator = new BetaGridGenerator(0.02, 0.5, 4, 12);
	    m_betaGenerator->setDistanceFunction(dist);
	    m_descriptor = m_betaGenerator;
	    descriptor = "beta";
	    break;
	case 1:
	    m_shapeGenerator = new ShapeContextGenerator(0.02, 0.5, 4, 12);
	    m_shapeGenerator->setDistanceFunction(dist);
	    m_descriptor = m_shapeGenerator;
	    descriptor = "shape";
	    break;
	default:
	    std::cerr << "Wrong descriptor type" << std::endl;
	    exit(-1);
    }
    
    switch(strategy){
	case 0:
	    m_ransac = new RansacFeatureSetMatcher(acceptanceSigma * acceptanceSigma * 5.99, success, inlier, matchingThreshold, acceptanceSigma * acceptanceSigma * 3.84, false);
	    break;
	case 1:
	    m_ransac = new RansacMultiFeatureSetMatcher(acceptanceSigma * acceptanceSigma * 5.99, success, inlier, matchingThreshold, acceptanceSigma * acceptanceSigma * 3.84, false);
	    break;
	default:
	    std::cerr << "Wrong strategy type" << std::endl;
	    exit(-1);
    }
    
    std::cerr << "Processing file:\t" << filename << "\nDetector:\t\t" << detector << "\nDescriptor:\t\t" << descriptor << "\nDistance:\t\t" << distance << std::endl;

    m_sensorReference.seek(0,END);
    unsigned int end = m_sensorReference.tell();
    m_sensorReference.seek(0,BEGIN);

    m_pointsReference.resize(end + 1);
    m_posesReference.resize(end + 1);
    
    detectLog();
    
    countLog();
    
    describeLog();
    
    std::string outfile = filename;
    
    //timerclear(&ransacTime);
    
    std::string bar(51,' ');
    bar[0] = '#';
    unsigned int progress = 0;
    
	std::ofstream log_match("match",std::ios::binary | std::ios::trunc);

    for(unsigned int i =0; i < m_pointsReference.size(); i++){
		unsigned int currentProgress = (i*100)/(m_pointsReference.size() - 1);
		if (progress < currentProgress){
			progress = currentProgress;
			bar[progress/2] = '#';
			//std::cout << "\rMatching  [" << bar << "] " << progress << "%" << std::flush;
			std::cout << "Matching  [" << bar << "] " << progress << "%" << std::flush;
		}
    	match(i,log_match);
		log_match<<" db_match:";
		DBoW3::QueryResults ret;
		db.query( descriptors[i], ret, 4);      // max result=4
		for ( int i = 0 ; i < ret.size() ; ++i )
		{
			log_match<<ret[i]<<" ";log_match<<ret[i].Id<<" ";
		}
		log_match<<std::endl;
		//std::cout<<ret<<std::endl;
    }
    std::cout << " done." << std::endl;
    
    std::stringstream matchFile;
    std::stringstream errorFile;
    std::stringstream timeFile;
    matchFile << outfile << "_" << detector << "_" << descriptor << "_" << distance << "_match.dat";
    errorFile << outfile << "_" << detector << "_" << descriptor << "_" << distance << "_error.dat";
    timeFile << outfile << "_" << detector << "_" << descriptor << "_" << distance << "_time.dat";
    
    std::ofstream matchOut(matchFile.str().c_str());
    std::ofstream errorOut(errorFile.str().c_str());
    std::ofstream timeOut(timeFile.str().c_str());
	
	matchOut << "# Number of matches according to various strategies" << std::endl;
    matchOut << "# The valid matches are the one with at least n correspondences in the inlier set " << std::endl;
    matchOut << "# where n = {0, 3, 5, 7, 9, 11, 13, 15}, one for each line " << std::endl;
    matchOut << "# optimal \t correspondence \t residual \v valid" << std::endl;
    
	errorOut << "# Mean error according to various strategies" << std::endl;
	errorOut << "# The valid matches are the one with at least n correspondences in the inlier set " << std::endl;
    errorOut << "# where n = {0, 3, 5, 7, 9, 11, 13, 15}, one for each line " << std::endl;
    errorOut << "# optimal \t correspondence \t residual \v valid" << std::endl;
	
	timeOut << "# Total time spent for the various steps" << std::endl;
	timeOut << "# detection \t description \t RANSAC" << std::endl;

    for(unsigned int c = 0; c < 8; c++){
      matchOut << m_match[c] << "\t" << m_matchC[c] << "\t" << m_matchR[c] << "\t" << m_valid[c] << std::endl;
      errorOut << m_error[c]/m_valid[c] << "\t" << m_errorC[c]/m_valid[c] << "\t" << m_errorR[c]/m_valid[c] << "\t" << m_valid[c] << std::endl;
    }

	log_match.flush();
	log_match.close();
	int i2;
	std::cin>>i2;
//     timeOut << double(detectTime.tv_sec) + 1e-06 * double(detectTime.tv_usec) << "\t"
// 	    << double(describeTime.tv_sec) + 1e-06 * double(describeTime.tv_usec) << "\t"
// 	    << double(ransacTime.tv_sec) + 1e-06 * double(ransacTime.tv_usec) << std::endl;
}

