#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

private slots:
	void on_radioButton_Cardinal_clicked(bool checked);

	void on_radioButton_Linear_clicked(bool checked);

	void on_radioButton_Cubic_clicked(bool checked);

	void on_radioButton_Line_clicked(bool checked);

	void on_radioButton_Track_clicked(bool checked);

	void on_radioButton_Road_clicked(bool checked);

	void on_actionLoad_Path_triggered();

	void on_actionSave_Path_triggered();

	void on_pushButton_Play_clicked();

private:
	Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
