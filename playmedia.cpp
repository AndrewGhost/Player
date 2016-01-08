#include<QtGui>
#include<QtWidgets/QDialog>
#include<QFileDialog>
#include<QMessageBox>
#include<QMenu>
#include "play.h"
#include <QPixmap>
#include <QScrollBar>
#include <QSlider>
#include <QSplitter>
#include <QMediaPlayer>
#include <QNetworkReply>
#include<QMediaMetaData>
#include <string>
#include<QTime>
#include <cstdlib>
#include <QMediaPlaylist>
#include<ctime>
#include<QTimer>
#include "SearchButton.h"
#include "download.h"
#include "no_focus_delegate.h"//去掉table选取虚线
#include <QDebug>
#include<iostream>
using namespace std;
int playnum=1;
int id=0;
int totaltime;
QFileInfo playfile;
QSlider *slider;
QMediaPlayer *player;
QLabel *current_time_label;
QLabel *whole_time_label;
bool isrand=false;
bool isloop=false;
bool delIsPlaying=false;
bool isfirstClicked=true;
QTimer *timer=new QTimer();
QList<QString > *searchedMusicList;//获取的网络音乐
DownLaod download;//只创建一次
QMap<int,QString> m_map; //定义一个QMap对象,容纳歌词
PlayMedia::PlayMedia(QWidget *parent):
    QDialog(parent)
{
    setupUi(this);
    SearchButton *search_button=new SearchButton("搜索",search_line_edit);

    searchframe->setVisible(false);
   //----网络音乐表
    QHeaderView* headerView = searchTable->verticalHeader();//隐藏行号
    headerView->setHidden(true);

    searchTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    searchTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    searchTable->setShowGrid(false);
    searchTable->horizontalHeader()->setSectionsClickable(false);//设置表头不可点击（默认点击后进行排序）
    searchTable->setItemDelegate(new NoFocusDelegate(searchTable));
    searchTable->horizontalHeader()->resizeSection(0,30); //设置表头第一列的宽度为50
    searchTable->horizontalHeader()->resizeSection(1,270);
    searchTable->horizontalHeader()->resizeSection(2,170);
    searchTable->horizontalHeader()->setStretchLastSection(true); //设置充满表宽度
   //------搜索框
    search_line_edit->installEventFilter(this);  //在窗体上为search_line_edit安装过滤器
    search_line_edit->installEventFilter(searchTable);
    search_line_edit->setPlaceholderText("搜索你的最爱");
   //------------
    srand((unsigned)time(0));//歌词流动
    timer->setInterval(4000);

    slider=new  QSlider(Qt::Horizontal);

    //初始播放列表
    player=new  QMediaPlayer(this);
    localplayList=new QMediaPlaylist(this);//本地列表
    webplayList=new QMediaPlaylist(this);//网络列表
    searchedMusicList=new QList<QString >;
    playList=localplayList;
    player->setPlaylist(playList);//默认为本地列表

    //设置背景图片
    QPixmap pixmap(":/wallpaper/source/wall.jpg");
    QPalette palette;
    palette.setBrush(this->backgroundRole(),QBrush(pixmap));
    setPalette(palette);
    setAutoFillBackground(true);

    //一句话啊，设置透明，好久才想到
     listwidget->setStyleSheet("background-color:transparent");
     lrctext->setStyleSheet("background-color:transparent");
     lrctext->setTextColor(QColor(25, 20, 55));
    //让QLabel自适应text的大小，直接用下面的代码：
    //labelsong->adjustSize();
    //让QLabel能够自动判断并换行显示：
    //labelsong->setGeometry(QRect(328, 240, 329, 27*4));  //四倍行距
    labelsong->setWordWrap(true);
    setWindowFlags(Qt::WindowMinimizeButtonHint|Qt::WindowCloseButtonHint);
    setFixedSize(907,630);

    QFile file(":/scroll/scrollbar.qss");//设置滚条样式
    file.open(QFile::ReadOnly);
    listwidget->verticalScrollBar()-> setStyleSheet(file.readAll());

    slider->setMinimum(0);
    current_time_label=new QLabel("0:00");
    whole_time_label=new QLabel("0:00");
    progressLayout->addWidget(current_time_label);
    progressLayout->addWidget(slider);
    progressLayout->addWidget(whole_time_label);
    createAction();
    connect(playButton,SIGNAL(clicked()),this,SLOT(playmusic()));
    connect(stopButton,SIGNAL(clicked()),this,SLOT(stopmusic()));
    connect(lastButton,SIGNAL(clicked()),this,SLOT(lastmusic()));
    connect(nextButton,SIGNAL(clicked()),this,SLOT(nextmusic()));
   // connect(openFileButton,SIGNAL(clicked()),this,SLOT(addlist()));
    connect(listwidget,SIGNAL(itemDoubleClicked(QListWidgetItem* )),this,SLOT(clickItem(QListWidgetItem* )));
    connect(player, SIGNAL(metaDataChanged()), this, SLOT(getInformation()));
    connect(player, SIGNAL(durationChanged(qint64)), this, SLOT(durationChanged(qint64)));
    connect(player, SIGNAL(positionChanged(qint64)), this, SLOT(positionChanged(qint64)));
    connect(voiceSlider,SIGNAL(valueChanged(int)),this,SLOT(setVoice()));
    connect(slider,SIGNAL(sliderMoved(int)), this, SLOT(setPositon(int)));
    connect(deleteButton,SIGNAL(clicked()), this, SLOT(deleteFile()));
    connect(timer,SIGNAL(timeout()),this,SLOT(showLrc()));
    connect(soundButton,SIGNAL(clicked()),this,SLOT(silent()));
    connect(search_button,SIGNAL(clicked()),this,SLOT(changePage()));
    connect(musicPageBtn,SIGNAL(clicked()),this,SLOT(toMusicPage()));
    connect(lrcPageBtn,SIGNAL(clicked()),this,SLOT(toLrcPage()));
    connect(searchTable,SIGNAL(itemDoubleClicked(QTableWidgetItem*)),this,SLOT(clickTableItem(QTableWidgetItem*)));

}

void PlayMedia::showEvent(QShowEvent *event){ //2015/12/30
    QFile f(".//recentPlay//localm.log");
    if(!f.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        cout << "Open localm.log failed." << endl;
        return;
    }
    QTextStream txtInput(&f);
    QString     linestr;
    QFont font;//字体
    font.setPixelSize(17);
    font.setBold(true);
    while(!txtInput.atEnd()){

        linestr=txtInput.readLine();
        int divide_pos=linestr.indexOf('#');
        QString songName=linestr.mid(0,divide_pos);
        QString songPath=linestr.mid(divide_pos+1);
        QListWidgetItem *musicitem=new QListWidgetItem(songName);
        name_path_map.insert(songName,songPath);
        localplayList->addMedia(QUrl::fromLocalFile(songPath));
        musicitem->setTextColor(QColor(19, 100, 255));
        musicitem->setFont(font);
        listwidget->addItem(musicitem);

  }//
    event->accept();
}
void PlayMedia::closeEvent(QCloseEvent *event)//窗口关闭事件
{
    QMessageBox::StandardButton button;
    button = QMessageBox::question(this, tr("退出程序"),
        QString(tr("是否关闭程序?")),
        QMessageBox::Yes | QMessageBox::No);

    if (button == QMessageBox::No) {
        event->ignore();  //忽略退出信号，程序继续运行
    }
    else if (button == QMessageBox::Yes) {
        QFile f(".//recentPlay//localm.log");
        if(!f.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            cout << "Open localm.log failed." << endl;
            return;
        }
        QTextStream txtInput(&f);
        int listSize=listwidget->count();
        int i=0;       
        while(i<listSize){
           QString tempItem=listwidget->item(i)->text();
           txtInput<<tempItem<<"#"<<name_path_map[tempItem]<<endl;
            i++;
        }
        f.close();
        event->accept();  //接受退出信号，程序退出
    }
}
bool PlayMedia::eventFilter(QObject *watched, QEvent *event)
{
    if (watched==search_line_edit)         //首先判断控件(这里指 search_line_edit)
       {
            if (event->type()==QEvent::FocusIn)     //然后再判断控件的具体事件 (这里指获得焦点事件)
            {
                search_line_edit->setPlaceholderText("");

                search_line_edit->setFocus ();

            }
            else if (event->type()==QEvent::FocusOut)    // 这里指 search_line_edit 控件的失去焦点事件
            {
               search_line_edit->clearFocus();
               search_line_edit->setPlaceholderText("搜索你的最爱");
            }
       }
    return QDialog::eventFilter(watched,event);     // 最后将事件交给上层对话框
}
void PlayMedia::changePage()
{
   QString whatToSearch=search_line_edit->text();
   if(!whatToSearch.isEmpty())
   {
     isfirstClicked=true;
     searchTable->setRowCount(0);
     searchTable->clearContents();
     searchframe->setVisible(true);//可视化搜索结果界面
     searchedMusicList->clear();
     download.do_download(searchTable,searchedMusicList,whatToSearch);//调用download

   }

}
void PlayMedia::toMusicPage()
{
   //inframe->setVisible(false);
   searchframe->setVisible(true);
}
void PlayMedia::toLrcPage()
{
  // inframe->setVisible(true);
   searchframe->setVisible(false);
}
void PlayMedia::silent()//静音
{
    static bool isMute=true;
    static int  v;//记录静音前声音
    if(isMute)
    {
       soundButton->setIcon(QIcon(":/wallpaper/source/noVoice.png"));
       v=player->volume();
       player->setVolume(0);
       voiceSlider->setValue(0);

    }
    else
    {
        soundButton->setIcon(QIcon(":/wallpaper/source/voice.png"));
        player->setVolume(v);
        voiceSlider->setValue(v);
    }

    isMute=isMute^1;//异或

}
void PlayMedia::createAction()
{

       //创建打开文件动作
    OpenFileAction = new QAction(tr("打开文件"), this);
       //设置打开文件动作的快捷键
    OpenFileAction->setShortcut(tr("Ctrl + O"));
       //设置打开文件动作的提示信息
    OpenFileAction->setStatusTip(tr("打开一个文件"));
       //关联打开文件动作的信号和槽
    connect(OpenFileAction, SIGNAL(triggered()),this, SLOT(addFile()));
    OpenDirAction= new QAction(tr("打开文件夹"), this);
    OpenDirAction->setShortcut(tr("Ctrl + D"));
    OpenDirAction->setStatusTip(tr("打开一个文件夹"));
    connect(OpenDirAction,SIGNAL(triggered()), this, SLOT(addDir()));
    menu=new QMenu();
    menu->addAction(OpenFileAction);
    menu->addAction(OpenDirAction);
    addButton->setMenu(menu);
    addButton->setStyleSheet("QPushButton::menu-indicator{image:None;}");

    playmodel.append(new QAction(tr("顺序播放"), this));
    playmodel.append(new QAction(tr("循环播放"), this));
    playmodel.append(new QAction(tr("随机播放"), this));
    playmodel.append(new QAction(tr("单个播放"), this));
    playmodel.append(new QAction(tr("单个循环"), this));
    for(int i=0;i<5;i++)
    {
        playmodel.at(i)->setData(i);
    }
    playmenu=new QMenu();
    playmenu->addActions(playmodel);
    connect(playmenu,SIGNAL(triggered(QAction * )),this,SLOT(loopSelect(QAction *)));
    loopButton->setMenu(playmenu);
    loopButton->setStyleSheet("QPushButton::menu-indicator{image:None;}");

}
void PlayMedia::loopSelect(QAction * action)
{

  isrand=false;//默认是不随机的
  isloop=false;//默认不随机
  int actionid=action->data().toInt();
  playmodel.at(actionid)->setIcon(QIcon(":/new/prefix1/source/bullet_blue.png"));
  for(int i=0;i<playmodel.size();i++)
   {
      if(i!=actionid)
      playmodel.at(i)->setIcon(QIcon(""));
   }
  switch(actionid)
  {
     case 0:
        playList->setPlaybackMode(QMediaPlaylist::Sequential);
        break;
     case 1:
        playList->setPlaybackMode(QMediaPlaylist::Loop);
        isloop=true;
        break;
     case 2:
        playList->setPlaybackMode(QMediaPlaylist::Random);
        isrand=true;
        break;
     case 3:
        playList->setPlaybackMode(QMediaPlaylist::CurrentItemOnce);
        break;
     case 4:
        playList->setPlaybackMode(QMediaPlaylist:: CurrentItemInLoop);

  }


}
void PlayMedia::deleteFile()
{
  QList<QListWidgetItem*> list_seleted=listwidget->selectedItems();
  int num=0;
  while(num<list_seleted.size())
  {
       int itemid=listwidget->row(list_seleted[num]);
       listwidget->takeItem(itemid);
       if(itemid==id)
       {
        delIsPlaying=true;//播完再删
        num++;
        continue;
       }
       playList->removeMedia(itemid);
       num++;
  }
}
void PlayMedia::addFile()
{
    QFileDialog dlg(NULL,"打开文件");
    dlg.setFixedSize(200,400);
    dlg.setWindowFlags(windowFlags()|Qt::WindowMinimizeButtonHint);
    dlg.setAcceptMode(QFileDialog::AcceptOpen);
    dlg.setNameFilter("音乐(*.mp3 *.wav *.ogg)");
    dlg.exec();
    QStringList files = dlg.selectedFiles();
    if(!files.isEmpty()){
        QString filepath = files.at(0);

        QFont font;//字体
        font.setPixelSize(17);
        font.setBold(true);

        QFileInfo fileInfo(filepath);
        localplayList->addMedia(QUrl::fromLocalFile(fileInfo.absoluteFilePath()));

        QString str=fileInfo.fileName();
        QListWidgetItem *musicitem=new QListWidgetItem(str);
        musicitem->setTextColor(QColor(240,100,18));
        musicitem->setFont(font);
        listwidget->addItem(musicitem);

        name_path_map.insert(str,filepath);//歌曲名与路径映射


    }
}
void PlayMedia::addDir()
{
    QFileDialog w;
    w.setAcceptMode(QFileDialog::AcceptOpen);   //AcceptOpen打开,AcceptSave保存文件
    w.setFileMode(QFileDialog::Directory);
    w.setOption(QFileDialog::ReadOnly, true);
    w.setWindowTitle(QString("打开文件夹"));
    w.setDirectory(QString("./"));
    if (w.exec())
    {
        cout<<"open filedir"<<endl;
    }

}
void PlayMedia::setPositon(int position)
{
    player->setPosition(position);
}
void PlayMedia::positionChanged(qint64 position)
{
   if(!current_time_label->text().compare(whole_time_label->text()))
    {
       playnum=1;
       playButton->setIcon(QIcon(":/new/prefix2/source/playIcon.png"));
       if(delIsPlaying)
       {
           playList->removeMedia(id);
           delIsPlaying=false;
       }
       return;
    }
    QString curtime=showtime(position,1);
    current_time_label->setText(curtime);
    slider->setValue(position);

}
void PlayMedia::durationChanged(qint64 duration)
{
   slider->setRange(0, duration-3500);
   totaltime=duration-2000;
}
QString PlayMedia::showtime(int duration,int apt)
{
    int musictime=duration/1000;
    int sec=musictime%60+apt;
    int min=musictime/60;
    QString minset=QString::number(min,10);
    QString secset=QString::number(sec,10);
    if(sec<10)
    secset="0"+secset;
    QString songtime=minset+":"+ secset;
    return songtime;

}
void PlayMedia::setVoice()
{
   int v=voiceSlider->value();
   player->setVolume(v);

}
void PlayMedia::readLrc(QString lrcPath)
{
    QFile f(lrcPath);  
    if(!f.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        cout << "Open failed." << endl;
        return;
    }

    QTextStream txtInput(&f);
    int i=1;
    QString lineStr;//歌词
    while(!txtInput.atEnd())
    {
        lineStr= txtInput.readLine();
        if(lineStr==NULL)
        continue;
        lineStr=lineStr.split("]").at(1);
       // qDebug()<<lineStr<<endl;
        m_map.insert(i,lineStr);//存入歌词key-value
        i++;
    }
    f.close();
}
void PlayMedia::showLrc()
{
    static int i=4;
    int count=i;
    QString nowLrc="";//显示部分歌词
    for(;count<10+i;count++)
    {
       QMap<int,QString>::iterator it=m_map.find(count);
       nowLrc+=it.value();
       nowLrc+="\n";

    }
     lrctext->setText(nowLrc);
     i++;
     if((i+10)>=m_map.count())
     timer->stop();


}
void PlayMedia::getInformation()
{
    current_time_label->setText("0:00");
    if (player->isMetaDataAvailable())
    {
        QString artist=player->metaData(QMediaMetaData::Author).toString();
        QString album=player->metaData(QMediaMetaData::AlbumTitle).toString();
        if(artist.isEmpty())
           artist="未知";
        if(album.isEmpty())
           album="未知";
        artist=" 歌手: "+artist;
        album="唱片集: "+ album;
        QString aboutSong=artist+"  "+album;
        labelSongInfo->setText(aboutSong);//陈奕迅

        QString songname=player->metaData(QMediaMetaData::Title).toString();

        labelsong->setText(songname);//显示歌曲名称
        player->setVolume(50);
        QString songtime=showtime(totaltime,0);
        whole_time_label->setText(songtime);
        current_time_label->setText("0:00");
        return;
    }

}
void PlayMedia::playmusic()
{
     cout<<"playnum:"<<playnum<<";"<<"id:"<<id<<endl;
    if(playList->isEmpty()&&webplayList->isEmpty())
     {
      QMessageBox::warning(this,"提醒","当前没有可播放的文件");
      return ;
     }

    if(playnum==1)//此处可优化。。。
    {
        if(isfirstClicked) //改变量为true，说明还没有被点，即不适用webplaylist
        playList->setCurrentIndex(id);
        else
        webplayList->setCurrentIndex(id);
        player->play();
        playButton->setIcon(QIcon(":/new/prefix1/source/pause.png"));
        playnum++;
        return;
    }
    if(playnum%2==0)
    {
        playButton->setIcon(QIcon(":/new/prefix2/source/playIcon.png"));
        player->pause();
        playnum++;
        return;
    }
    else
    {

     playButton->setIcon(QIcon(":/new/prefix1/source/pause.png"));
     player->play();
     playnum++;
    }
}
void PlayMedia::stopmusic()
{
    player->stop();
    playButton->setIcon(QIcon(":/new/prefix2/source/playIcon.png"));
    labelsong->setText(NULL);
    playnum=1;
    whole_time_label->setText("0:00");
    current_time_label->setText("0:00");
    slider->setValue(0);
    cout<<"stopmusic"<<endl;
}
void PlayMedia::addlist()
{
    QString path="F:\\movies\\班得瑞全集\\05迷雾森林";//"D:\\Testmusic";
    QDir dir(path);
    dir.setFilter(QDir::Dirs|QDir::Files);
    dir.setSorting(QDir::DirsFirst);
    QFileInfoList templist =dir.entryInfoList();
    QFont font;//字体
    font.setPixelSize(17);
    font.setBold(true);
    int i = 2;
    do{
          QFileInfo fileInfo = templist.at(i);    
          localplayList->addMedia(QUrl::fromLocalFile(fileInfo.absoluteFilePath()));
          QString str=fileInfo.fileName();
          QListWidgetItem *musicitem=new QListWidgetItem(str);
          musicitem->setTextColor(QColor(19, 100, 255));
          musicitem->setFont(font);
          listwidget->addItem(musicitem);
          i++;

      }
    while(i<templist.size());
    id=0;
    cout<<"addlist"<<endl;

}
void PlayMedia::lastmusic()
{
    cout<<"last song"<<endl;
    if(!isrand)
    {
        id--;
        if(id<0)
        {
            id=playList->mediaCount()-1;
            if(!isloop)
            return;
        }
    }
    else
    {
        id=rand()%playList->mediaCount();

    }
    playnum=1;
    playmusic();
}
void PlayMedia::nextmusic()
{
    cout<<"next song"<<endl;
    id++;
    int count=playList->mediaCount();
    if(!isrand)
   {
        if(id>count-1)
        {
         id=0;
         if(!isloop)
         return;
        }
   }
    else
    {
        id=rand()%count;

    }
    playnum=1;
    playmusic();
}

void PlayMedia::clickItem(QListWidgetItem * item)
{

   int listid=listwidget->row(item);
   id=listid;
   player->setPlaylist(localplayList);//播放列表改为localplayList
   playnum=1;
   playmusic();
}
void PlayMedia::clickTableItem(QTableWidgetItem * item)//点击播放
{

    if(isfirstClicked)
   {
    webplayList->clear();//初始要清空
    int musicAmount=searchedMusicList->size();
    int order=0;
    while(order<musicAmount)
    {
        QString songlink=searchedMusicList->at(order);
        webplayList->addMedia(QUrl(songlink));
        order++;
    }   
    //player->setPlaylist(webplayList);//播放列表改为webplayList
    isfirstClicked=false;
  }//if end
    player->setPlaylist(webplayList);//播放列表改为webplayList
    int listid=searchTable->row(item);
    id=listid;
    playnum=1;
    whole_time_label->setText(searchTable->item(id,3)->text());
  /*************加载网络图片 ***********************/
    QUrl url("http://image.haosou.com/i?q="+searchTable->item(id,2)->text()+searchTable->item(id,1)->text()+"&src=srp");
    QNetworkAccessManager manager;
    QEventLoop loop;
    QNetworkReply *reply = manager.get(QNetworkRequest(url));

    //请求结束并下载完成后，退出子事件循环
    QObject::connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
       //开启子事件循环
    loop.exec();
    QByteArray jpegData = reply->readAll();
    QString pattern("thumb_bak(.){0,70}jpg\",\"thumb");
    QRegExp rx(pattern);
    QString str(jpegData);
    int pos = str.indexOf(rx);
    QString luanurl=rx.cap(0);
    QString picurl=luanurl.mid(luanurl.indexOf("http"),luanurl.indexOf(",")-luanurl.indexOf("http")-1);
//-------
    QStringList urlslice=picurl.split("\\");
    picurl="";
    int index=0;
    while(index<urlslice.length()){
        picurl+=urlslice.at(index);
        index++;
    }
    QUrl url2(picurl);
    QNetworkAccessManager managerPic;
    QNetworkReply *replyPic = managerPic.get(QNetworkRequest(url2));
    QEventLoop loopPic;
    //请求结束并下载完成后，退出子事件循环
    QObject::connect(replyPic, SIGNAL(finished()), &loopPic, SLOT(quit()));
       //开启子事件循环
    loopPic.exec();
    QByteArray picData = replyPic->readAll();
    QSize picSize(260,300);
    QPixmap pixmap;
    pixmap.loadFromData(picData);
    QPixmap scaledPixmap = pixmap.scaled(picSize);
    picLabel->setPixmap(scaledPixmap); // 你在QLabel显示图片*/
    /****************************************/
    playmusic();
   //开始获取歌词
    QString songInfo=searchTable->item(id,1)->text();
    songInfo.remove(0,1);
    QString lyric=download.python(songInfo);
    QFile f(".//lyrics//"+songInfo+".lrc");
    if(!f.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        cout << "Open failed." << endl;
    }
    else{
        QTextStream txtOutput(&f);
        txtOutput <<lyric<< endl;
    }
    readLrc(".//lyrics//"+songInfo+".lrc");
    timer->start();
    //lrctext->setText(lyric);
}

PlayMedia::~PlayMedia()
{
    //delete player;
}
