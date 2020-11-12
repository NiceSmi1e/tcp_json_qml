#include "tcp_json.h"

//Initializing socket and signals for it
TCP_Json::TCP_Json()
{
    qDebug()<<"Initialized";
    socket = new QTcpSocket();
    connect(socket,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(error(QAbstractSocket::SocketError)));
    connect(socket,SIGNAL(connected()),this,SLOT(connected()));
    connect(socket,SIGNAL(readyRead()),this,SLOT(read()));
    socket->connectToHost("jsonplaceholder.typicode.com",80);
}

//Signal for error
void TCP_Json::error(QAbstractSocket::SocketError error)
{
    sendStatusToQml("Connection error");
    qDebug()<<error;
}

//Signal when socket is connected
void TCP_Json::connected()
{
    qDebug()<<"Connected";
    socket->write("GET /users HTTP/1.0\r\nHOST: jsonplaceholder.typicode.com\r\n\r\n"); //getting data from host
}

//Signal for reading data form socket
void TCP_Json::read()
{
    qDebug()<<"Read";
    QString received_data = "";
    while(socket->bytesAvailable()) {
        received_data.append(socket->readAll());
    }
    QString JSON_str = received_data.section("\r\n\r\n", 1); //cropping header
    qDebug()<<JSON_str;
    sendJsonToQml(JSON_str); //sending JSON to QML
    qDebug()<<"Done";
    socket->close();
}

TCP_Json::~TCP_Json()
{
}
