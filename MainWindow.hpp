#ifndef TP3_MAINWINDOW_HPP
#define TP3_MAINWINDOW_HPP


#include <QMainWindow>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QVideoWidget>


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();
    QMediaPlayer *player;
    QMediaPlaylist *playlist;
    QVideoWidget *videoWidget;
};


#endif //TP3_MAINWINDOW_HPP
