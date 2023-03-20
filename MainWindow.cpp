#include <QFileDialog>
#include <QWidget>
#include <QStatusBar>
#include <QMenuBar>
#include <QToolBar>
#include <QAction>
#include <QCoreApplication>
#include "MainWindow.hpp"


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    player = new QMediaPlayer(this);
    videoWidget = new QVideoWidget(this);
    setCentralWidget(videoWidget);
    player->setVideoOutput(videoWidget);

    // Créer une action pour ouvrir un fichier
    QAction *openAction = new QAction(tr("Open"), this);
    connect(openAction, &QAction::triggered, this, &MainWindow::open);

    // Créer une barre de menu et ajouter l'action d'ouverture de fichier
    QMenu *fileMenu = menuBar()->addMenu(tr("File"));
    fileMenu->addAction(openAction);

}

void MainWindow::open()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Ouvrir un fichier"), QDir::homePath(), tr("Fichier Vidéo (*.mp4 *.avi)"));

    player->setMedia(QUrl::fromLocalFile(fileName));
    player->play();

}



