#include "myclass.h"

MyClass::MyClass(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);
}

MyClass::~MyClass()
{

}

void MyClass::houghCircles(int value)
{
	cv::Mat imgPrint = image;
	cv::Mat imgGray;
	imgGray = OCF.getGrayImage(image);
	unsigned int threshold = OCF.Otsu(imgGray, imgGray.cols, imgGray.rows, imgGray.step);
	if ( true == OCF.Threshold(imgGray, imgGray.cols, imgGray.rows, imgGray.step, 185) ){

		cv::namedWindow("Threshold Image", CV_WINDOW_AUTOSIZE);   
		cv::imshow("Threshold Image", imgGray); 

	cv::GaussianBlur(imgGray, imgGray, cv::Size(5, 5), 1.5);
	std::vector<cv::Vec3f> circles;
	cv::HoughCircles(imgGray, circles, CV_HOUGH_GRADIENT, 2, 50, 200, 100, 25, 100);//累加器的分辨率（图像尺寸/2）,两圆之间最小距离，高阀值，最小投票数，极小大半径。
	std::vector<cv::Vec3f>::const_iterator itc = circles.begin();
	while( itc != circles.end() )
	{
		cv::circle(imgPrint, cv::Point((*itc)[0], (*itc)[1]), (*itc)[2], cv::Scalar(0, 0 , 255), 2);
		cv::circle(imgGray, cv::Point((*itc)[0], (*itc)[1]), (*itc)[2], cv::Scalar(255), 2);
		++itc;
	}
	
	cv::imwrite("HoughCircles.jpg", imgPrint);
	QImage *img = new QImage;
	img->load("HoughCircles.jpg");
	ui.Process->setPixmap(QPixmap::fromImage(*img));
	ui.Process->resize(ui.Process->pixmap()->size());
	ui.Process->show();

	}
	cv::namedWindow("Gray Image");
	cv::imshow("Gray Image", imgGray);
}

void MyClass::findContours(void)
{
	cv::Mat src = OCF.getGrayImage(image);   
    cv::Mat dsc,cannyDsc;
	dsc.create(src.rows, src.cols, src.type());
	src.copyTo(dsc);

	cv::Canny(image, cannyDsc, 125, 350);
	cv::namedWindow("Canny Image");   
	cv::imshow("Canny Image", cannyDsc); 

	unsigned int threshold = OCF.Otsu(src, src.cols, src.rows, src.step);   
	//QMessageBox::about(NULL, "Value", QString::number(threshold, 10));
    // 图像二值化   
	if ( true == OCF.Threshold(src, src.cols, src.rows, src.step, 100) )   
    {   
        cv::namedWindow("Threshold Image", CV_WINDOW_AUTOSIZE);   
		cv::imshow("Threshold Image", src);   
        OCF.FindContours(src, src.cols, src.rows, src.step);   
        cv::namedWindow("FindContours Image", CV_WINDOW_AUTOSIZE);   
		cv::imshow("FindContours Image", src);         
    }
}

void MyClass::on_OpenImage_clicked()  
{  
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Image"), ".", tr("Image Files (*.png *.jpg *.jpeg *.bmp)")); 
    image = cv::imread(fileName.toAscii().data());
	cv::cvtColor(image, image, CV_RGB2RGBA);
	QImage img = QImage((const unsigned char*)(image.data), image.cols, image.rows, QImage::Format_RGB32);
	ui.Original->setPixmap(QPixmap::fromImage(img));
	ui.Original->resize(ui.Original->pixmap()->size());
	ui.Original->show();
} 

void MyClass::on_ProcessImage_clicked()  
{  
	//findContours();
	//houghCircles();
	//OCF.VedioProcess();
	OCF.ForeGround();
    
}



void MyClass::on_SliderValue_changed(int value)
{
	houghCircles(ui.horizontalSlider->value());
}

