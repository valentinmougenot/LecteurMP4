#include <QApplication>
#include "MainWindow.hpp"


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QWidget *parent = nullptr; // ou spécifiez un parent si nécessaire
    MainWindow window(parent);
    window.show();

    return QApplication::exec();
}

