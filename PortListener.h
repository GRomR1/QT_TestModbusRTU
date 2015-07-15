#ifndef PORTLISTENER_H
#define PORTLISTENER_H

#include <QObject>
#include <QDebug>
#include <QSerialPort>
#include <QMessageBox>
#include "../Defines.h"

class PortListener : public QObject
{
    Q_OBJECT
public:
    explicit PortListener(QObject *parent = 0);

public slots:
    void setPortSettings(QString PortName,
                         QSerialPort::BaudRate baud,
                         QSerialPort::DataBits dataBits,
                         QSerialPort::FlowControl flow,
                         QSerialPort::Parity parity,
                         QSerialPort::StopBits stopBits);    //установка настроек порта
    void writeInSocket(QByteArray arr);            //отправка данных в порт

signals:
    void event(QString);                            //сигнал о событии
    void signalGetData(QByteArray);
    void connected(QString portName);
//    void clientConnected(QString name, QString address);
//                                                    //подключился клиент
private:
    QSerialPort             *_port;                 //последовательный порт
    QByteArray               _arr;
    void connectPort();                             //подключение к порту

private slots:
    void readSocket();                              //считывание данных из порта
    void reportClose();                             //сообщить о закрытии порта


};

#endif // PORTLISTENER_H
