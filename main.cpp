#include <QApplication>
#include "FolderServer.h"
#include <QDebug>
#include "Dialog.h"


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    FolderServer myFolder;
    //myFolder.uploadFolder("C:/Users/sheerServer/Cairnsmith/abc", "");
    //Dialog myDial;
    //myDial.show();
    //QByteArray result;
    //myFolder.getListFromServer("very/huge", result);
    myFolder.askRender("very/not_needed/scene.txt");

    qDebug() << "IsRender done? :" << myFolder.isCompletedRender();
    return app.exec();
}
