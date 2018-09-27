#ifndef BROWSER_H
#define BROWSER_H

#include <QWebEnginePage>
#include <QtNetwork/QTcpServer>

class Browser : public QObject {
    Q_OBJECT
public:
    explicit Browser();
private:
    QWebEnginePage* webPage;
    QTcpServer* tcpServer;
};

#endif // BROWSER_H
