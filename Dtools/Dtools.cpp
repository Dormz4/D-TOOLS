#include "Dtools.h"
#include "UI/FileAnalyze/fileanalyzewindow.h"

Dtools::Dtools(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	connect(ui.FileAnalyze, SIGNAL(click()), this, SLOT(on_FileAnalyze_clicked()));
}

void Dtools::on_FileAnalyze_clicked()
{
	FileAnalyzeWindow* fileAnlyzeWindow = new FileAnalyzeWindow(this);
	fileAnlyzeWindow->show();
}

