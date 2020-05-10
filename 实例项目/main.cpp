#include "mainscene.h"
#include "dataconfig.h"

#include <QApplication>
#include <QMap>
#include <QPair>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainScene w;
    w.show();

//    dataConfig config;
//    QMap<int,int*>::iterator iter = config.mData.begin();
//    int * array = iter.value();
//    for(int i =0; i < 16 ; i++){
//        qDebug() << array[i];
//    }

    return a.exec();
}
