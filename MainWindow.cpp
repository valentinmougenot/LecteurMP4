#include <QFileDialog>
#include <QStatusBar>
#include <QMenuBar>
#include <QAction>
#include <QCoreApplication>
#include <QDirIterator>
#include <QVBoxLayout>
#include <QAbstractItemView>

#include "MainWindow.hpp"

MainWindow::MainWindow() : QMainWindow()
{
    // Créer les éléments de base
    player = new QMediaPlayer(this);
    playlist = new QMediaPlaylist(this);
    videoWidget = new QVideoWidget(this);
    setCentralWidget(videoWidget);
    player->setVideoOutput(videoWidget);
    player->setPlaylist(playlist);

    // Créer la liste qui contient toutes les vidéos
    listWidget = new QListWidget(this);
    listWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    connect(playlist, &QMediaPlaylist::currentIndexChanged, this, &MainWindow::setCurrentRow);
    connect(listWidget, &QListWidget::itemDoubleClicked, this, &MainWindow::setCurrentIndex);

    // Créer une action pour ouvrir un fichier
    auto *openAction = new QAction(tr("Open"), this);
    connect(openAction, &QAction::triggered, this, &MainWindow::open);

    // Créer une action pour ouvrir un dossier
    auto *openDirectoryAction = new QAction(tr("Open Directory"), this);
    connect(openDirectoryAction, &QAction::triggered, this, &MainWindow::openDirectory);

    // Créer une barre de menu et ajouter les actions d'ouverture de fichier et de dossier
    QMenu *fileMenu = menuBar()->addMenu(tr("File"));
    fileMenu->addAction(openAction);
    fileMenu->addAction(openDirectoryAction);
    
    // Créer les boutons de contrôle avec les bonnes icônes
    previousButton = new QPushButton(this);
    previousButton->setIcon(QIcon("/home/gaetan/Documents/c++/LecteurMP4/images/previous.png"));
    connect(previousButton, &QPushButton::clicked, playlist, &QMediaPlaylist::previous);

    playPauseButton = new QPushButton(this);
    connect(playPauseButton, &QPushButton::clicked, this, &MainWindow::setPlayPauseButtonState);
    playPauseButton->setIcon(QIcon("/home/gaetan/Documents/c++/LecteurMP4/images/play.png"));

    stopButton = new QPushButton(this);
    connect(stopButton, &QPushButton::clicked, player, &QMediaPlayer::stop);
    stopButton->setIcon(QIcon("/home/gaetan/Documents/c++/LecteurMP4/images/stop.png"));

    nextButton = new QPushButton(this);
    connect(nextButton, &QPushButton::clicked, playlist, &QMediaPlaylist::next);
    nextButton->setIcon(QIcon("/home/gaetan/Documents/c++/LecteurMP4/images/next.png"));

    auto *centralWidget = new QWidget(this);
    auto *layout = new QVBoxLayout();

    auto *playlistMedia = new QHBoxLayout();


    playlistMedia->addWidget(videoWidget);
    playlistMedia->addWidget(listWidget);
    layout->addLayout(playlistMedia);

    // Une HBox pour les boutons de controle
    auto *controlButtons = new QHBoxLayout();
    controlButtons->addWidget(previousButton);
    controlButtons->addWidget(playPauseButton);
    controlButtons->addWidget(stopButton);
    controlButtons->addWidget(nextButton);

    // Pour centrer les boutons de la HBox
    controlButtons->setAlignment(Qt::AlignCenter);

    layout->addLayout(controlButtons);

    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);

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
            listWidget->addItem(QFileInfo(file).fileName());
        }
    }

    player->play();
}

void MainWindow::setPlayPauseButtonState() {
    // On change l'état de la lecture et l'icone du bouton en fonction de l'état de la lecture
    if (player->state() == QMediaPlayer::PlayingState) {
        playPauseButton->setIcon(QIcon("/home/gaetan/Documents/c++/LecteurMP4/images/play.png"));
        player->pause();
    }
    else {
        playPauseButton->setIcon(QIcon("/home/gaetan/Documents/c++/LecteurMP4/images/pause.png"));
        player->play();
    }
}

void MainWindow::setCurrentRow(int index) {
    listWidget->setCurrentRow(index);
}

void MainWindow::setCurrentIndex(QListWidgetItem *item) {
    playlist->setCurrentIndex(listWidget->row(item));
}