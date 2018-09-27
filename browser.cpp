#include "browser.h"
#include <QApplication>
#include <QtCore/QDebug>

Browser::Browser()
    : QObject(), webPage(new QWebEnginePage), tcpServer(nullptr) {

}


