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

Browser::Browser(uint _portNumber)
    : QObject(), webPage(new QWebEnginePage), tcpServer(new QTcpServer(this)),
      portNumber(_portNumber) {

    connect(tcpServer,SIGNAL(newConnection()),this,SLOT(readCommand()));
}

Browser::~Browser() {
    tcpServer->close();
    webPage->profile()->cookieStore()->deleteAllCookies();
    webPage->profile()->clearHttpCache();
}

bool Browser::startServer() {
    if (!tcpServer->listen(QHostAddress::Any,portNumber)) {
        return false;
    }
    std::cout << "server started at port: 3000" << std::endl;
    return true;
}

void Browser::readCommand() {
    //QByteArray block;
    //QDataStream out(&block, QIODevice::WriteOnly);
    //out.setVersion(QDataStream::Qt_5_10);

    //out << "success\r\n";

    QTcpSocket* clientConnection = tcpServer->nextPendingConnection();

    connect(clientConnection, &QAbstractSocket::disconnected, clientConnection, &QObject::deleteLater);
    connect(clientConnection, &QAbstractSocket::readyRead, this, [this,&clientConnection]() {
        //QTcpSocket* clientConnection = static_cast<QTcpSocket*>(sender());
        QJsonDocument d = QJsonDocument::fromJson(clientConnection->readAll());
        QString command = d.object().value("command").toString();
        QString commandData = d.object().value("command_data").toString();
        executeCommand(ClientCommand(command,commandData));

        clientConnection->write("success\r\n");
        clientConnection->waitForBytesWritten();
        clientConnection->close();
        clientConnection->disconnectFromHost();
    });
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


