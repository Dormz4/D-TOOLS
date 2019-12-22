#include "fileanalyzewindow.h"
#include "ui_fileanalyzewindow.h"

#include <QFileDialog>


FileAnalyzeWindow::FileAnalyzeWindow(QWidget *parent) :
        QDialog(parent),
        ui(new Ui::FileAnalyzeWindow)
{
    ui->setupUi(this);
    this->setAcceptDrops(true);
    this->setWindowTitle("文件解析");
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
    setBackgroundRole(QPalette::Highlight);

    event->acceptProposedAction();
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
    QString name = event->mimeData()->urls().first().toString();
    ui->textBrowser->setText(name);
}


void FileAnalyzeWindow::on_label_windowIconChanged(const QIcon &icon)
{

}

void FileAnalyzeWindow::on_select_file_clicked()
{
    QString lastPath="C:\Englishpath";
    QString fileName = QFileDialog::getOpenFileName(this, tr("打开文件"), lastPath);
    ui->textBrowser->setText(fileName);
}
