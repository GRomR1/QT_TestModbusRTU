#include "PortListener.h"

PortListener::PortListener(QObject *parent) :
    QObject(parent)
{
    _port = new QSerialPort();       //создание порта
    _port->open(QIODevice::NotOpen); //открытие порта
}

void PortListener::setPortSettings(QString PortName,
                                   QSerialPort::BaudRate baud,
                                   QSerialPort::DataBits dataBits,
                                   QSerialPort::FlowControl flow,
                                   QSerialPort::Parity parity,
                                   QSerialPort::StopBits stopBits)
{
    //установка параметров порта
    _port->setPortName(PortName);
    _port->setBaudRate(baud);
    _port->setDataBits(dataBits);
    _port->setFlowControl(flow);
    _port->setParity(parity);
    _port->setStopBits(stopBits);

    connectPort();    //соединение с портом
}

void PortListener::connectPort()
{
    //открытие порта
    if(_port->open(QIODevice::ReadWrite))
    {
        emit connected(_port->portName());
    };

    connect(_port, SIGNAL(readyRead()), this, SLOT(readSocket()));
    connect(_port, SIGNAL(aboutToClose()), this, SLOT(reportClose()));
}

void PortListener::readSocket()
{
    QByteArray arr = _port->readAll();
    qDebug() <<  "Read [" << arr.size() << "]: " << arr.toHex();
    emit signalGetData(arr);

}

//void PortListener::sendMessage(Element el, quint8 mes)
//{
//    QByteArray  arrBlock;
//    QDataStream out(&arrBlock, QIODevice::WriteOnly);
//    out << quint8(el) << mes;
//    writeInSocket(arrBlock);
//}

void PortListener::writeInSocket(QByteArray arr)
{
    if(_port->isOpen()&&_port->isWritable())
    {
        qDebug() << "write to port: " << arr.toHex();
        _port->write( arr.data(), arr.size() );
    }
}

void PortListener::reportClose()
{
    emit event(tr("Закрытие порта"));
    QMessageBox::information(0,tr("Внимание"),tr("Закрытие порта"));
}

//void PortListener::reportDsr(bool status)
//{
//    if(status)
//    {
//        emit event(tr("Устройство подключено"));
//        QMessageBox::information(0,tr("Внимание"),tr("Устройство подключено"));
//    }
//    else
//    {
//        emit event(tr("Устройство отключено"));
//        QMessageBox::information(0,tr("Внимание"),tr("Устройство отключено"));
//    }
//}
