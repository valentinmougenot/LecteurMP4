#ifndef TP3_MAINWINDOW_HPP
#define TP3_MAINWINDOW_HPP


#include <QMainWindow>
#include <QMediaPlayer>
#include <QWidget>
#include <QMediaPlaylist>
#include <QVideoWidget>
#include <QPushButton>
#include <QListWidget>
#include <QSlider>

class MainWindow : public QMainWindow {
Q_OBJECT

public:
    MainWindow();
    static inline QString imagePath = QString("/Volumes/T7 Shield/IUT/S4/Qt/LecteurMP4/images/");

private:
    QMediaPlayer *player;
    QMediaPlaylist *playlist;
    QVideoWidget *videoWidget;
    QSlider *slider;
    QPushButton *previousButton;
    QPushButton *playPauseButton;
    QPushButton *stopButton;
    QPushButton *nextButton;
    QPushButton *volumeButton;
    QSlider *sliderVolume;
    QListWidget *listWidget;

private slots:
    void open();
    void openDirectory();
    void setPlayPauseButtonState();
    void setCurrentRow(int index);
    void setCurrentIndex(QListWidgetItem *item);
    void addFileToPlaylist();
    void clearPlaylist();
    void deleteFileFromPlaylist();
    void setVolumeButtonState();

    void setupMainElements();
    void setupFileMenu() const;
    void setupPlaylistButtons(QPushButton *&buttonAddFilePlaylist, QPushButton *&buttonDeleteFilePlaylist, QPushButton *&buttonClearPlaylist) const;
    void setupControlButtons();
};



#endif //TP3_MAINWINDOW_HPP
