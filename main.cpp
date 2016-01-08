#include "play.h"
#include <QApplication>
#include<QtGui>
#include<QMediaPlayer>
#include<QFileDialog>
#include<QtWidgets/QDialog>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PlayMedia w;
    w.show();
    return a.exec();
}


