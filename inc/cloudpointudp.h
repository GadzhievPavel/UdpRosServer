#ifndef CLOUDPOINTUDP_H
#define CLOUDPOINTUDP_H
#include <QObject>
#include <QUdpSocket>
#include <QTimer>
#include <QString>
#include <QTextCodec>
#include <QNetworkDatagram>
//#include <QNetworkDatagram>
#include <iostream>
using namespace std;

class CloudPointUDP: public QObject
{
  Q_OBJECT
public:
  explicit  CloudPointUDP(QObject *parent = 0 ):QObject(parent){
    socket = new QUdpSocket(this);
    if (socket->state() != socket->BoundState)
    {
      bool res = socket->bind(/*QHostAddress::AnyIPv4*/QHostAddress("192.168.0.104"), port);
      if(res)
      {
        qDebug() << "PASS";
        qDebug()<< socket->localAddress().toString();
        qDebug()<< socket->localPort();
        connect(socket, &QUdpSocket::readyRead,this, &CloudPointUDP::Read);
      }
      else
      {
        qDebug() << "FAIL";
      }
    }
  };

  ~CloudPointUDP(){};
  void setData(vector<QByteArray>& data);
  void sendPacket(vector<QByteArray>& data);

private:
  vector<QByteArray> data;
  QString clientAddress="127.0.0.1";
  QString serverAddress="192.168.0.104";
  int port=50001;
  int clientPort= 21333;
  QUdpSocket *socket;

public slots:
  void Read();
  void ReadTest();

};

#endif // CLOUDPOINTUDP_H
