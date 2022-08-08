#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QMessageBox>
#include <QTimer>
#include <thread>
#include <windows.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private slots:

    void on_pushButton_released();

    // https://blog.csdn.net/elikang/article/details/114693536
    bool eventFilter(QObject *,QEvent *);

    void on_comboBox_ports_currentIndexChanged(int index);

    void on_comboBox_bauds_currentIndexChanged(int index);

    void on_comboBox_dataBits_currentIndexChanged(int index);

    void on_comboBox_stopBits_currentIndexChanged(int index);

    void on_comboBox_parity_currentIndexChanged(int index);

    void on_comboBox_flowCtrl_currentIndexChanged(int index);

    void on_lineEdit_input_returnPressed();

    void receiveData();

    void onClickClear();
private:
    Ui::MainWindow *ui;
    QSerialPort *SPort;
    QSerialPortInfo *SPortInfo;
    QTimer *time_event;
    void SerialPortInit();
};

#endif // MAINWINDOW_H
