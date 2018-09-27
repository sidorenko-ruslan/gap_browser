#include <QApplication>
#include "browser.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    QCoreApplication::setApplicationName("gap browser");
    QCoreApplication::setApplicationVersion("0.0.1");

    Browser browser();
    return app.exec();
}
