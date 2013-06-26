/**
 * @file FolderServer.h
 * @brief The FolderServer class will contain all required
 * definitions and basic utilities functions for the synchronization
 * betweeen a client folder and the server or remote
 *
 * @author Alvine AGBO
 * @date 6/07/2013
 * @version 1.0
 */

#ifndef FOLDERSERVER_H
#define FOLDERSERVER_H

#include <QString>
#include <QByteArray>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QFile>
#include <QEventLoop>
#include "../../../../Desktop/Cairnsmith13/CairnSmith/CairnSmith/Server/ClientLib/sheer_cloud.h"
#include <QDir>
#include <QHash>
#include <QList>
#include "FileHash.h"
#include <QtTest/QtTest>
#include <QtTest/QTest>

class FolderServer : public QObject {
    Q_OBJECT

public:
    /**
     * @brief FolderServer
     * Constructor that set the connection to the server
     * This uses SheerCloudLink class to perform all the function
     */
    FolderServer(): link("http://localhost:8080", "abc", "123")
    {
        link.connect( &link, SIGNAL(done()), &loop, SLOT(quit()));
        link.connect( &link, SIGNAL(progress(qint64 , qint64)), this, SLOT(progress_check(qint64 , qint64)));

       m_now = 0;
       m_total = 0;
       m_progress_reports = 0;
    }

    SheerCloudLink link;
    QEventLoop loop;

    qint64 m_now;
    qint64 m_total;
    int m_progress_reports;
    bool renderIsDone;

    /**
     * @brief isCompletedRender
     * This helps to set if the rendering is achieved
     * @return a boolean.
     */
    bool isCompletedRender();

public slots:
    /**
     * @brief loginLink
     * This slot helps to connect to the server
     */
    void loginLink();

    /**
     * @brief uploadFolder
     * This slot helps to send all files and directories from
     * a local folder to the server. The folders' structure is
     * the same at both sides.
     * @param myFolder is the path of the main folder at the client side
     * @param serverPath is the path of the folder at the server side
     */
    bool uploadFolder(QString myFolder, QString serverPath);

    /**
     * @brief progress_check
     * This slot helps to check the progress of the uploading process
     * @param now
     * @param total
     */
    void progress_check(qint64 now, qint64 total);

    /**
     * @brief askRender
     * This slot helps to request a render to the server
     * @param scene is the name of the scene of the rendering
     */
    void askRender(QString scene);

    /**
     * @brief fDragAndDrop
     * When a library is used from the server directory and not exists in
     * the local directory of the user, the library is copy/paste to local
     * @param sLibrary is the used Library
     */
    //void fDragAndDrop(QString sLibrary);

    /**
     * @brief getListFromServer
     * This helps to get the list of files in a folder locate on the server
     * @param sFolder is the QString  path of the folder locate on the remote
     * @param result is the QByteArray of the data received
     */
    void getListFromServer(QString sFolder, QByteArray &result);

    /**
     * @brief getListFileServer
     * This helps to save the file in a local folder
     * @param sFilepath is the filename with the path
     */
    void getListFileServer(QString sFilepath);

    /**
     * @brief listFiles
     * This function helps to build a list of files in a
     * defined folder
     * @param mDir is the name or path of the folder
     * @return the result of this function is a QHash of
     * the name of each file and their MD5 sum
     */
    QHash<QString, QString> listFiles(QString mDir);

    /**
     * @brief compareFileList
     * This function compare the QHash of two list of files
     * @param local is the QHash of files list on local folder
     * @param remote is the QHash of files list on the server folder
     * @return is a QList of the file that are not on the remote or server
     */
    QList<QString> compareFileList(QHash<QString, QString> local, QHash<QString, QString> remote);

    /**
     * @brief saveToUserFolder
     * This function helps to save a file to the user local folder
     * @param filename is the name of the file that will
     * be saved to the local machine
     * @param data is the content of the file that has been retrieve
     * from the remote
     * @return a boolean that helps to know if the file has been
     * successfully saved
     */
    bool saveToUserFolder(QString &filename, QIODevice *data);

private:

    FileHash m_oHashMD5;
    QHash<QString, QString> mylist;
};

#endif // FOLDERSERVER_H
