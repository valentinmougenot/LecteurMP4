# Lecteur MP4

Ce projet a été réalisé en 2e année de BUT Informatique avec C++ et Qt réalisé par Gaëtan Jobst et Valentin Mougenot.

## Description

Cette application permet de lire des vidéos mp4, mais aussi des vidéos avi, et des fichiers mp3.

## Fonctionnalités

* Lecture de vidéos mp4, avi et fichiers mp3
* Affichage de la vidéo dans une fenêtre
* Ouvrir un fichier
* Ouvrir un dossier avec des fichiers mp4, avi et mp3
  * Playlist contenant les médias du dossier ouvert
* Boutons de contrôle de la vidéo
  * Play / Pause
  * Stop
  * Suivant
  * Précédent

## Installation et compilation (Linux debian)

### Prérequis

* Qt 5

``` bash
sudo apt install qtbase5-dev qt5-qmake --fix-missing
sudo apt-get install qtmultimedia5-dev
sudo apt-get install libqt5multimedia5-plugins
```

* CMake (optionnel)

``` bash
sudo apt install cmake
```

### Récupération du projet

``` bash
git clone https://github.com/valentinmougenot/LecteurMP4.git
cd LecteurMP4
```

#### Changer le chemin du dossier des images

`MainWindow.hpp` ligne 19 (ne pas oublier de mettre un `/` à la fin)

```cpp
static inline QString imagePath = QString("/chemin/vers/dossier/images/");
```

#### Compilation avec qmake

``` bash
qmake
make
```

#### Compilation avec CMake

``` bash
mkdir build
cd build
cmake ..
make
```

### Exécution

``` bash
./LecteurMP4
```
