#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Dtools.h"
#include <iostream>

using namespace std;


class Dtools : public QMainWindow
{
	Q_OBJECT

public:
	Dtools(QWidget *parent = Q_NULLPTR);


signals:
	void testClick();

public slots:
	void on_FileAnalyze_clicked();
	void mySlots();

private:
	Ui::DtoolsClass ui;
};
