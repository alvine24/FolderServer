#include "FolderServer.h"
#include <QDir>

void FolderServer::loginLink(){
    link.Authorize();
    loop.exec();
}

void FolderServer::uploadFolder(QString myFolder, QString serverPath){
    QDir dir(myFolder);
    QFileInfoList list = dir.entryInfoList(QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot);
    foreach(QFileInfo finfo, list){
        if(!finfo.isDir()){ //it's a file; upload to server
            QFile *file = new QFile(finfo.absoluteFilePath());
            file->open(QIODevice::ReadOnly);
            QByteArray massive = file->readAll();
            //loginLink();
            link.Upload(serverPath+"/"+finfo.fileName(), massive);
            loop.exec();
        }else
            uploadFolder(finfo.absoluteFilePath(), serverPath + "/" + finfo.fileName());
    }
}

void FolderServer::progress_check(qint64 now, qint64 total){
    m_now = now;
    m_total = total;
    m_progress_reports++;
}
