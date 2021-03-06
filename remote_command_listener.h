#ifndef REMOTE_COMMAND_LISTENER_H
#define REMOTE_COMMAND_LISTENER_H
#include <QtNetwork/QTcpServer>
#include "global.h"

class RemoteCommandListener final : public QObject {
    Q_OBJECT
public:
    explicit RemoteCommandListener(QObject* parent = nullptr);
    virtual ~RemoteCommandListener();
    bool start(uint _portNumber);
signals:
    void commandReceived(const ClientCommand& command);
private slots:
    void handleConnection();
    void readCommand();

private:
    QTcpServer* tcpServer;
}

#endif // REMOTE_COMMAND_LISTENER_H
