#ifndef PORTSELECTOR_H
#define PORTSELECTOR_H

#include <QDialog>
#include <QDebug>
#include <QSerialPortInfo>
#include <QSerialPort>
#include <QtWidgets>

namespace Ui {
class PortSelector;
}

class PortSelector : public QDialog
{
    Q_OBJECT

public:
    explicit PortSelector(QWidget *parent = 0);
    ~PortSelector();

signals:
    void accepted(QString PortName,
                  QSerialPort::BaudRate baud,
                  QSerialPort::DataBits dataBits,
                  QSerialPort::FlowControl flow,
                  QSerialPort::Parity parity,
                  QSerialPort::StopBits stopBits);  //принять настройки порта

private slots:
    void on_buttonBox_accepted();

private:
    Ui::PortSelector *ui;
    QComboBox cb;
};

#endif // PORTSELECTOR_H
