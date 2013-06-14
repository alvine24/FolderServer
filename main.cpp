#include <QApplication>
#include "FolderServer.h"
#include <QDebug>


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    FolderServer myFolder;
    //myFolder.uploadFolder("C:/Users/sheerServer/Cairnsmith/abc", "");
    QByteArray result;
    myFolder.getListFromServer("very/much", result);

    return app.exec();
}
