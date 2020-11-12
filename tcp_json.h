#ifndef TCP_JSON_H
#define TCP_JSON_H

#include <QTcpSocket>
#include <QObject>

class TCP_Json : public QObject
{
    Q_OBJECT

public:
    QTcpSocket* socket;
    TCP_Json();
    ~TCP_Json();

signals:
    // Signals for transfering data into QML
    void sendStatusToQml(QString error);
    void sendJsonToQml(QString JSON_str);

private slots:
    void error(QAbstractSocket::SocketError error);
    void connected();
    void read();
};
#endif // TCP_JSON_H
