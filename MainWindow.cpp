#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    _portSelector = new PortSelector();
    _portListener = new PortListener();

    _portSelector->show();
    connect(_portSelector, SIGNAL(accepted()),
            this, SLOT(show()));
    connect(_portSelector, SIGNAL(accepted(QString,QSerialPort::BaudRate,QSerialPort::DataBits,QSerialPort::FlowControl,QSerialPort::Parity,QSerialPort::StopBits)),
            _portListener, SLOT(setPortSettings(QString,QSerialPort::BaudRate,QSerialPort::DataBits,QSerialPort::FlowControl,QSerialPort::Parity,QSerialPort::StopBits)));
    connect(_portListener, SIGNAL(signalGetData(QByteArray)),
            this, SLOT(readFromPort(QByteArray)));
    connect(_portListener, SIGNAL(connected(QString)),
            this, SLOT(setWindowTitle(QString)));
    connect(ui->actionSettings_port, SIGNAL(triggered()),
            _portSelector, SLOT(show()));

}

MainWindow::~MainWindow()
{
    delete _portSelector;
    delete _portListener;
    delete ui;
}

void MainWindow::on_actionAbout_triggered()
{
    QString text;
    text.append(tr("<p><h3>Эмулятор крана</h3></p>"));
    text.append(tr("<p>Программу разработал <a href='https://www.blogger.com/profile/05001160230860564687'>Гайнанов Руслан</a>, студент гр.ЭВТ-11, ПНИПУ</p>"));
    text.append(tr("<p><br />Связаться с автором: <a href='mailto:ruslan.r.gainanov@gmail.com'>ruslan.r.gainanov@gmail.com</a></p>"));
    QMessageBox::about(this, tr("About"), text);
}

void MainWindow::on__plainTextEditWrite_textChanged()
{
    if(_currentWriteText.size()<ui->_plainTextEditWrite->toPlainText().size())
    {
        QString str = ui->_plainTextEditWrite->toPlainText();
        str.remove(0,str.size()-1);
        qDebug() << str;
        _portListener->writeInSocket(str.toLocal8Bit());
    }
    _currentWriteText=ui->_plainTextEditWrite->toPlainText();
}

void MainWindow::readFromPort(QByteArray arr)
{
    ui->_plainTextEditRead->setPlainText(ui->_plainTextEditRead->toPlainText()+QString(arr));
}

void MainWindow::on__pushButtonMB_clicked()
{
    modbus_t *mb;
    uint16_t tab_reg[32]={};
    mb =  modbus_new_rtu("\\\\.\\COM1", 9600, 'N', 8, 1);
    if (mb == NULL)
    {
            qDebug() << "Unable to allocate libmodbus context\n";
    }
//    qDebug() << "mode: " << modbus_rtu_set_serial_mode(mb, MODBUS_RTU_RS232);
    if (modbus_connect(mb) == -1) {
        qDebug() << "Connection failed: %s\n" << modbus_strerror(errno);
        modbus_free(mb);
        return;
    }
    if (modbus_set_slave(mb, 1) == -1) //MODBUS_BROADCAST_ADDRESS
    {
        qDebug() << "Set slave failed: %s\n" << modbus_strerror(errno);
        modbus_free(mb);
        return;
    }
    /* Read 10 registers from the address 0 */
    int rc = modbus_read_registers(mb, 0, 10, tab_reg);
    if (rc == -1) {
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

    modbus_close(mb);
    modbus_free(mb);
}
