/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QPushButton *lastButton;
    QPushButton *playButton;
    QPushButton *stopButton;
    QPushButton *nextButton;
    QSpacerItem *horizontalSpacer;
    QPushButton *soundButton;
    QSlider *voiceSlider;
    QLabel *playListLabel;
    QListWidget *listwidget;
    QWidget *horizontalLayoutWidget_3;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *loopButton;
    QPushButton *addButton;
    QPushButton *deleteButton;
    QWidget *horizontalLayoutWidget_2;
    QHBoxLayout *progressLayout;
    QFrame *inframe;
    QLabel *picLabel;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout_2;
    QLabel *labelsong;
    QLabel *labelSongInfo;
    QTextEdit *lrctext;
    QFrame *searchframe;
    QLabel *label_2;
    QTableWidget *searchTable;
    QWidget *horizontalLayoutWidget_4;
    QHBoxLayout *horizontalLayout_3;
    QToolButton *lrcPageBtn;
    QToolButton *musicPageBtn;
    QLineEdit *search_line_edit;
    QFrame *line;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QStringLiteral("Dialog"));
        Dialog->setEnabled(true);
        Dialog->resize(907, 630);
        QIcon icon;
        icon.addFile(QStringLiteral(":/wallpaper/source/title.png"), QSize(), QIcon::Normal, QIcon::Off);
        Dialog->setWindowIcon(icon);
        Dialog->setSizeGripEnabled(true);
        horizontalLayoutWidget = new QWidget(Dialog);
        horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(440, 550, 421, 71));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(horizontalLayoutWidget);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        lastButton = new QPushButton(horizontalLayoutWidget);
        lastButton->setObjectName(QStringLiteral("lastButton"));
        lastButton->setEnabled(true);
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/new/prefix2/source/lastIcon.png"), QSize(), QIcon::Normal, QIcon::Off);
        lastButton->setIcon(icon1);
        lastButton->setIconSize(QSize(30, 30));
        lastButton->setFlat(true);

        horizontalLayout->addWidget(lastButton);

        playButton = new QPushButton(horizontalLayoutWidget);
        playButton->setObjectName(QStringLiteral("playButton"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/new/prefix2/source/playIcon.png"), QSize(), QIcon::Normal, QIcon::Off);
        playButton->setIcon(icon2);
        playButton->setIconSize(QSize(30, 30));
        playButton->setFlat(true);

        horizontalLayout->addWidget(playButton);

        stopButton = new QPushButton(horizontalLayoutWidget);
        stopButton->setObjectName(QStringLiteral("stopButton"));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/new/prefix1/source/stopIcon.png"), QSize(), QIcon::Normal, QIcon::Off);
        stopButton->setIcon(icon3);
        stopButton->setIconSize(QSize(30, 30));
        stopButton->setFlat(true);

        horizontalLayout->addWidget(stopButton);

        nextButton = new QPushButton(horizontalLayoutWidget);
        nextButton->setObjectName(QStringLiteral("nextButton"));
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/new/prefix2/source/nextIcon.png"), QSize(), QIcon::Normal, QIcon::Off);
        nextButton->setIcon(icon4);
        nextButton->setIconSize(QSize(30, 30));
        nextButton->setFlat(true);

        horizontalLayout->addWidget(nextButton);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        soundButton = new QPushButton(horizontalLayoutWidget);
        soundButton->setObjectName(QStringLiteral("soundButton"));
        QIcon icon5;
        icon5.addFile(QStringLiteral(":/wallpaper/source/voice.png"), QSize(), QIcon::Normal, QIcon::Off);
        soundButton->setIcon(icon5);
        soundButton->setIconSize(QSize(25, 25));
        soundButton->setFlat(true);

        horizontalLayout->addWidget(soundButton);

        voiceSlider = new QSlider(horizontalLayoutWidget);
        voiceSlider->setObjectName(QStringLiteral("voiceSlider"));
        voiceSlider->setStyleSheet(QStringLiteral(""));
        voiceSlider->setMaximum(100);
        voiceSlider->setValue(50);
        voiceSlider->setSliderPosition(50);
        voiceSlider->setOrientation(Qt::Horizontal);
        voiceSlider->setTickPosition(QSlider::TicksAbove);

        horizontalLayout->addWidget(voiceSlider);

        playListLabel = new QLabel(Dialog);
        playListLabel->setObjectName(QStringLiteral("playListLabel"));
        playListLabel->setGeometry(QRect(0, 30, 221, 16));
        playListLabel->setAlignment(Qt::AlignCenter);
        listwidget = new QListWidget(Dialog);
        listwidget->setObjectName(QStringLiteral("listwidget"));
        listwidget->setGeometry(QRect(0, 110, 271, 511));
        listwidget->setAutoFillBackground(false);
        listwidget->setStyleSheet(QString::fromUtf8("font: 75 10pt \"\344\273\277\345\256\213\";\n"
"font: 9pt \"Adobe Caslon Pro\";\n"
"color: rgb(85, 255, 255);\n"
""));
        listwidget->setFrameShadow(QFrame::Sunken);
        listwidget->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        listwidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        listwidget->setAutoScroll(false);
        listwidget->setDragEnabled(false);
        listwidget->setDragDropOverwriteMode(false);
        listwidget->setHorizontalScrollMode(QAbstractItemView::ScrollPerItem);
        listwidget->setProperty("isWrapping", QVariant(false));
        listwidget->setResizeMode(QListView::Fixed);
        listwidget->setSortingEnabled(false);
        horizontalLayoutWidget_3 = new QWidget(Dialog);
        horizontalLayoutWidget_3->setObjectName(QStringLiteral("horizontalLayoutWidget_3"));
        horizontalLayoutWidget_3->setGeometry(QRect(30, 60, 158, 41));
        horizontalLayout_2 = new QHBoxLayout(horizontalLayoutWidget_3);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        loopButton = new QPushButton(horizontalLayoutWidget_3);
        loopButton->setObjectName(QStringLiteral("loopButton"));
        QIcon icon6;
        icon6.addFile(QStringLiteral(":/new/prefix2/source/loop.png"), QSize(), QIcon::Normal, QIcon::Off);
        loopButton->setIcon(icon6);
        loopButton->setIconSize(QSize(30, 30));
        loopButton->setFlat(true);

        horizontalLayout_2->addWidget(loopButton);

        addButton = new QPushButton(horizontalLayoutWidget_3);
        addButton->setObjectName(QStringLiteral("addButton"));
        QIcon icon7;
        icon7.addFile(QStringLiteral(":/new/prefix1/source/add.png"), QSize(), QIcon::Normal, QIcon::Off);
        addButton->setIcon(icon7);
        addButton->setIconSize(QSize(20, 20));
        addButton->setAutoDefault(true);
        addButton->setDefault(false);
        addButton->setFlat(true);

        horizontalLayout_2->addWidget(addButton);

        deleteButton = new QPushButton(horizontalLayoutWidget_3);
        deleteButton->setObjectName(QStringLiteral("deleteButton"));
        QIcon icon8;
        icon8.addFile(QStringLiteral(":/new/prefix1/source/delete.png"), QSize(), QIcon::Normal, QIcon::Off);
        deleteButton->setIcon(icon8);
        deleteButton->setIconSize(QSize(25, 25));
        deleteButton->setFlat(true);

        horizontalLayout_2->addWidget(deleteButton);

        horizontalLayoutWidget_2 = new QWidget(Dialog);
        horizontalLayoutWidget_2->setObjectName(QStringLiteral("horizontalLayoutWidget_2"));
        horizontalLayoutWidget_2->setGeometry(QRect(280, 530, 621, 20));
        progressLayout = new QHBoxLayout(horizontalLayoutWidget_2);
        progressLayout->setObjectName(QStringLiteral("progressLayout"));
        progressLayout->setContentsMargins(0, 0, 0, 0);
        inframe = new QFrame(Dialog);
        inframe->setObjectName(QStringLiteral("inframe"));
        inframe->setEnabled(true);
        inframe->setGeometry(QRect(280, 60, 621, 461));
        inframe->setFrameShape(QFrame::StyledPanel);
        inframe->setFrameShadow(QFrame::Raised);
        picLabel = new QLabel(inframe);
        picLabel->setObjectName(QStringLiteral("picLabel"));
        picLabel->setEnabled(true);
        picLabel->setGeometry(QRect(353, 100, 261, 301));
        picLabel->setPixmap(QPixmap(QString::fromUtf8(":/wallpaper/source/title.png")));
        verticalLayoutWidget = new QWidget(inframe);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(0, 10, 341, 87));
        verticalLayout_2 = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        labelsong = new QLabel(verticalLayoutWidget);
        labelsong->setObjectName(QStringLiteral("labelsong"));
        labelsong->setStyleSheet(QLatin1String("font: 75 16pt \"Adobe Caslon Pro Bold\";\n"
"color: rgb(0, 0, 0);"));

        verticalLayout_2->addWidget(labelsong);

        labelSongInfo = new QLabel(verticalLayoutWidget);
        labelSongInfo->setObjectName(QStringLiteral("labelSongInfo"));
        labelSongInfo->setStyleSheet(QLatin1String("font: 10pt \"Simplified Arabic\";\n"
"color: rgb(108, 109, 125);\n"
"font: 12pt \"Adobe Caslon Pro\";"));

        verticalLayout_2->addWidget(labelSongInfo);

        lrctext = new QTextEdit(inframe);
        lrctext->setObjectName(QStringLiteral("lrctext"));
        lrctext->setEnabled(false);
        lrctext->setGeometry(QRect(0, 100, 341, 331));
        QFont font;
        font.setFamily(QStringLiteral("Adobe Caslon Pro"));
        font.setPointSize(11);
        lrctext->setFont(font);
        lrctext->setStyleSheet(QStringLiteral("color: rgb(0, 0, 127);"));
        lrctext->setFrameShape(QFrame::NoFrame);
        lrctext->setFrameShadow(QFrame::Plain);
        lrctext->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        lrctext->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        searchframe = new QFrame(inframe);
        searchframe->setObjectName(QStringLiteral("searchframe"));
        searchframe->setGeometry(QRect(0, 10, 621, 481));
        searchframe->setFrameShape(QFrame::StyledPanel);
        searchframe->setFrameShadow(QFrame::Raised);
        label_2 = new QLabel(searchframe);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(-10, 70, 621, 20));
        searchTable = new QTableWidget(searchframe);
        if (searchTable->columnCount() < 4)
            searchTable->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        searchTable->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        searchTable->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        searchTable->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        searchTable->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        searchTable->setObjectName(QStringLiteral("searchTable"));
        searchTable->setGeometry(QRect(0, 0, 621, 471));
        searchTable->setRowCount(0);
        searchTable->setColumnCount(4);
        searchTable->horizontalHeader()->setCascadingSectionResizes(false);
        searchTable->horizontalHeader()->setDefaultSectionSize(100);
        horizontalLayoutWidget_4 = new QWidget(Dialog);
        horizontalLayoutWidget_4->setObjectName(QStringLiteral("horizontalLayoutWidget_4"));
        horizontalLayoutWidget_4->setGeometry(QRect(590, 10, 291, 51));
        horizontalLayout_3 = new QHBoxLayout(horizontalLayoutWidget_4);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        lrcPageBtn = new QToolButton(horizontalLayoutWidget_4);
        lrcPageBtn->setObjectName(QStringLiteral("lrcPageBtn"));
        QFont font1;
        font1.setFamily(QStringLiteral("Adobe Garamond Pro"));
        font1.setPointSize(17);
        font1.setBold(true);
        font1.setItalic(false);
        font1.setUnderline(true);
        font1.setWeight(75);
        lrcPageBtn->setFont(font1);
        lrcPageBtn->setStyleSheet(QLatin1String("color: rgb(170, 255, 0);\n"
"background-color: transparent\n"
""));
        lrcPageBtn->setIconSize(QSize(28, 28));

        horizontalLayout_3->addWidget(lrcPageBtn);

        musicPageBtn = new QToolButton(horizontalLayoutWidget_4);
        musicPageBtn->setObjectName(QStringLiteral("musicPageBtn"));
        QFont font2;
        font2.setFamily(QStringLiteral("Adobe Garamond Pro"));
        font2.setPointSize(15);
        font2.setBold(true);
        font2.setUnderline(true);
        font2.setWeight(75);
        musicPageBtn->setFont(font2);
        musicPageBtn->setStyleSheet(QLatin1String("color: rgb(0, 255, 0);\n"
"background-color:transparent\n"
""));
        musicPageBtn->setIconSize(QSize(28, 28));

        horizontalLayout_3->addWidget(musicPageBtn);

        search_line_edit = new QLineEdit(Dialog);
        search_line_edit->setObjectName(QStringLiteral("search_line_edit"));
        search_line_edit->setEnabled(true);
        search_line_edit->setGeometry(QRect(290, 20, 241, 31));
        search_line_edit->setLayoutDirection(Qt::LeftToRight);
        line = new QFrame(Dialog);
        line->setObjectName(QStringLiteral("line"));
        line->setEnabled(false);
        line->setGeometry(QRect(290, 50, 602, 20));
        QFont font3;
        font3.setFamily(QStringLiteral("Adobe Caslon Pro"));
        font3.setBold(false);
        font3.setWeight(50);
        line->setFont(font3);
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        retranslateUi(Dialog);

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QApplication::translate("Dialog", "Lagoon50", 0));
        label->setText(QString());
        lastButton->setText(QString());
        playButton->setText(QString());
        stopButton->setText(QString());
        nextButton->setText(QString());
#ifndef QT_NO_TOOLTIP
        soundButton->setToolTip(QApplication::translate("Dialog", "\351\235\231\351\237\263", 0));
#endif // QT_NO_TOOLTIP
        soundButton->setText(QString());
        playListLabel->setText(QApplication::translate("Dialog", "<html><head/><body><p><span style=\" font-size:11pt; font-weight:600; color:#070608;\">\346\222\255\346\224\276\345\210\227\350\241\250</span></p></body></html>", 0));
#ifndef QT_NO_TOOLTIP
        loopButton->setToolTip(QApplication::translate("Dialog", "\346\222\255\346\224\276\346\250\241\345\274\217", 0));
#endif // QT_NO_TOOLTIP
        loopButton->setText(QString());
        addButton->setText(QString());
        deleteButton->setText(QString());
        picLabel->setText(QString());
        labelsong->setText(QString());
        labelSongInfo->setText(QString());
#ifndef QT_NO_TOOLTIP
        lrctext->setToolTip(QString());
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        lrctext->setStatusTip(QString());
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_WHATSTHIS
        lrctext->setWhatsThis(QString());
#endif // QT_NO_WHATSTHIS
        lrctext->setHtml(QApplication::translate("Dialog", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Adobe Caslon Pro'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>", 0));
        label_2->setText(QString());
        QTableWidgetItem *___qtablewidgetitem = searchTable->horizontalHeaderItem(1);
        ___qtablewidgetitem->setText(QApplication::translate("Dialog", "\351\237\263\344\271\220\345\220\215", 0));
        QTableWidgetItem *___qtablewidgetitem1 = searchTable->horizontalHeaderItem(2);
        ___qtablewidgetitem1->setText(QApplication::translate("Dialog", "\346\255\214\346\211\213", 0));
        QTableWidgetItem *___qtablewidgetitem2 = searchTable->horizontalHeaderItem(3);
        ___qtablewidgetitem2->setText(QApplication::translate("Dialog", "\346\227\266\351\225\277", 0));
        lrcPageBtn->setText(QApplication::translate("Dialog", "\346\255\214\350\257\215", 0));
        musicPageBtn->setText(QApplication::translate("Dialog", "\351\237\263\344\271\220\345\210\227\350\241\250", 0));
        search_line_edit->setInputMask(QString());
        search_line_edit->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // MAINWINDOW_H
