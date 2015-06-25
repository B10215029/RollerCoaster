#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QSound>

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	//connect(ui->openGLWidget, SIGNAL(getLastFPS(QString)), ui->statusBar, SLOT(showMessage(QString)));
	connect(ui->openGLWidget, SIGNAL(getLastFPS(QString)), ui->label, SLOT(setText(QString)));
	ui->listWidget->insertItem(0, QString("X"));
	for(int i=0;i<ui->openGLWidget->track.controlPoints.size();++i)
		ui->listWidget->insertItem(i+1, QString::number(i+1));
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::on_radioButton_Linear_clicked(bool checked)
{
	if(checked){
		ui->openGLWidget->track.curveType = Track::LinearType;
		ui->openGLWidget->track.update();
	}
}

void MainWindow::on_radioButton_Cardinal_clicked(bool checked)
{
	if(checked){
		ui->openGLWidget->track.curveType = Track::CardinalType;
		ui->openGLWidget->track.update();
	}
}

void MainWindow::on_radioButton_Cubic_clicked(bool checked)
{
	if(checked){
		ui->openGLWidget->track.curveType = Track::CubicType;
		ui->openGLWidget->track.update();
	}
}

void MainWindow::on_radioButton_Line_clicked(bool checked)
{
	if(checked){
		ui->openGLWidget->track.trackType = Track::LineType;
		ui->openGLWidget->track.update();
	}
}

void MainWindow::on_radioButton_Track_clicked(bool checked)
{
	if(checked){
		ui->openGLWidget->track.trackType = Track::TrackType;
		ui->openGLWidget->track.update();
	}
}

void MainWindow::on_radioButton_Road_clicked(bool checked)
{
	if(checked){
		ui->openGLWidget->track.trackType = Track::RoadType;
		ui->openGLWidget->track.update();
	}
}

void MainWindow::on_actionLoad_Path_triggered()
{
	QString filePath = QFileDialog::getOpenFileName(this, "Load Path", "../", "Text(*.txt);;All(*)");
	ui->openGLWidget->track.loadFile(filePath);
	ui->listWidget->clear();
	ui->listWidget->insertItem(0, QString("X"));
	for(int i=0;i<ui->openGLWidget->track.controlPoints.size();++i)
		ui->listWidget->insertItem(i+1, QString::number(i+1));
}

void MainWindow::on_actionSave_Path_triggered()
{
	QString filePath = QFileDialog::getSaveFileName(this, "Save Path", "../");
	ui->openGLWidget->track.saveFile(filePath);
}

void MainWindow::on_pushButton_Play_clicked()
{
	ui->openGLWidget->track.driving = !ui->openGLWidget->track.driving;
}

void MainWindow::on_actionLine_triggered(bool checked)
{
	ui->openGLWidget->isLine = checked;
}

void MainWindow::on_pushButton_Add_clicked()
{
	ui->openGLWidget->track.addPoint();
	ui->openGLWidget->track.update();
	ui->listWidget->clear();
	ui->listWidget->insertItem(0, QString("X"));
	for(int i=0;i<ui->openGLWidget->track.controlPoints.size();++i)
		ui->listWidget->insertItem(i+1, QString::number(i+1));
	ui->openGLWidget->select(ui->openGLWidget->track.controlPoints.size()-1);
	QSound::play("C:/Users/Delin/Desktop/RollerCoaster/sounds/add.wav");
}

void MainWindow::on_pushButton_Delete_clicked()
{
	if(ui->listWidget->selectedItems().size()>0&&ui->listWidget->selectedItems()[0]->text()!="X")
		ui->openGLWidget->track.removePoint(ui->listWidget->selectedItems()[0]->text().toInt()-1);
	else
		ui->openGLWidget->track.removePoint(-1);
	ui->openGLWidget->track.update();
	ui->listWidget->clear();
	ui->listWidget->insertItem(0, QString("X"));
	for(int i=0;i<ui->openGLWidget->track.controlPoints.size();++i)
		ui->listWidget->insertItem(i+1, QString::number(i+1));
	ui->openGLWidget->selectCP = -1;
	QSound::play("C:/Users/Delin/Desktop/RollerCoaster/sounds/delete.wav");
}

void MainWindow::on_comboBox_activated(int index)
{
	ui->openGLWidget->effectMode = index;
}

void MainWindow::on_listWidget_itemClicked(QListWidgetItem *item)
{
	ui->openGLWidget->select(item->text().toInt()-1);
	QSound::play("C:/Users/Delin/Desktop/RollerCoaster/sounds/select.wav");
}

void MainWindow::on_actionChang_sky_triggered()
{
	ui->openGLWidget->nowSkyTexture = (ui->openGLWidget->nowSkyTexture+1)%ui->openGLWidget->skyTexture.size();
}

void MainWindow::on_actionTrainView_triggered()
{
	if(ui->openGLWidget->mainCamera == &ui->openGLWidget->worldCamera)
		ui->openGLWidget->mainCamera = &ui->openGLWidget->trainCamera;
	else
		ui->openGLWidget->mainCamera = &ui->openGLWidget->worldCamera;
}

void MainWindow::on_horizontalSlider_valueChanged(int value)
{
	ui->openGLWidget->track.trainSpeed = value;
}

void MainWindow::on_comboBox_2_activated(int index)
{
	if(ui->openGLWidget->track.trains[index]->parent)
		ui->openGLWidget->track.trains[index]->deleteParent();
	else
		ui->openGLWidget->track.setChild(ui->openGLWidget->track.trains[index]);
}
