#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Dtools.h"

class Dtools : public QMainWindow
{
	Q_OBJECT

public:
	Dtools(QWidget *parent = Q_NULLPTR);

public slots:
	void on_FileAnalyze_clicked();

private:
	Ui::DtoolsClass ui;
};
