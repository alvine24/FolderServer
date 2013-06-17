#include "FolderServer.h"
#include <QDir>
#include <QDebug>

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

void FolderServer::askRender(QString scene){
    //if the file named scene exists
    QFile sceneFile(scene);
    if(sceneFile.exists()){
        sceneFile.open(QIODevice::ReadOnly);
        QByteArray massive = sceneFile.readAll();
        link.Upload(sceneFile.fileName(), massive);
        loop.exec();
        //If the rendering is OK
        renderIsDone = link.Authorized();
    }
}

bool FolderServer::isCompletedRender(){
    return renderIsDone;
}

void FolderServer::getListFromServer(QString sFolder, QByteArray &result){
    loginLink();
    link.List(sFolder, result);
    loop.exec();
    QString myResult = result.data();
    QStringList list = myResult.split("\n");
    foreach(QString s, list){
        if(s.contains('/')){
            qDebug() << "Ici on a : " << s;
            getListFileServer(s);
        }
    }
}

void FolderServer::getListFileServer(QString sFilepath){
    QByteArray result;
    link.Download(sFilepath, result);
    //save result into temp folder
    QString myTempPath = QDir::tempPath();
    QFile myFile(myTempPath+'/'+sFilepath);
    qDebug() << "le chemin : " << myTempPath+'/'+sFilepath;
    myFile.open(QIODevice::WriteOnly);
    myFile.write(result);
    myFile.close();
}
