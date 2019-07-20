#include "opencv2/highgui/highgui.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <math.h>
#include <iostream>

using namespace cv;
using namespace std;



int main(int argv,char** argc)
{
	
	Mat img,image,l,u;

	image = imread(argc[1],1);
	cvtColor(image,img,CV_RGB2HSV);
	cvtColor(image,l,CV_RGB2HSV);
	cvtColor(image,u,CV_RGB2HSV);
	Mat hsv[3];
	Mat result = imread(argc[1],0);
	split(img,hsv);
	for(int i=1;i<img.rows;i++){
		for(int j=1;j<img.cols-1;j++){
			 //cout << (int)((img.at<Vec3b>(i,j)[0]+1)*1.0/(img.at<Vec3b>(i,j)[2]+1)*10.0) <<endl;
			 result.at<uchar>(i,j) = (int)((img.at<Vec3b>(i,j)[0]+1)*1.0/(img.at<Vec3b>(i,j)[2]+1)*100.0) ;

		}	
	}
	
	threshold(result, result, 0, 255, CV_THRESH_BINARY | CV_THRESH_OTSU);
	//namedWindow("image");
	for(int i=1;i<img.rows;i++){
		for(int j=1;j<img.cols-1;j++){
			 //cout << (int)((img.at<Vec3b>(i,j)[0]+1)*1.0/(img.at<Vec3b>(i,j)[2]+1)*10.0) <<endl;
			 if(result.at<uchar>(i,j)){
			 	image.at<Vec3b>(i,j)[0] = (image.at<Vec3b>(i-1,j-1)[0]+image.at<Vec3b>(i-1,j)[0]+image.at<Vec3b>(i-1,j+1)[0])/3;
			 	image.at<Vec3b>(i,j)[1] = (image.at<Vec3b>(i-1,j-1)[1]+image.at<Vec3b>(i-1,j)[1]+image.at<Vec3b>(i-1,j+1)[1])/3;
			 	image.at<Vec3b>(i,j)[2] = (image.at<Vec3b>(i-1,j-1)[2]+image.at<Vec3b>(i-1,j)[2]+image.at<Vec3b>(i-1,j+1)[2])/3;
			 	u.at<Vec3b>(i,j)[2] = (u.at<Vec3b>(i-1,j-1)[2]+u.at<Vec3b>(i-1,j)[2]+u.at<Vec3b>(i-1,j+1)[2])/3;
			 	
			 } 

		}	
	}
	for(int j=1;j<img.cols;j++){
		for(int i=1;i<img.rows-1;i++){
			if(result.at<uchar>(i,j))
				l.at<Vec3b>(i,j)[2] = (l.at<Vec3b>(i-1,j-1)[2]+l.at<Vec3b>(i,j-1)[2]+l.at<Vec3b>(i+1,j-1)[2])/3;
				img.at<Vec3b>(i,j)[2] = (l.at<Vec3b>(i,j)[2] + u.at<Vec3b>(i,j)[2])/2;
		}
	}
	cvtColor(l,l,CV_HSV2RGB);
	cvtColor(u,u,CV_HSV2RGB);
	cvtColor(img,img,CV_HSV2RGB);
	imshow("initial",image);
	imshow("final",img);
	imshow("Shadow_Region",result);
	waitKey(0);
	return 0;
	//cvtColor(img,image,CV_HSV2RGB);
	
}