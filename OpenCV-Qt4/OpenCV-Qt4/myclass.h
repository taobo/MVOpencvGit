#ifndef MYCLASS_H
#define MYCLASS_H

#include <QtGui/QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include <QLabel>
#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include "ui_myclass.h"
#include "OpenCVFunction.h"
#include <iostream>

class MyClass : public QMainWindow
{
	Q_OBJECT

public:
	MyClass(QWidget *parent = 0, Qt::WFlags flags = 0);
	~MyClass();
	OpenCVFunction OCF;

private:
	Ui::MyClassClass ui;
	cv::Mat image;
	private slots:
		void on_OpenImage_clicked();
		void on_ProcessImage_clicked();
		void on_SliderValue_changed(int value);
public:
	void houghCircles(int value = 25);
	void findContours(void);
};

#endif // MYCLASS_H
