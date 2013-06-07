#ifndef FOLDERSERVER_H
#define FOLDERSERVER_H

#include <QString>
#include <QByteArray>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QFile>
#include <QEventLoop>
#include "../../../../Desktop/Cairnsmith13/CairnSmith/CairnSmith/Server/ClientLib/sheer_cloud.h"

class FolderServer : public QObject {
    Q_OBJECT

public:
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

public slots:
    void loginLink();
    void uploadFolder(QString myFolder, QString serverPath);
    void progress_check(qint64 now, qint64 total);

};

#endif // FOLDERSERVER_H
