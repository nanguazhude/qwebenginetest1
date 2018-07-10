#include "MainWindow.hpp"
#include <QApplication>

#include "XWebView.hpp"

int main(int argc, char *argv[]){
    QApplication app(argc, argv);

    XWebView view;
    view.show();

    return app.exec();
}
