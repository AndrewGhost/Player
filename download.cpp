#include "download.h"
#include <QUrl>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkAccessManager>
#include <QFile>
#include <QTextStream>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonParseError>
#include <QMediaPlayer>
#include <QList>
#include <Python.h>
#include <iostream>
using namespace std;
#define  MP3_URL       "http://lib9.service.kugou.com/websearch/index.php?"
#define  urLPrefix       "http://trackercdn.kugou.com/i/?"
int mp3Num=60;//获取的音乐数量
int currentNum=0;//当前已有数量
DownLaod::DownLaod(QObject *parent):
    QObject(parent)
{
    manager = new QNetworkAccessManager(this);
    managerSingle = new QNetworkAccessManager(this);
    HashManager = new QNetworkAccessManager(this);
}
void DownLaod::do_download(QTableWidget *fromSearchTable, QList<QString> *fromRealList, QString searhText)
{
    pointToSearchTable=fromSearchTable;//指向searchTable(位于mainwindow.h)
    netList=fromRealList;
    netList->clear();
    rowIndex=0;
    //设置发送的数据
    QByteArray byte_array;
    byte_array.append("page=1");
    byte_array.append("&keyword="+searhText);
    byte_array.append("&cmd=100");
    byte_array.append("&pagesize="+QString::number(mp3Num,10));
    QString url = MP3_URL + QString(byte_array);
    QNetworkRequest *network_request = new QNetworkRequest();
    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));
    connect(managerSingle, SIGNAL(finished(QNetworkReply*)), this, SLOT(replySingsong(QNetworkReply*)));
    connect(HashManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(hashTrans(QNetworkReply*)));
    network_request->setUrl(url);
    manager->get(*network_request);

}
QString DownLaod::python(QString songInfo){

     Py_Initialize();
     // 检查初始化是否成功
     if (!Py_IsInitialized())
     {
         return NULL;
     }
     PyObject * pModule = NULL;//声明变量
     PyObject * pFunc = NULL;// 声明变量
     PyObject * pArgs = NULL;// 声明变量
     PyObject * result = NULL;// 声明变量张国荣
     qDebug()<<"444";
     pModule =PyImport_ImportModule("lrc");//这里是要调用的文件名
     qDebug()<<"333";
     if(pModule==NULL)
      qDebug()<<"null";
     pFunc= PyObject_GetAttrString(pModule, "getLrc");//这里是要调用的函数名
     if(pFunc)
     qDebug()<<"lrc下载成功";
     //参数进栈
     pArgs=PyTuple_New(1);
     string searchInfo=songInfo.toStdString();
     const char* ss=searchInfo.data();

     qDebug()<<ss;
     PyTuple_SetItem(pArgs, 0, Py_BuildValue("s",ss));
     result=PyEval_CallObject(pFunc, pArgs);//调用函数
     //c用来保存c/c++类型的返回值
     char *lrccontent=NULL;
     //将python类型的返回值转换为c/c++类型
     PyArg_Parse(result, "s", &lrccontent);
     QString returnLrc(lrccontent);
     Py_DECREF(pModule);
     // cleanup
     Py_DECREF(pFunc);
     Py_DECREF(pArgs);
     Py_Finalize();//调用Py_Finalize，这个根Py_Initialize相对应的。
     return returnLrc;
}

void DownLaod::replyFinished(QNetworkReply *reply)
{
    //获取响应的信息，状态码为200表示正常
    QVariant status_code = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
    //无错误返回
    if(reply->error() == QNetworkReply::NoError)
     {
        QByteArray bytes = reply->readAll();  //获取字节
        QString result(bytes);  //转化为字符串

        pointToSearchTable->setRowCount(mp3Num);//一共多少行

        parseJson(result);  //自定义方法，解析歌曲数据

     }

    else
    {
        qDebug()<<"error";
        qDebug()<<reply->errorString();
        //处理错误
    }
    reply->deleteLater();//按照程序进程删除该对象，防止内存泄露
}

void DownLaod::replySingsong(QNetworkReply *reply)
{
    if(reply->error()!= QNetworkReply::NoError)
    return;
    QByteArray addr_bytes=reply->readAll();
    QJsonParseError json_error;
    QJsonDocument parse_doucment = QJsonDocument::fromJson(addr_bytes, &json_error);
    if(parse_doucment.isObject())
    {
        QJsonObject obj=parse_doucment.object();//获取一个jsonobject
        QJsonValue  urlvalue=obj.take("url");//
        //qDebug()<<"obj"<<obj; //输出获得的歌曲信息
        if(urlvalue.toString().isEmpty())
        return;
        //写入table
        pointToSearchTable->setItem(rowIndex,0,new QTableWidgetItem(QString::number(rowIndex+1,10)));//序号
        QJsonValue  namevalue=obj.take("fileName");//

        QString     filename=namevalue.toString();
        int  _pos=filename.indexOf("-");
        if(_pos==-1)
         return;
        netList->append(urlvalue.toString());//存入mp3地址
        QString artist=filename.mid(0,_pos);
        QString songname=filename.mid(_pos+1,filename.length());
        pointToSearchTable->setItem(rowIndex,1,new QTableWidgetItem(songname));
        pointToSearchTable->setItem(rowIndex,2,new QTableWidgetItem(artist));
       //pointToSearchTable->setItem(rowIndex,3,new QTableWidgetItem("未知专辑"));
        QJsonValue  timevalue=obj.take("timeLength");//
        //-------时间化为0:00的形式
        int  musictime=timevalue.toInt();
        int sec=musictime%60;
        int min=musictime/60;
        QString minset=QString::number(min,10);
        QString secset=QString::number(sec,10);
        if(sec<10)
        secset="0"+secset;
        QString timeToStr=minset+":"+ secset;
        //------------------------
        pointToSearchTable->setItem(rowIndex++,3,new QTableWidgetItem(timeToStr));

    }//if

}

void DownLaod::hashTrans(QNetworkReply *reply)
{
    QByteArray addr_bytes=reply->readAll();
    QString patternKey("this.select(.*)class=\"input");
    QRegExp rxkey(patternKey);
    QString resul(addr_bytes);
    int pos=resul.indexOf(rxkey);
    int length=rxkey.matchedLength();
    QString contain_addr=resul.mid(pos,length);//子串
    int s=contain_addr.indexOf("e=");
    int e=contain_addr.indexOf("cla");
    QString key=contain_addr.mid(s+3,e-s-5);

    QString patternHash("id=\"q(.*)class=\"input");
    QRegExp rxHash(patternHash);
    QString hashPart(addr_bytes);
    pos=hashPart.indexOf(rxHash);
    length=rxHash.matchedLength();
    contain_addr=hashPart.mid(pos,length);//子串
    s=contain_addr.indexOf("e=");
    e=contain_addr.indexOf("cla");
    globalHash=contain_addr.mid(s+3,e-s-5);
    globalHash=globalHash.mid(0,globalHash.indexOf("kg"));


    //拼接单个url
    QByteArray byte_array;
    byte_array.append("key="+key);//加密后的key &cmd=4&acceptMp3=1
    byte_array.append("&cmd=4");
    byte_array.append("&acceptMp3=1");
    byte_array.append("&hash="+globalHash);
    byte_array.append("&pid=1");
    //寻找single music
    QString singurl = urLPrefix+QString(byte_array);
    managerSingle->get(QNetworkRequest(singurl));
}

void DownLaod::parseJson(QString json)
{

    QByteArray byte_array;
    QJsonParseError json_error;
    QJsonDocument parse_doucment = QJsonDocument::fromJson(byte_array.append(json), &json_error);

    if(json_error.error == QJsonParseError::NoError)
    {
        qDebug()<<"Connect successfully";
       if(parse_doucment.isObject())
       {
          QJsonObject obj=parse_doucment.object();//获取一个jsonobject
          if(obj.contains("data"))
           {
              QJsonValue name_value = obj.take("data");//查看代码发现是一个数组
              obj=name_value.toObject();
              QJsonValue value=obj.take("songs");
              QJsonArray array=value.toArray();

              for(int i=0;i<array.size();i++)
              {
                  obj=array.at(i).toObject();
                  QString hashUrl="http://tool.chinaz.com/Tools/MD5.aspx?q=";
                  QJsonValue hash=obj.take("hash");//取得mp3 hash值,之后用md5解密              

                  //去转换url
                  hashUrl+=hash.toString()+"kgcloud&md5type=1";//去找mp3位置
                  HashManager->get(QNetworkRequest(hashUrl));
              }
           }

       }//isobject

    }
}
