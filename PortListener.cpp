#include "PortListener.h"

PortListener::PortListener(QObject *parent) :
    QObject(parent),
    _mb(0)
{
    _port = new QSerialPort();       //создание порта
    _port->open(QIODevice::NotOpen); //открытие порта

    uint16_t tab_reg[32]={};
}

PortListener::~PortListener()
{

    modbus_close(mb);
    modbus_free(mb);
}

void PortListener::setPortSettings(QString portName,
                                   QSerialPort::BaudRate baud,
                                   QSerialPort::DataBits dataBits,
                                   QSerialPort::FlowControl flow,
                                   QSerialPort::Parity parity,
                                   QSerialPort::StopBits stopBits)
{
    //установка параметров порта
    _port->setPortName(portName);
    _location="\\\\.\\"+portName;
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
//    if(_port->open(QIODevice::ReadWrite))
//    {
//        emit connected(_port->portName());
//    };
//    connect(_port, SIGNAL(readyRead()), this, SLOT(readSocket()));
//    connect(_port, SIGNAL(aboutToClose()), this, SLOT(reportClose()));

    if(_mb)
    {
        modbus_close(_mb);
        modbus_free(_mb);
    }
    _mb =  modbus_new_rtu(_location,
                         QString::number(_port->baudRate()),
                         (_port->parity()==0? 'N': (_port->parity()==2? 'E': (_port->parity()==3? 'O': ''))),
                         _port->dataBits(),
                         _port->stopBits());
    if(_mb == NULL)
            qDebug() << "Unable to allocate libmodbus context";
    if(modbus_connect(_mb) == -1)
    {
        qDebug() << "Connection failed: " << modbus_strerror(errno);
        modbus_free(_mb);
        return;
    }

    if(modbus_set_slave(_mb, SLAVE_ID) == -1)
    {
        qDebug() << "Set slave failed: " << modbus_strerror(errno);
        modbus_free(_mb);
        return;
    }

    /* Read 10 registers from the address 0 */
    int rc = modbus_read_registers(mb, 0, 10, tab_reg);
    if(rc == -1) {
        qDebug() << modbus_strerror(errno);
        return;
    }

    for(int i=0; i<10; i++)
    {
        qDebug() << i << ":" << tab_reg[i];
        tab_reg[i]++;
    }
    /* Write 10 registers from the address 0 */
    rc = modbus_write_registers(mb, 0, 10, tab_reg);
    if (rc == -1) {
        qDebug() << modbus_strerror(errno);
        return;
    }

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
