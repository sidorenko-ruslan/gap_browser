#ifndef BROWSER_H
#define BROWSER_H

#include <QWebEnginePage>
#include <QtNetwork/QTcpServer>

enum class CommandType {
    Goto,
    ExecuteScript,
    CreatePdf,
    Unknown
};

struct ClientCommand {
    explicit ClientCommand(const QString& _type, const QString& _data): data(_data) {
        if (_type == "goto") {
            type = CommandType::Goto;
        }
        else if (_type == "script") {
            type = CommandType::ExecuteScript;
        }
        else if (_type == "pdf") {
            type = CommandType::CreatePdf;
        }
        else {
            type = CommandType::Unknown;
        }
    }
    CommandType type;
    QString data;
};

class Browser : public QObject {
    Q_OBJECT
public:
    explicit Browser(uint _portNumber);
    virtual ~Browser();
    bool startServer();
private slots:
    void readCommand();
private:
    void executeCommand(const ClientCommand& command);

    // Browser commands list
    void gotoPage(const QString& commandData);
    void createPdf(const QString& commandData);
    void executeScript(const QString& commandData);

    // --------------------

    QWebEnginePage* webPage;
    QTcpServer* tcpServer;
    uint portNumber;
};

#endif // BROWSER_H
