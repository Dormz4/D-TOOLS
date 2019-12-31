#include "QtDzSdk.h"
#include <QDebug>


QObject* QtDzSdk::printObjName(QObject* obj)
{
	if (!obj) {
		return NULL;
	}
	QObjectList cs = obj->children();
	qDebug() << obj->objectName()<< ":" << obj->metaObject()->className();
	//qDebug() <<
	qDebug() << "==================";
	if (cs.size() <= 0) {
		return NULL;
	}
	for (int i = 0; i < cs.size(); i++) {
		printObjName(cs[i]);
	}

}
