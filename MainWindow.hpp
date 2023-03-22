#ifndef TP3_MAINWINDOW_HPP
#define TP3_MAINWINDOW_HPP


#include <QMainWindow>
#include <QMediaPlayer>
#include <QWidget>
#include <QMediaPlaylist>
#include <QVideoWidget>

class MainWindow : public QMainWindow {
Q_OBJECT

public:
    MainWindow();


private:
    QMediaPlayer *player;
    QMediaPlaylist *playlist;
    QVideoWidget *videoWidget;


private slots:

    void open();
    void openDirectory();

};



#endif //TP3_MAINWINDOW_HPP
