#include "Dtools.h"
#include <QtWidgets/QApplication>
#include <QTextCodec>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Dtools w;
	w.show();
	QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
	return a.exec();
}
