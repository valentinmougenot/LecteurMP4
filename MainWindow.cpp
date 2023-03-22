#include <QFileDialog>
#include <QStatusBar>
#include <QMenuBar>
#include <QToolBar>
#include <QAction>
#include <QCoreApplication>
#include <QDirIterator>

#include "MainWindow.hpp"

MainWindow::MainWindow() : QMainWindow()
{
    player = new QMediaPlayer(this);
    playlist = new QMediaPlaylist(this);
    videoWidget = new QVideoWidget(this);
    setCentralWidget(videoWidget);
    player->setVideoOutput(videoWidget);
    player->setPlaylist(playlist);

    // Créer une action pour ouvrir un fichier
    QAction *openAction = new QAction(tr("Open"), this);
    connect(openAction, &QAction::triggered, this, &MainWindow::open);

    // Créer une action pour ouvrir un dossier
    QAction *openDirectoryAction = new QAction(tr("Open Directory"), this);
    connect(openDirectoryAction, &QAction::triggered, this, &MainWindow::openDirectory);

    // Créer une barre de menu et ajouter les actions d'ouverture de fichier et de dossier
    QMenu *fileMenu = menuBar()->addMenu(tr("File"));
    fileMenu->addAction(openAction);
    fileMenu->addAction(openDirectoryAction);

    // Créer les boutons de contrôle avec les bonnes icônes
    previousButton = new QPushButton(this);
    previousButton->setIcon(QIcon("/Volumes/T7 Shield/IUT/S4/Qt/LecteurMP4/images/previous.png"));
    connect(previousButton, &QPushButton::clicked, playlist, &QMediaPlaylist::previous);

    playPauseButton = new QPushButton(this);
    connect(playPauseButton, &QPushButton::clicked, this, &MainWindow::setPlayPauseButtonState);
    playPauseButton->setIcon(QIcon("/Volumes/T7 Shield/IUT/S4/Qt/LecteurMP4/images/play.png"));

    stopButton = new QPushButton(this);
    connect(stopButton, &QPushButton::clicked, player, &QMediaPlayer::stop);
    stopButton->setIcon(QIcon("/Volumes/T7 Shield/IUT/S4/Qt/LecteurMP4/images/stop.png"));

    nextButton = new QPushButton(this);
    connect(nextButton, &QPushButton::clicked, playlist, &QMediaPlaylist::next);
    nextButton->setIcon(QIcon("/Volumes/T7 Shield/IUT/S4/Qt/LecteurMP4/images/next.png"));

    // On ajoute les boutons à la barre d'outils
    QToolBar *controlToolBar = addToolBar(tr("Control"));
    controlToolBar->addWidget(previousButton);
    controlToolBar->addWidget(playPauseButton);
    controlToolBar->addWidget(stopButton);
    controlToolBar->addWidget(nextButton);

}

void MainWindow::open()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Ouvrir un fichier"), QDir::homePath(), tr("Fichier Vidéo (*.mp4 *.mp3 *.avi)"));

    player->setMedia(QUrl::fromLocalFile(fileName));
    player->play();
}

void MainWindow::openDirectory()
{
    QString directoryName = QFileDialog::getExistingDirectory(this, tr("Sélectionner un dossier"), QDir::homePath());

    if (!directoryName.isEmpty()) {
        // On filtre les fichiers vidéo du dossier
        QDirIterator it(directoryName, QStringList() << "*.mp4" << "*.mp3" << "*.avi", QDir::Files, QDirIterator::Subdirectories);
        QStringList mediaFiles;

        while (it.hasNext()) {
            mediaFiles << it.next();
        }

        // On ajoute les vidéos dans la playlist
        for (const QString &file : mediaFiles) {
            playlist->addMedia(QUrl::fromLocalFile(file));
        }
    }

    player->play();
}

void MainWindow::setPlayPauseButtonState() {
    // On change l'état de la lecture et l'icone du bouton en fonction de l'état de la lecture
    if (player->state() == QMediaPlayer::PlayingState) {
        playPauseButton->setIcon(QIcon("/Volumes/T7 Shield/IUT/S4/Qt/LecteurMP4/images/play.png"));
        player->pause();
    }
    else {
        playPauseButton->setIcon(QIcon("/Volumes/T7 Shield/IUT/S4/Qt/LecteurMP4/images/pause.png"));
        player->play();
    }
}