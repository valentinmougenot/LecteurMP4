#ifndef TP3_MAINWINDOW_HPP
#define TP3_MAINWINDOW_HPP


#include <QMainWindow>
#include <QMediaPlayer>
#include <QWidget>
#include <QMediaPlaylist>
#include <QVideoWidget>
#include <QPushButton>
#include <QListWidget>

class MainWindow : public QMainWindow {
Q_OBJECT

public:
    MainWindow();
    static inline QString imagePath = QString("/Volumes/T7 Shield/IUT/S4/Qt/LecteurMP4/images/");

private:
    QMediaPlayer *player;
    QMediaPlaylist *playlist;
    QVideoWidget *videoWidget;
    QPushButton *previousButton;
    QPushButton *playPauseButton;
    QPushButton *stopButton;
    QPushButton *nextButton;
    QListWidget *listWidget;

private slots:
    void open();
    void openDirectory();
    void setPlayPauseButtonState();
    void setCurrentRow(int index);
    void setCurrentIndex(QListWidgetItem *item);
    void addFileToPlaylist();
};



#endif //TP3_MAINWINDOW_HPP
