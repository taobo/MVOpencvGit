#pragma once
#include <Windows.h>
#include <iostream>
#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <opencv2/video/background_segm.hpp>

#include "videoprocessor.h"
#include "BGFGSegmentor.h"

using namespace std;
class OpenCVFunction
{
public:
	OpenCVFunction(void);
	~OpenCVFunction(void);
	
	cv::Mat getGrayImage(const cv::Mat &image);
	void SharpenImage(const cv::Mat &image, cv::Mat &result);
	bool GetHistogram(const cv::Mat & image, int nWidth, int nHeight, int nWidthStep, int *pHistogram);
	int Otsu(const cv::Mat &image, int nWidth, int nHeight, int nWidthStep);
	bool Threshold(cv::Mat &image, int nWidth, int nHeight, int nWidthStep, unsigned int nThreshold);
	bool FindContours(cv::Mat &image, int nWidth, int nHeight, int nWidthStep);
	int VedioProcess(void);
	int ForeGround(void);
};

