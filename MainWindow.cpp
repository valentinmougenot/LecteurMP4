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
    setupMainElements();

    // Créer le menu pour ouvrir un fichier
    setupFileMenu();

    QPushButton *buttonAddFilePlaylist;
    QPushButton *buttonDeleteFilePlaylist;
    QPushButton *buttonClearPlaylist;
    setupPlaylistButtons(buttonAddFilePlaylist, buttonDeleteFilePlaylist, buttonClearPlaylist);

    setupControlButtons();

    auto *centralWidget = new QWidget(this);
    auto *layout = new QVBoxLayout();

    auto *playlistMedia = new QHBoxLayout();

    auto *videoVBox = new QVBoxLayout();
    videoVBox->addWidget(videoWidget);
    videoVBox->addWidget(slider);

    playlistMedia->addLayout(videoVBox);

    // La taille de la vidéo est 4x plus grande que celle de la playlist
    playlistMedia->setStretch(0, 4);
    playlistMedia->setStretch(1,1);

    layout->addLayout(playlistMedia);

    // Une HBox pour les boutons de controle
    auto *controlButtons = new QHBoxLayout();
    controlButtons->addWidget(previousButton);
    controlButtons->addWidget(playPauseButton);
    controlButtons->addWidget(stopButton);
    controlButtons->addWidget(nextButton);
    controlButtons->addWidget(volumeButton);
    controlButtons->addWidget(sliderVolume);

    auto *playlistVBox = new QVBoxLayout();
    playlistVBox->addWidget(listWidget);
    playlistVBox->addWidget(buttonClearPlaylist);
    playlistVBox->addWidget(buttonDeleteFilePlaylist);
    playlistVBox->addWidget(buttonAddFilePlaylist);

    playlistMedia->addLayout(playlistVBox);

    // Pour centrer les boutons de la HBox
    controlButtons->setAlignment(Qt::AlignCenter);

    layout->addLayout(controlButtons);

    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);
}

void MainWindow::setupControlButtons() {
    sliderVolume = new QSlider();
    sliderVolume->setOrientation(Qt::Horizontal);
    sliderVolume->setMaximumWidth(100);
    sliderVolume->setValue(100);
    connect(player, &QMediaPlayer::volumeChanged, sliderVolume, &QSlider::setValue);
    connect(sliderVolume, &QSlider::sliderMoved, player, &QMediaPlayer::setVolume);

    // Créer les boutons de contrôle avec les bonnes icônes
    previousButton = new QPushButton(this);
    previousButton->setIcon(QIcon(imagePath + "previous.png"));
    previousButton->setFixedSize(80, 50);
    connect(previousButton, &QPushButton::clicked, playlist, &QMediaPlaylist::previous);

    playPauseButton = new QPushButton(this);
    playPauseButton->setIcon(QIcon(imagePath + "play.png"));
    playPauseButton->setFixedSize(80, 50);
    connect(playPauseButton, &QPushButton::clicked, this, &MainWindow::setPlayPauseButtonState);

    stopButton = new QPushButton(this);
    stopButton->setIcon(QIcon(imagePath + "stop.png"));
    stopButton->setFixedSize(80, 50);
    connect(stopButton, &QPushButton::clicked, player, &QMediaPlayer::stop);

    nextButton = new QPushButton(this);
    nextButton->setIcon(QIcon(imagePath + "next.png"));
    nextButton->setFixedSize(80, 50);
    connect(nextButton, &QPushButton::clicked, playlist, &QMediaPlaylist::next);

    volumeButton = new QPushButton(this);
    volumeButton->setIcon(QIcon(imagePath + "volume.png"));
    volumeButton->setFixedSize(40, 40);
    connect(volumeButton, &QPushButton::clicked, this, &MainWindow::setVolumeButtonState);
}

void MainWindow::setupPlaylistButtons(QPushButton *&buttonAddFilePlaylist, QPushButton *&buttonDeleteFilePlaylist, QPushButton *&buttonClearPlaylist) const {
    buttonAddFilePlaylist= new QPushButton(tr("Ajouter un média à la playlist"));
    buttonDeleteFilePlaylist= new QPushButton(tr("Supprimer un média de la playlist"));
    buttonClearPlaylist= new QPushButton(tr("Vider la playlist"));// Créer le bouton pour ajouter un fichier à la playlist
    connect(buttonAddFilePlaylist, &QPushButton::clicked, this, &MainWindow::addFileToPlaylist);

    // Créer le bouton pour supprimer un fichier de la playlist
    connect(buttonDeleteFilePlaylist, &QPushButton::clicked, this, &MainWindow::deleteFileFromPlaylist);

    // Créer le bouton pour vider la playlist
    connect(buttonClearPlaylist, &QPushButton::clicked, this, &MainWindow::clearPlaylist);
}

void MainWindow::setupFileMenu() const {
    // Créer une action pour ouvrir un fichier
    auto *openAction = new QAction(tr("Open"));
    connect(openAction, &QAction::triggered, this, &MainWindow::open);

    // Créer une action pour ouvrir un dossier
    auto *openDirectoryAction = new QAction(tr("Open Directory"));
    connect(openDirectoryAction, &QAction::triggered, this, &MainWindow::openDirectory);

    // Créer une barre de menu et ajouter les actions d'ouverture de fichier et de dossier
    QMenu *fileMenu = menuBar()->addMenu(tr("File"));
    fileMenu->addAction(openAction);
    fileMenu->addAction(openDirectoryAction);
}

void MainWindow::setupMainElements() {
    player = new QMediaPlayer(this);
    playlist = new QMediaPlaylist(this);
    videoWidget = new QVideoWidget(this);
    player->setVideoOutput(videoWidget);
    player->setPlaylist(playlist);

    // Créer la liste qui contient toutes les vidéos
    listWidget = new QListWidget(this);
    listWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    connect(playlist, &QMediaPlaylist::currentIndexChanged, this, &MainWindow::setCurrentRow);
    connect(listWidget, &QListWidget::itemDoubleClicked, this, &MainWindow::setCurrentIndex);

    // Créer le slider de progression de la vidéo
    slider = new QSlider();
    slider->setOrientation(Qt::Horizontal);
    connect(player, &QMediaPlayer::durationChanged, slider, &QSlider::setMaximum);
    connect(player, &QMediaPlayer::positionChanged, slider, &QSlider::setValue);
    connect(slider, &QSlider::sliderMoved, player, &QMediaPlayer::setPosition);
}

void MainWindow::open()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Ouvrir un fichier"), QDir::homePath(), tr("Fichier Vidéo (*.mp4 *.mp3 *.avi)"));

    clearPlaylist();

    playlist->addMedia(QUrl::fromLocalFile(fileName));
    listWidget->addItem(QFileInfo(fileName).fileName());
    player->play();
}

void MainWindow::openDirectory()
{
    QString directoryName = QFileDialog::getExistingDirectory(this, tr("Sélectionner un dossier"), QDir::homePath());

    clearPlaylist();

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
        playPauseButton->setIcon(QIcon(imagePath + "play.png"));
        player->pause();
    }
    else {
        playPauseButton->setIcon(QIcon(imagePath + "pause.png"));
        player->play();
    }
}

void MainWindow::setCurrentRow(int index) {
    listWidget->setCurrentRow(index);
}

void MainWindow::setCurrentIndex(QListWidgetItem *item) {
    playlist->setCurrentIndex(listWidget->row(item));
}

void MainWindow::addFileToPlaylist(){
    QString fileName = QFileDialog::getOpenFileName(this, tr("Ouvrir un fichier"), QDir::homePath(), tr("Fichier Vidéo (*.mp4 *.mp3 *.avi)"));
    playlist->addMedia(QUrl::fromLocalFile(fileName));
    listWidget->addItem(QFileInfo(fileName).fileName());
}

void MainWindow::clearPlaylist(){
    playlist->clear();
    listWidget->clear();
}

void MainWindow::deleteFileFromPlaylist(){
    int i = listWidget->currentRow();
    playlist->removeMedia(i);
    listWidget->takeItem(i);
}

void MainWindow::setVolumeButtonState() {
    // On change l'état du volume et du slider et de l'icone en fonction du volume
    if (player->isMuted()) {
        volumeButton->setIcon(QIcon(imagePath + "volume.png"));
        player->setMuted(false);
        sliderVolume->setValue(player->volume());
    }
    else {
        volumeButton->setIcon(QIcon(imagePath + "mute.png"));
        player->setMuted(true);
        sliderVolume->setValue(0);
    }
}