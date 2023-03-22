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