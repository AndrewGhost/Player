#ifndef DOWNLOAD_H
#define DOWNLOAD_H
#include <QObject>
#include <QtNetwork/QNetworkAccessManager>
#include <QDebug>
#include <QTableWidget>
class DownLaod : public QObject
{
    Q_OBJECT
public:
    explicit DownLaod(QObject *parent = 0);
    //声明下载函数
    void do_download(QTableWidget *, QList<QString> *, QString);
    void parseJson(QString);
    QString python(QString songInfo);
signals:

public slots:
    //槽函数声明
    void replyFinished(QNetworkReply* reply);
    void replySingsong(QNetworkReply* reply);
    void hashTrans(QNetworkReply* reply);//hash值加密
private:
    //QNetworkAccessManager类允许应用发送互联网请求并且接收其回复信息
    QNetworkAccessManager *manager;
    QNetworkAccessManager *managerSingle;
    QNetworkAccessManager *HashManager;
    QList<QString> *netList;
    QString globalHash;
    //QList<QMap<QString,QString> > *musicMapList;//存放每个音乐的全部信息map
    QTableWidget *pointToSearchTable;//指向主窗体中的searchTable,当读取了网络音乐后，写入table
    int rowIndex=0;
};

#endif // DOWNLOAD_H

