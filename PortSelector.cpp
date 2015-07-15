#include "PortSelector.h"
#include "ui_PortSelector.h"

PortSelector::PortSelector(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PortSelector)
{
    ui->setupUi(this);
    //получение доступных последовательных портов в системе
    QList<QSerialPortInfo> ports =	QSerialPortInfo::availablePorts();
    foreach(QSerialPortInfo port, ports)
    {
        ui->_comboBoxPortName->addItem(port.portName());
    }

    //запись возможных скоростей передачи данных
    // "2400" << "4800" << "9600" << "14400" << "19200" << "38400" << "57600" << "115200"

    //запись возможных типов контроля передачи
    // "OFF" << "HARDWARE" << "XON/XOFF";

    //запись возможных паритетов
    // "NONE" << "ODD" << "EVEN" << "MARK" << "SPACE";

    //запись возможных битов данных
    // "5" << "6" << "7" << "8";

    //запись возможных стоповых битов
    // "1" << "1.5" << "2";
    setWindowFlags(Qt::WindowCloseButtonHint);
}

PortSelector::~PortSelector()
{
    delete ui;
}

void PortSelector::on_buttonBox_accepted()
{
    QString portName = ui->_comboBoxPortName->currentText();
    QSerialPort::BaudRate baud = QSerialPort::BaudRate(ui->_comboBoxBaudRate->currentText().toInt());
    QSerialPort::DataBits dataBits = QSerialPort::DataBits(ui->_comboBoxDataBits->currentText().toInt());
    QSerialPort::FlowControl flow = QSerialPort::FlowControl(ui->_comboBoxFlowControl->currentIndex());
    QSerialPort::Parity parity = QSerialPort::Parity((ui->_comboBoxParity->currentIndex()>0? ui->_comboBoxParity->currentIndex()+1: ui->_comboBoxParity->currentIndex()));

    QSerialPort::StopBits stopBits;
    switch(ui->_comboBoxStopBits->currentIndex())
    {
    case 0:
        stopBits = QSerialPort::StopBits(1);
        break;
    case 1:
        stopBits = QSerialPort::StopBits(3);
        break;
    case 2:
        stopBits = QSerialPort::StopBits(2);
        break;
    default:
        stopBits = QSerialPort::StopBits(-1);
        break;
    }

    emit accepted(portName,
                  baud,
                  dataBits,
                  flow,
                  parity,
                  stopBits);
    this->accept();
}
