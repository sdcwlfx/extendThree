#include <opencv2/opencv.hpp>

#include "math.h"
using namespace cv;
/**
Hough�任���ͼ���Ե
https://blog.csdn.net/yuyuntan/article/details/80141392#%E9%9C%8D%E5%A4%AB%E5%8F%98%E6%8D%A2%E6%8F%90%E5%8F%96%E7%9B%B4%E7%BA%BF%E5%A6%82%E4%BD%95%E5%AE%9E%E7%8E%B0%E5%AE%9E%E7%8E%B0%E6%9C%BA%E7%90%86%E6%98%AF%E4%B8%BA%E4%BD%95
����ռ���ÿ���㣨б�ʺͽؾࣩ����ʵ��һ��ֱ�ߣ�����ռ���һ���ߴ���ʵ�������о����̶��������ֱ�ߣ�
�����㷨��ͶƱ�ƣ����趨��ֵ��ȡ����ռ��н���һ����ߵ���Ŀ������ֵ�����е����꣬����ȡ�ĵ�������ʵ�������л�������Ϊ��Ե
*/
int main()
{
	IplImage *src=0,*gray=0,*dst,*src_hough,*color_dst=0;
	src = cvLoadImage("F:/ustcsse/AdvancedImageProcessing/experiment/picture/natali.jpg");
	if (src == 0)
	{
		return -1;
	}
	//cvCvtColor(src,gray, CV_BGR2GRAY);
	dst = cvCreateImage(cvGetSize(src),8,1);
	color_dst = cvCreateImage(cvGetSize(src),8,3);
	CvMemStorage* storage = cvCreateMemStorage(0);
	CvSeq* lines = 0;
	int i;
	//Canny��Ե���
	cvCanny(src,dst,50,200,3);
	//ת����Ե�����ͼΪ�Ҷ�ͼ
	cvCvtColor(dst,color_dst,CV_GRAY2BGR);

	//cvCvtColor(color_dst,color_dst,CV_RGB2GRAY);

	//ʹ�û���任�����صõ����߶�ʸ������lines��һ��line����һ������ռ���һ�㣬�������ʵ������һ���ߣ�
	lines = cvHoughLines2(dst,storage,CV_HOUGH_STANDARD,1,CV_PI/180,150,0,0);
	
	//������ͼ�л��Ƴ�ÿ���߶�
	for (i = 0; i < lines->total; i++)
	{
		float* line = (float*)cvGetSeqElem(lines, i);
		float rho = line[0];
		float theta = line[1];
		CvPoint pt1, pt2;
		double a = cos(theta), b = sin(theta);
		if (fabs(a) < 0.001)
		{
			pt1.x = pt2.x = cvRound(rho);
			pt1.y = 0;
			pt2.y = color_dst->height;
		}
		else if (fabs(b) < 0.001)
		{
			pt1.y = pt2.y = cvRound(rho);
			pt1.y = 0;
			pt2.y = color_dst->height;
		}
		else {
			pt1.x = 0;
			pt1.y = cvRound(rho / b);
			pt2.x = cvRound(rho / a);
			pt2.y = 0;
		}
		cvLine(color_dst, pt1, pt2, CV_RGB(255, 0, 0), 3, 8);
	}
		

		/*
		lines = cvHoughLines2(dst, storage, CV_HOUGH_PROBABILISTIC, 1, CV_PI / 180, 80, 30, 10);
		for (i = 0; i < lines->total; i++)
		{
			CvPoint* line = (CvPoint*)cvGetSeqElem(lines,i);
			cvLine(color_dst,line[0],line[1],CV_RGB(255,0,0),3,8);
		}*/
		cvNamedWindow("Source",1);
		cvShowImage("Source",src);

		//cvNamedWindow("GRAY",1);
		//cvShowImage("GRAY",gray);

		cvNamedWindow("HOUGH",1);
		cvShowImage("HOUGH",color_dst);

		printf("color_dsfͨ������%d",color_dst->nChannels);
		//src_hough = src + color_dst;
		

		char c=cvWaitKey(0);
		
		if (c == 27)
		{
			cvDestroyAllWindows();
		}

	


}