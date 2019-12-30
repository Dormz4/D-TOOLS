#include "Dtools.h"
#include "UI/FileAnalyze/fileanalyzewindow.h"


Dtools::Dtools(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	testClick();
	auto aa = connect(ui.buttonFileAnalyze, SIGNAL(clicked()), this, SLOT(on_FileAnalyze_clicked()));

#ifdef _DEBUG
	on_FileAnalyze_clicked();
#endif
}

void Dtools::on_FileAnalyze_clicked()
{
	FileAnalyzeWindow* fileAnlyzeWindow = new FileAnalyzeWindow(this);
	fileAnlyzeWindow->show();
}

void Dtools::mySlots()
{
	cout << "我感动天感动地" << endl;
}
