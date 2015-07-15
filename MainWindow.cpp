#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    _portSelector = new PortSelector();
    _portListener = new PortListener();
//    craneWidget = new CraneWidget();

    _portSelector->show();
    connect(_portSelector, SIGNAL(accepted()),
            this, SLOT(show()));
    connect(_portSelector, SIGNAL(accepted(QString,QSerialPort::BaudRate,QSerialPort::DataBits,QSerialPort::FlowControl,QSerialPort::Parity,QSerialPort::StopBits)),
            _portListener, SLOT(setPortSettings(QString,QSerialPort::BaudRate,QSerialPort::DataBits,QSerialPort::FlowControl,QSerialPort::Parity,QSerialPort::StopBits)));
//    connect(this, SIGNAL(writeInSocket(QByteArray)),
//            _portListener, SLOT(writeInSocket(QByteArray&)));
//    connect(portListener, SIGNAL(receivedMessage(Element,quint8)),
//            this, SLOT(translateMessage(Element,quint8)));

//    connect(craneWidget, SIGNAL(signalPowerOn()),
//            this, SLOT(sendPowerOn()));
//    connect(craneWidget, SIGNAL(signalPowerOff()),
//            this, SLOT(sendPowerOff()));
//    connect(craneWidget, SIGNAL(signalLightOn()),
//            this, SLOT(sendLightOn()));
//    connect(craneWidget, SIGNAL(signalLightOff()),
//            this, SLOT(sendLightOff()));
//    connect(craneWidget, SIGNAL(temperatureHigh()),
//            this, SLOT(sendTemperatureHigh()));
//    connect(craneWidget, SIGNAL(temperatureNormal()),
//            this, SLOT(sendTemperatureNormal()));
//    connect(craneWidget, SIGNAL(hookIsWarning()),
//            this, SLOT(sendHookIsWarning()));
//    connect(craneWidget, SIGNAL(hookIsNormal()),
//            this, SLOT(sendHookIsNormal()));

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
//    delete craneWidget;
    delete ui;
}

//void MainWindow::translateMessage(Element el,quint8 mes)
//{
//    switch (el) {
//    case powerButton:
//        craneWidget->powerOn(mes);
//        break;
//    case lightButton:
//        craneWidget->lightOn(mes);
//        break;
//    case soundSignal:
//        craneWidget->soundSignalOn(mes);
//        break;
//    case pillarUp:
//        craneWidget->pillarUp(mes);
//        break;
//    case pillarDown:
//        craneWidget->pillarDown(mes);
//        break;
//    case derrickUp:
//        craneWidget->derrickUp(mes);
//        break;
//    case derrickDown:
//        craneWidget->derrickDown(mes);
//        break;
//    case outriggerUp:
//        craneWidget->outriggerUp(mes);
//        break;
//    case outriggerDown:
//        craneWidget->outriggerDown(mes);
//        break;
//    case telescopicUp:
//        craneWidget->telescopicUp(mes);
//        break;
//    case telescopicDown:
//        craneWidget->telescopicDown(mes);
//        break;
//    case hookUp:
//        craneWidget->hookUp(mes);
//        break;
//    case hookDown:
//        craneWidget->hookDown(mes);
//        break;
//    case leftCrutchUp:
//        craneWidget->leftCrutchUp(mes);
//        break;
//    case leftCrutchDown:
//        craneWidget->leftCrutchDown(mes);
//        break;
//    case rightCrutchUp:
//        craneWidget->rightCrutchUp(mes);
//        break;
//    case rightCrutchDown:
//        craneWidget->rightCrutchDown(mes);
//        break;
//    default:
//        break;
//    }
//}


//void MainWindow::sendPowerOn()
//{
//    portListener->sendMessage(powerStatus, 0x01);
//}

//void MainWindow::sendPowerOff()
//{
//    portListener->sendMessage(powerStatus, 0x00);
//}

//void MainWindow::sendLightOn()
//{
//    portListener->sendMessage(lightStatus, 0x01);
//}

//void MainWindow::sendLightOff()
//{
//    portListener->sendMessage(lightStatus, 0x00);
//}

//void MainWindow::sendTemperatureHigh()
//{
//    portListener->sendMessage(highTemperature, 0x01);
//}

//void MainWindow::sendTemperatureNormal()
//{
//    portListener->sendMessage(highTemperature, 0x00);
//}

//void MainWindow::sendHookIsWarning()
//{
//    portListener->sendMessage(hookWarning, 0x01);
//}

//void MainWindow::sendHookIsNormal()
//{
//    portListener->sendMessage(hookWarning, 0x00);
//}

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
