#ifndef FILEANALYZEWINDOW_H
#define FILEANALYZEWINDOW_H

#include <QDialog>
#include <QLabel>
#include <QDragEnterEvent>
//#include <QUrl>
#include <QMimeData>

namespace Ui {
class FileAnalyzeWindow;
}

class FileAnalyzeWindow : public QDialog
{
    Q_OBJECT

public:
    explicit FileAnalyzeWindow(QWidget *parent = nullptr);
    ~FileAnalyzeWindow();

private slots:
    void on_FileRepair_clicked();

    void on_label_windowIconChanged(const QIcon &icon);

    void on_select_file_clicked();

protected:
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dragMoveEvent(QDragMoveEvent *event) override;
    void dragLeaveEvent(QDragLeaveEvent *event) override;
    void dropEvent(QDropEvent *event) override;
private:
    Ui::FileAnalyzeWindow *ui;
private:
    QLabel *label;
};

#endif // FILEANALYZEWINDOW_H
