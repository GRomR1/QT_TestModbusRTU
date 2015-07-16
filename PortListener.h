#ifndef PORTLISTENER_H
#define PORTLISTENER_H

#include <QObject>
#include <QDebug>
#include <QSerialPort>
#include <QMessageBox>
#include "../Defines.h"
#include <libmodbus-3.0.6/src/modbus.h>
#define SLAVE_ID 1

class PortListener : public QObject
{
    Q_OBJECT
public:
    explicit PortListener(QObject *parent = 0);
    ~PortListener();

public slots:
    void setPortSettings(QString portName,
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

private slots:
    void readSocket();                              //считывание данных из порта
    void reportClose();                             //сообщить о закрытии порта
                                     //подключился клиент
private:
    void connectPort();                             //подключение к порту
    QSerialPort             *_port;                 //последовательный порт
    QByteArray               _arr;
    modbus_t                *_mb;
    QString                 _location;


};

#endif // PORTLISTENER_H
