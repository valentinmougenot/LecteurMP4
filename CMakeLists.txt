cmake_minimum_required(VERSION 3.24)
project(LecteurMP4)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(Qt5_DIR "/opt/homebrew/Cellar/qt@5/5.15.8_2/lib/cmake/Qt5")

find_package(Qt5 COMPONENTS
        Widgets
        Multimedia
        MultimediaWidgets
        Gui
        Core
        REQUIRED)

add_executable(LecteurMP4 main.cpp MainWindow.hpp MainWindow.cpp)

target_link_libraries(LecteurMP4 Qt5::Widgets Qt5::Multimedia Qt5::MultimediaWidgets Qt5::Gui Qt5::Core)