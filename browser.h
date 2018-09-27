#ifndef BROWSER_H
#define BROWSER_H

#include <QWebEnginePage>
#include <QtNetwork/QTcpServer>

#include "remote_command_listener.h"

class Browser : public QObject {
    Q_OBJECT
public:
    explicit Browser();
    virtual ~Browser();
    bool startServer(uint _portNumber);
private slots:
    void executeCommand(const ClientCommand& command);
private:
    // Browser commands list
    void gotoPage(const QString& commandData);
    void createPdf(const QString& commandData);
    void executeScript(const QString& commandData);
    // --------------------

    QWebEnginePage* webPage;
    RemoteCommandListener* commandListener;
};

#endif // BROWSER_H
