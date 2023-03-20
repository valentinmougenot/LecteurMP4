#ifndef TP3_MAINWINDOW_HPP
#define TP3_MAINWINDOW_HPP


#include <QMainWindow>
#include <QMediaPlayer>
#include <QWidget>
#include <QMediaPlaylist>
#include <QVideoWidget>

QT_BEGIN_NAMESPACE
class QAction;
class QMenu;
class QSessionManager;
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
Q_OBJECT



public:
    MainWindow(QWidget *parent);

    QMediaPlayer *player;
    QMediaPlaylist *playlist{};
    QVideoWidget *videoWidget;


private slots:

    void open();

};



#endif //TP3_MAINWINDOW_HPP
