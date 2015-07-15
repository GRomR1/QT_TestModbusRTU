#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "PortSelector.h"
#include "PortListener.h"
#include <QByteArray>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

//signals:
//    void writeInSocket(QByteArray&);

public slots:
//    void translateMessage(Element,quint8);


private slots:
//    void sendPowerOn();
//    void sendPowerOff();
//    void sendLightOn();
//    void sendLightOff();
//    void sendTemperatureHigh();
//    void sendTemperatureNormal();
//    void sendHookIsWarning();
//    void sendHookIsNormal();
    void on_actionAbout_triggered();                    //показ О программе
    void on__plainTextEditWrite_textChanged();
    void readFromPort(QByteArray arr);

    void on__pushButtonMB_clicked();

private:
    Ui::MainWindow      *ui;
    PortSelector        *_portSelector;
    PortListener        *_portListener;
    QString              _currentWriteText;

};

#endif // MAINWINDOW_H
