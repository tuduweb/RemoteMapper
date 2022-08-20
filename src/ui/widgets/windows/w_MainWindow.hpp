#pragma once

#include "ui_w_MainWindow.h"

#include <QMainWindow>
#include <QTextDocument>

#include "base/interface/DeviceInterface.hpp"

class MainWindow
	: public QMainWindow
	, Ui::MainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget* parent = Q_NULLPTR);
	~MainWindow() override {};

protected slots:
	void on_remotes_btn_clicked();
	void on_remoteStart_btn_clicked();

protected:
	//void initUIVideo();
	DeviceInterface* _device = nullptr;
};
