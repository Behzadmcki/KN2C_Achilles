#include "xnetwork.h"

XNetwork::XNetwork(QObject *parent) : QObject(parent)
{
    socket=new QUdpSocket(this);
    connect(socket,SIGNAL(readyRead()),this,SLOT(readyRead()));

}



void XNetwork::send(QByteArray data)
{
    socket->flush();
    socket->writeDatagram(data,clientHostAddress,clientPort);
    qDebug()<<data;



}

void XNetwork::set_client_IP(QString MY_IP, long port)
{
    clientHostAddress.setAddress(MY_IP);
    clientPort=port;
}



void XNetwork::set_server_IP(QString MY_IP, long port)
{
    serverHostAddress.setAddress(MY_IP);
    serverPort=port;
    socket->bind(serverHostAddress,serverPort);

}



QByteArray XNetwork::get_data()
{
    return receiveDataReg;
}



int XNetwork::get_data_size()
{
    return receiveDataReg.size();
}

bool XNetwork::net_is_connect()
{

 //   return socket->isOpen();
    return (socket->state() == QTcpSocket::ConnectedState);

}


void XNetwork::readyRead()
{
    receiveDataReg.resize(socket->pendingDatagramSize());
    socket->readDatagram(receiveDataReg.data(),socket->pendingDatagramSize());
    socket->flush();
    emit receivedData(receiveDataReg,receiveDataReg.size());

}
