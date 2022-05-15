#ifndef XNETWORK_H
#define XNETWORK_H

#include <QObject>
#include <QByteArray>
#include <QUdpSocket>
#include <QTcpSocket>
#include <QDebug>


class XNetwork : public QObject
{

  Q_OBJECT
public:
    explicit XNetwork(QObject *parent = 0);

    void set_client_IP (QString VmyIP, long Vport);
    void set_server_IP (QString VmyIP, long Vport);
    QByteArray get_data ();
    int get_data_size ();
    bool net_is_connect ();

signals:
    void receivedData(QByteArray,int);

public slots:
     void readyRead();
     void send (QByteArray Vdata);

private:
    QUdpSocket* socket;
    QByteArray receiveDataReg;

    QHostAddress serverHostAddress;
    long serverPort;

    QHostAddress clientHostAddress;
    long clientPort;

};

#endif // XNETWORK_H
