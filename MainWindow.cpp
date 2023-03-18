#include "MainWindow.hpp"


MainWindow::MainWindow()
{
    playlist = new QMediaPlaylist;
    playlist->addMedia(QUrl::fromLocalFile("/home/valentin/Documents/LecteurMP4/videos/sample-5s.mp4"));
    playlist->addMedia(QUrl::fromLocalFile("/home/valentin/Documents/LecteurMP4/videos/sample-10s.mp4"));
    playlist->setCurrentIndex(1);

    player = new QMediaPlayer;
    player->setPlaylist(playlist);

    videoWidget = new QVideoWidget;
    player->setVideoOutput(videoWidget);

    setCentralWidget(videoWidget);

    player->play();
}

