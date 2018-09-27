#include <QApplication>
#include "browser.h"
#include <iostream>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    QCoreApplication::setApplicationName("gap browser");
    QCoreApplication::setApplicationVersion("0.0.1");

    Browser browser(3000);
    if (!browser.startServer()) {
        std::cerr << "unable to start listen server!\n";
        return -1;
    }
    return app.exec();
}
