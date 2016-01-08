#ifndef PLAY_H
#define PLAY_H
#include"mainwindow.h"
#include<QtWidgets/QDialog>
#include<QMediaPlaylist>
#include<qmap.h>
class PlayMedia : public QDialog,public Ui::Dialog
{
    Q_OBJECT

public:
    explicit PlayMedia(QWidget *parent = 0);
    ~PlayMedia();
public slots:
    void playmusic();
    void stopmusic();
    void addlist();
    void lastmusic();
    void nextmusic();
    void clickItem(QListWidgetItem * item);
    void clickTableItem(QTableWidgetItem * item);
    void getInformation();
    void setVoice();
    void addFile();
    void addDir();
    void deleteFile();
    void createAction();        //创建动作
    void loopSelect(QAction * action);//播放模式
    void positionChanged(qint64);
    void durationChanged(qint64);
    void setPositon(int);
    void readLrc(QString);//读歌词
    void showLrc();//刷新歌词
    void silent();//静音
    void changePage();//换页
    bool eventFilter(QObject *,QEvent *);    //注意这里
    void toMusicPage();//前一个frame
    void toLrcPage();//切换到歌词页面
    void closeEvent(QCloseEvent *event);
    void showEvent(QShowEvent *event);
    QString showtime(int,int);
private:
    QAction *OpenFileAction;    //打开文件动作
    QAction *OpenDirAction;   //打开文件夹动作
    QMenu * menu;
    QList<QAction*> playmodel;
    QMenu * playmenu;
    QMediaPlaylist  *playList;
    QMediaPlaylist  *webplayList;
    QMediaPlaylist  *localplayList;
    QMap<QString,QString> name_path_map;//歌曲名与路径映射，2015/12/30

};
#endif // PLAY_H

