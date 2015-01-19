#include "OpenCVFunction.h"


OpenCVFunction::OpenCVFunction(void)
{
}


OpenCVFunction::~OpenCVFunction(void)
{
}


cv::Mat OpenCVFunction::getGrayImage(const cv::Mat &image)
{
	cv::Mat result;
	cv::cvtColor(image, result, cv::COLOR_BGR2GRAY);
	return result;
}


void OpenCVFunction::SharpenImage(const cv::Mat &image, cv::Mat &result)
{
	result.create(image.rows, image.cols, image.type());
	int row = image.rows;
	int col = image.cols;
	for(int i = 1; i < row - 1; i++)
	{
		const uchar *previous = image.ptr<const uchar>(i - 1);
		const uchar *next = image.ptr<const uchar>(i + 1);
		const uchar *current = image.ptr<const uchar>(i);
		uchar *output = result.ptr<uchar>(i);

		for(int j = 1; j < col - 1; j++)
		{
			if ( image.channels() == 1 )
			{
				output[j] = cv::saturate_cast<uchar>(5 * current[j] - current[j - 1] - current[j + 1] - previous[j] - next[j]);
			}
			else if(image.channels() == 3)
			{
				result.at<cv::Vec3b>(i, j)[0] = cv::saturate_cast<uchar>(image.at<cv::Vec3b>(i, j)[0] * 5 - image.at<cv::Vec3b>(i, j - 1)[0] - image.at<cv::Vec3b>(i, j + 1)[0] - image.at<cv::Vec3b>(i - 1, j)[0] - image.at<cv::Vec3b>(i + 1, j)[0]);
				result.at<cv::Vec3b>(i, j)[1] = cv::saturate_cast<uchar>(image.at<cv::Vec3b>(i, j)[1] * 5 - image.at<cv::Vec3b>(i, j - 1)[1] - image.at<cv::Vec3b>(i, j + 1)[1] - image.at<cv::Vec3b>(i - 1, j)[1] - image.at<cv::Vec3b>(i + 1, j)[1]);
				result.at<cv::Vec3b>(i, j)[2] = cv::saturate_cast<uchar>(image.at<cv::Vec3b>(i, j)[2] * 5 - image.at<cv::Vec3b>(i, j - 1)[2] - image.at<cv::Vec3b>(i, j + 1)[2] - image.at<cv::Vec3b>(i - 1, j)[2] - image.at<cv::Vec3b>(i + 1, j)[2]);
			}
		}
	}
	
	result.row(0).setTo(cv::Scalar(0));
	result.row(result.rows - 1).setTo(cv::Scalar(0));
	result.col(0).setTo(cv::Scalar(0));
	result.col(result.cols - 1).setTo(cv::Scalar(0));
}


// ��ȡֱ��ͼ   
// 1. pImageData   ͼ������   
// 2. nWidth       ͼ����   
// 3. nHeight      ͼ��߶�   
// 4. nWidthStep   ͼ���д�С   
// 5. pHistogram   ֱ��ͼ   
bool OpenCVFunction::GetHistogram(const cv::Mat &image, int nWidth, int nHeight, int nWidthStep, int *pHistogram)   
{   
    int            i     = 0;   
    int            j     = 0;   
    //uchar *pLine = NULL;   
    // ���ֱ��ͼ   
    memset(pHistogram, 0, sizeof(int) * 256); 
	const uchar *pLine = image.ptr<const uchar>(0);

    for (j = 0; j < nHeight; j++, pLine += nWidthStep)   
    {   
        for (i = 0; i < nWidth; i++)   
        {   
            pHistogram[pLine[i]]++;   
        }   
    }   
    return true;   
} 

// ���ȡ��ֵ   
// 1. pImageData   ͼ������   
// 2. nWidth       ͼ����   
// 3. nHeight      ͼ��߶�   
// 4. nWidthStep   ͼ���д�С   
// ����������ֵ   
int OpenCVFunction::Otsu(const cv::Mat &image, int nWidth, int nHeight, int nWidthStep)   
{   
    int    i          = 0;   
    int    j          = 0;   
    int    nTotal     = 0;   
    int    nSum       = 0;   
    int    A          = 0;   
    int    B          = 0;   
    double u          = 0;   
    double v          = 0;   
    double dVariance  = 0;   
    double dMaximum   = 0;   
    int    nThreshold = 0;   
    int    nHistogram[256];   
    // ��ȡֱ��ͼ   
    GetHistogram(image, nWidth, nHeight, nWidthStep, nHistogram);   
    for (i = 0; i < 256; i++)   
    {   
        nTotal += nHistogram[i];   
        nSum   += (nHistogram[i] * i);   
    }   
    for (j = 0; j < 256; j++)   
    {   
        A = 0;   
        B = 0;   
        for (i = 0; i < j; i++)   
        {   
            A += nHistogram[i];   
            B += (nHistogram[i] * i);   
        }   
        if (A > 0)   
        {   
            u = B / A;   
        }   
        else  
        {   
            u = 0;   
        }   
        if (nTotal - A > 0)    
        {   
            v = (nSum - B) / (nTotal - A);   
        }   
        else  
        {   
            v = 0;   
        }   
        dVariance = A * (nTotal - A) * (u - v) * (u - v);   
        if (dVariance > dMaximum)   
        {   
            dMaximum = dVariance;   
            nThreshold = j;   
        }   
    }   
    return nThreshold;   
}


// ��ֵ��   
// 1. pImageData   ͼ������   
// 2. nWidth       ͼ����   
// 3. nHeight      ͼ��߶�   
// 4. nWidthStep   ͼ���д�С   
// 5. nThreshold   ��ֵ   
bool OpenCVFunction::Threshold(cv::Mat &image, int nWidth, int nHeight, int nWidthStep, unsigned int nThreshold)   
{   
    int            i     = 0;   
    int            j     = 0;   
    uchar *pLine = image.ptr<uchar>(0);   
    for (j = 0; j < nHeight; j++, pLine += nWidthStep)   
    {   
        for (i = 0; i < nWidth; i++)   
        {   
            if (pLine[i] >= nThreshold)   
            {   
                pLine[i] = 0x00;   
            }   
            else  
            {   
                pLine[i] = 0xff;   
            }   
        }   
    }   
    return true;   
}


bool OpenCVFunction::FindContours(cv::Mat &image, int nWidth, int nHeight, int nWidthStep)
{
	int            i        = 0;   
    int            j        = 0;   
    uchar *pLine[3] = { NULL, NULL, NULL };   
    for (j = 1; j < nHeight - 1; j++)   
    {   
        pLine[0]  = image.ptr<uchar>(j - 1);   
        pLine[1]  = image.ptr<uchar>(j);   
        pLine[2]  = image.ptr<uchar>(j + 1);   
        for (i = 1; i < nWidth - 1; i++)   
        {   
            if (pLine[0][i-1] == 0xFF && pLine[0][i] == 0xFF && pLine[0][i+1] == 0xFF &&   
                pLine[1][i-1] == 0xFF && pLine[1][i] == 0xFF && pLine[1][i+1] == 0xFF &&   
                pLine[2][i-1] == 0xFF && pLine[2][i] == 0xFF && pLine[2][i+1] == 0xFF)   
            {   
                pLine[0][i-1] = 0;   
            }   
            else  
            {   
                pLine[0][i-1] = pLine[1][i];   
            }   
        }   
    }   
    return true;
}


int OpenCVFunction::VedioProcess(void)
{
	//����IplImageָ��
	cv::Mat pFrame;
	cv::Mat gray;
	cv::Mat pFrImg;
	cv::Mat pBkImg;
 
	cv::Mat pFrameMat;
	cv::Mat pFrMat;
	cv::Mat pBkMat;
 
	cv::VideoCapture pCapture;
 
	int nFrmNum = 0;
 
	//��������
	cv::namedWindow("video");
	cv::namedWindow("background",1);
	cv::namedWindow("foreground",1);
	//ʹ������������
	cv::moveWindow("video", 30, 0);
	cv::moveWindow("background", 660, 0);
	cv::moveWindow("foreground", 1290, 0);
 
 
	//������ͷ
	pCapture.open(0);
	if( !pCapture.isOpened() )
    {
		//printf("Can not open camera.\n");
		return -2;
    }
	//��֡��ȡ��Ƶ
	while( 1 )
    {
		pCapture >> pFrame;
		if ( pFrame.empty() ) break;

		nFrmNum++;
		//����ǵ�һ֡����Ҫ�����ڴ棬����ʼ��
		if(nFrmNum == 1)
		{ 
			pFrImg = cv::Mat(pFrame.rows, pFrame.cols, CV_32FC1);
			pBkImg = cv::Mat(pFrame.rows, pFrame.cols, CV_32FC1);
			pBkMat = cv::Mat(pFrame.rows, pFrame.cols, CV_32FC1);
			pFrMat = cv::Mat(pFrame.rows, pFrame.cols, CV_32FC1);
			pFrameMat = cv::Mat(pFrame.rows, pFrame.cols, CV_32FC1);
 
			//ת���ɵ�ͨ��ͼ���ٴ���
			cv::cvtColor(pFrame, pBkImg, CV_BGR2GRAY);
			pBkImg.convertTo(pBkImg, CV_32FC1, 1/255.0);
			cv::cvtColor(pFrame, pFrImg, CV_BGR2GRAY);

			cv::cvtColor(pFrame, pBkMat, CV_BGR2GRAY);
			cv::cvtColor(pFrame, pFrMat, CV_BGR2GRAY);
			cv::cvtColor(pFrame, pFrameMat, CV_BGR2GRAY);
		}
		else
		{
			/*
			**��ִ��ͼ��Ӽ���ʱ��Ӧ�����涨��ʽ��32��8.
			*/

			cv::cvtColor(pFrame, pFrameMat, CV_BGR2GRAY);

			cv::cvtColor(pFrame, pFrImg, CV_BGR2GRAY);
			//pFrImg.convertTo(pFrImg, CV_8U);

			//��˹�˲��ȣ���ƽ��ͼ��
			//cvSmooth(pFrameMat, pFrameMat, CV_GAUSSIAN, 3, 0, 0);
 
			//��ǰ֡������ͼ���
			cv::absdiff(pFrameMat, pBkMat, pFrMat);
 
			//��ֵ��ǰ��ͼ
			cv::threshold(pFrMat, pFrImg, 60, 255.0, CV_THRESH_BINARY);
 
			/*//������̬ѧ�˲���ȥ������  
			//cvErode(pFrImg, pFrImg, 0, 1);
			//cvDilate(pFrImg, pFrImg, 0, 1);
 
			//���±���*/
			cv::accumulateWeighted(pFrameMat, pBkImg, 0.02, pFrImg);
 
			//��ʾͼ��
			cv::imshow("video", pFrame);
			cv::imshow("background", pBkImg);
			cv::imshow("foreground", pFrImg);
 
			//����а����¼���������ѭ��
			//�˵ȴ�ҲΪcvShowImage�����ṩʱ�������ʾ
			//�ȴ�ʱ����Ը���CPU�ٶȵ���
			if( cvWaitKey(1) >= 0 )
				break;
		}
    }
	return 0;
}


int OpenCVFunction::ForeGround(void)
{
	// Open the video file
    cv::VideoCapture capture("E:\\bike.avi");//"E:\\bike.avi"
	// check if video successfully opened
	if (!capture.isOpened())
		return 0;

	// current video frame
	cv::Mat frame; 
	// foreground binary image
	cv::Mat foreground;
	// current video contoursframe
	cv::Mat contoursFrame; 

	cv::namedWindow("Extracted Foreground");

	// The Mixture of Gaussian object
	// used with all default parameters
	cv::BackgroundSubtractorMOG mog;

	bool stop(false);
	// for all frames in video
	while (!stop) {

		// read next frame if any
		if (!capture.read(frame))
			break;

		// update the background
		// and return the foreground
		mog(frame,foreground,0.09);

		// show vedio
		cv::imshow("Extracted Vedio",frame);
		
		// show foreground
		cv::imshow("Extracted Foreground",foreground);

		vector< vector<cv::Point> > contours;
		vector< cv::Vec4i > hierarchy;
		frame.copyTo(contoursFrame);
		cv::threshold(foreground,foreground,128,255,cv::THRESH_BINARY_INV);
		cv::findContours(foreground, contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE);
		int cmin = 10;  
		int cmax = 1000;  
		vector< vector<cv::Point> >::const_iterator itc = contours.begin();  
		while(itc != contours.end())  
		{  
			if(itc->size() < cmin || itc->size() > cmax)  
				itc = contours.erase(itc);  
			else  
				++itc;  
		}
		cv::drawContours(contoursFrame, contours, -1, cv::Scalar(0, 0, 255), 2); 
		cv::imshow("Contours Foreground",contoursFrame);
		/*// Complement the image
		cv::threshold(foreground,foreground,128,255,cv::THRESH_BINARY_INV);

		// show foreground
		cv::imshow("Extracted Foreground",foreground);

		cv::Mat cannyDsc;
		cv::Canny(foreground, cannyDsc, 125, 350);
		// show canny 
		cv::imshow("Canny Foreground",cannyDsc);*/

		// introduce a delay
		// or press key to stop
		if (cv::waitKey(10)>=0)
				stop= true;
	}

	cv::waitKey();

	/*// Create video procesor instance
	VideoProcessor processor;

	// Create background/foreground segmentor 
	BGFGSegmentor segmentor;
	segmentor.setThreshold(25);

	// Open video file
	processor.setInput("E:\\bike.avi");

	// set frame processor
	processor.setFrameProcessor(&segmentor);

	// Declare a window to display the video
	processor.displayOutput("Extracted Foreground");

	// Play the video at the original frame rate
	processor.setDelay(1000./processor.getFrameRate());

	// Start the process
	processor.run();

	cv::waitKey();*/
}
