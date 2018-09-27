#include "browser.h"
#include <QApplication>
#include <QtCore/QDebug>
#include <QtNetwork/QTcpSocket>
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>
#include <QtCore/QJsonValue>

#include <QWebEngineProfile>
#include <QWebEngineCookieStore>

#include <iostream>

Browser::Browser()
    : QObject(), webPage(new QWebEnginePage(this)), commandListener(new RemoteCommandListener(this)) {

}

Browser::~Browser() {
    webPage->profile()->cookieStore()->deleteAllCookies();
    webPage->profile()->clearHttpCache();
}

bool Browser::startServer(uint _portNumber) {
    return commandListener->start(_portNumber);
}

void Browser::readCommand() {
    QTcpSocket* clientConnection = static_cast<QTcpSocket*>(sender());
    QJsonDocument d = QJsonDocument::fromJson(clientConnection->readAll());
    QString command = d.object().value("command").toString();
    QString commandData = d.object().value("command_data").toString();
    executeCommand(ClientCommand(command,commandData));

    clientConnection->write("success\r\n");
    clientConnection->waitForBytesWritten();
    clientConnection->close();
    clientConnection->disconnectFromHost();
}

void Browser::readClientReply() {
    QTcpSocket* clientConnection = tcpServer->nextPendingConnection();
    connect(clientConnection, &QAbstractSocket::disconnected, clientConnection, &QObject::deleteLater);
    connect(clientConnection, &QAbstractSocket::readyRead, this, &Browser::readCommand);
}

void Browser::executeCommand(const ClientCommand& command) {
    switch (command.type) {
        case CommandType::Goto: {
            gotoPage(command.data);
            break;
        }
        case CommandType::ExecuteScript: {
            executeScript(command.data);
            break;
        }
        case CommandType::CreatePdf: {
            createPdf(command.data);
            break;
        }
        default: {
            break;
        }
    }
}

void Browser::gotoPage(const QString& commandData) {
    webPage->load(QUrl(commandData));
}

void Browser::executeScript(const QString& commandData) {
    webPage->runJavaScript(commandData);
}

void Browser::createPdf(const QString& commandData) {
    webPage->printToPdf(commandData);
}


