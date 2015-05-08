#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	//connect(ui->openGLWidget, SIGNAL(getLastFPS(QString)), ui->statusBar, SLOT(showMessage(QString)));
	connect(ui->openGLWidget, SIGNAL(getLastFPS(QString)), ui->label, SLOT(setText(QString)));
}

MainWindow::~MainWindow()
{
	delete ui;
}
