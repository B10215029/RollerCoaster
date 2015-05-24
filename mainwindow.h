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

	void on_actionLine_triggered(bool checked);

	void on_pushButton_Add_clicked();

	void on_pushButton_Delete_clicked();

	void on_comboBox_activated(int index);

private:
	Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
