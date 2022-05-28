#include "inc/cloudpointudp.h"

void CloudPointUDP::Read(){
  QByteArray buffer;
  QHostAddress sender;
  quint16 senderPort;
  while (!socket->hasPendingDatagrams()) {
    cout<<"nixyia";
  }
  if(socket->hasPendingDatagrams()){
    buffer.fill(0,socket->pendingDatagramSize());
    socket->readDatagram(buffer.data(), buffer.size(),
                         &sender, &senderPort);
    clientAddress = sender.toIPv4Address();
    clientPort = senderPort;
    qDebug() << "Message from: " << sender.toString();
    qDebug() << "Message port: " << senderPort;
    if(buffer[0]=='p' && buffer[1] =='c'){
      CloudPointUDP::sendPacket(data);
    }
  }
}

void CloudPointUDP::ReadTest(){
  qDebug()<<"test init";
  while (socket->hasPendingDatagrams()) {
         QNetworkDatagram datagram = socket->receiveDatagram();
         //processTheDatagram(datagram);
         qDebug()<<" test";
     }
}
void CloudPointUDP::sendPacket(vector<QByteArray>& _data){
  for(int i = 0; i< _data.size(); i++){
    socket->writeDatagram(_data.at(i),QHostAddress(clientAddress),clientPort);
  }

}

void CloudPointUDP::setData(vector<QByteArray>& data){
  this->data = data;
}
