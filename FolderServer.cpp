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
    QString myTempPath = QDir::tempPath(); //here we set the folder in which server's files will be saved
    QFile myFile(myTempPath+'/'+sFilepath);
    qDebug() << "le chemin : " << myTempPath+'/'+sFilepath;
    myFile.open(QIODevice::WriteOnly);
    myFile.write(result);
    myFile.close();
}

QHash<QString, QString> FolderServer::listFiles(QString mDir){
    QDir dir(mDir);
    QFileInfoList list = dir.entryInfoList(QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot);
    foreach(QFileInfo finfo, list) {
        //qDebug() << finfo.absoluteDir().dirName()+"/"+finfo.fileName() << endl;
        if (finfo.isDir()) {
            listFiles(finfo.absoluteFilePath());
        } else {
            //Calcul MD5 and store in a QHash
            QString m_sResValCryptoMD5;
            m_oHashMD5.SetInFile(finfo.absoluteFilePath());
            m_oHashMD5.SetOutFile("C:/Data/OutFile");
            m_oHashMD5.CalculateCryptoMD5();
            if(m_oHashMD5.IsOk() == true){
                m_sResValCryptoMD5 = m_oHashMD5.GetResCryptoMD5();
                mylist.insert(m_sResValCryptoMD5,finfo.absoluteDir().dirName()+"/"+finfo.fileName());
            }
        }
    }
    return mylist;
}

QList<QString> FolderServer::compareFileList(QHash<QString, QString> local, QHash<QString, QString> remote){
    QString key;
    QList<QString> result;
    foreach(key, local.keys()){
        if(!remote.contains(key) || remote[key] != local[key]){
            result.append(local[key]);
        }
    }
    return result;
}

bool FolderServer::saveToUserFolder(QString &filename, QIODevice *data){
    QFile file(filename);
    if(!file.open(QIODevice::WriteOnly)){
        return false;
    }
    file.write(data->readAll()); //here we can use QFile::copy(const QString & fileName, const QString & newName) if used of local folder
    file.close();

    return true;
}
