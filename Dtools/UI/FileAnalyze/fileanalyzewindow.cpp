#include "fileanalyzewindow.h"
#include "ui_fileanalyzewindow.h"
#include <QFileDialog>
#include <QDebug>
#include "../../QtDzSdk.h"



#define TAG "FileAnalyzeWindow"

FileAnalyzeWindow::FileAnalyzeWindow(QWidget *parent) :
        QDialog(parent),
        ui(new Ui::FileAnalyzeWindow)
{
    ui->setupUi(this);
    this->setAcceptDrops(true);		//接收拖放文件
    this->setWindowTitle("文件解析");


	//enum the widget and initialize them
	QObjectList childrenList = children();
	for each (QObject *obj in childrenList)
	{
		if (obj->metaObject()->className() == QStringLiteral("QTabWidget")) {
			qDebug() << "命中" << obj->metaObject()->className();
			QLabel* label = new QLabel();
			m_fileAnalyzeShowPlace = (QTabWidget*)obj;
			//((qtabwidget*)obj)->addtab(label, r"(haha)");
		}
	}
	//QString tab2Title = "啊啊啊啊啊";
	m_fileAnalyzeShowPlace->setTabText(1, QStringLiteral("啊"));
	//m_fileAnalyzeShowPlace->setTabWhatsThis(1, tab2Title);

	debugTestFunc();
}

FileAnalyzeWindow::~FileAnalyzeWindow()
{
    delete ui;
}





//开始 elf 的文件修复
void FileAnalyzeWindow::on_FileRepair_clicked()
{

}

void FileAnalyzeWindow::dragEnterEvent(QDragEnterEvent *event)
{
    //    setText(tr("<drop content>"));
    //setBackgroundRole(QPalette::Highlight);
	if (event->mimeData()->hasUrls()) {
		event->acceptProposedAction();
	}
	else
	{	
		qDebug() << "FileAnalyzeWindow dragEnterEvent ignore!";
		event->ignore();
	}
    //    emit changed(event->mimeData());
}

void FileAnalyzeWindow::dragMoveEvent(QDragMoveEvent *event)
{

}

void FileAnalyzeWindow::dragLeaveEvent(QDragLeaveEvent *event)
{

}

void FileAnalyzeWindow::dropEvent(QDropEvent *event)
{
    //	const QMimeData *mimeData = event->mimeData();
	qDebug() << "Hit fileAnalyzeWindow dropEvent";
	
	QList<QUrl> urls = event->mimeData()->urls();

	if (urls.isEmpty()) {
		qDebug() << TAG <<"url is nulling";
		return;
	}
	// Fitter file type
	// reserve!!

	QString name = urls.first().toLocalFile();
	//QString name = event->mimeData->text();


	ui->textBrowser->setText(name);

	qDebug() << TAG << "file name is " << name.toStdString().data();
	QFile file(name);
	if (!file.open(QIODevice::ReadWrite)) {
		qDebug() << TAG << "open file failed";
		return;
	}
	else {
		qDebug() << TAG << "open file success ,file size:" << file.size();
		uchar* fpr = file.map(0, file.size()); //Map files to memory.

		m_elfAnalyze = new ElfAnalyze();
		m_elfAnalyze->AnalyzeElf(fpr);
	}



}

void FileAnalyzeWindow::debugTestFunc()
{
	QtDzSdk::printObjName(this);
	QFile file("F:\\D-Tools\\Dtools\\libdvm.so");
	if (!file.open(QIODevice::ReadWrite)) {
		qDebug() << TAG << "open file failed";
		system("pause");
		exit(-1);
	}
	uchar* fpr = file.map(0, file.size()); //Map files to memory.

	m_elfAnalyze = new ElfAnalyze();
	m_elfAnalyze->AnalyzeElf(fpr);
}



void FileAnalyzeWindow::on_label_windowIconChanged(const QIcon &icon)
{

}

void FileAnalyzeWindow::on_select_file_clicked()
{/*
	QString lastPath="C:\Englishpath";
	QString fileName = QFileDialog::getOpenFileName(this, tr("打开文件"), lastPath);
	ui->textBrowser->setText(fileName);*/
}
