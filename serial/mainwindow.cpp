#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    SPort = new QSerialPort(this);
    SPortInfo = new QSerialPortInfo();
    connect(SPort, SIGNAL(readyRead()), this, SLOT(receiveData()));
    //combo box 下拉菜单触发
    ui->comboBox_ports->installEventFilter(this);
    SerialPortInit();
    //限制textbrowser行数
    ui->textBrowser->document()->setMaximumBlockCount(10000);
}

MainWindow::~MainWindow()
{
    delete SPort;
    delete SPortInfo;
    delete time_event;
    delete ui;
}

void MainWindow::SerialPortInit()
{
    // 添加扫描串口
    QList<QSerialPortInfo> ports_available  = SPortInfo->availablePorts();
    foreach (QSerialPortInfo port_info,ports_available)
    {
        MainWindow::ui->comboBox_ports->addItem(port_info.portName());
    }
    // 添加波特率
    QStringList portDatas = (QStringList() <<"115200"<< "1200"<<"2400"<<"4800"<<"9600"<<"19200"<<"38400"<<"57600");
    MainWindow::ui->comboBox_bauds->addItems(portDatas);
    //添加数据位
    portDatas.clear();
    portDatas = (QStringList() << "8"<<"7"<<"6"<<"5");
    MainWindow::ui->comboBox_dataBits->addItems(portDatas);
    //添加停止位
    portDatas.clear();
    portDatas = (QStringList() << "1"<<"1.5"<<"2");
    MainWindow::ui->comboBox_stopBits->addItems(portDatas);
    //添加校验位
    portDatas.clear();
    portDatas = (QStringList() << "None"<<"Even"<<"Odd"<<"Space"<<"Mark");
    MainWindow::ui->comboBox_parity->addItems(portDatas);
    //添加流控
    portDatas.clear();
    portDatas = (QStringList() << "None"<<"Hardware"<<"Software");
    MainWindow::ui->comboBox_flowCtrl->addItems(portDatas);
    if(ports_available.size()>0)SPort->setPort(ports_available[0]);
    SPort->setBaudRate(QSerialPort::Baud115200);
    SPort->setDataBits(QSerialPort::Data8);
    SPort->setStopBits(QSerialPort::OneStop);
    SPort->setParity(QSerialPort::NoParity);
    SPort->setFlowControl(QSerialPort::NoFlowControl);
}

void MainWindow::on_pushButton_released()
{
    if(MainWindow::ui->pushButton->isChecked())
    {
        ui->comboBox_ports->setEnabled(false);
        ui->comboBox_bauds->setEnabled(false);
        ui->comboBox_stopBits->setEnabled(false);
        ui->comboBox_parity->setEnabled(false);
        ui->comboBox_dataBits->setEnabled(false);
        ui->comboBox_flowCtrl->setEnabled(false);
        MainWindow::ui->pushButton->setText("已连接");
        if(!SPort->open(QIODevice::ReadWrite))
        {
            QMessageBox::critical(this,"错误","打开串口失败","关闭");
            ui->comboBox_ports->setEnabled(true);
            ui->comboBox_bauds->setEnabled(true);
            ui->comboBox_stopBits->setEnabled(true);
            ui->comboBox_parity->setEnabled(true);
            ui->comboBox_dataBits->setEnabled(true);
            ui->comboBox_flowCtrl->setEnabled(true);
            ui->pushButton->setChecked(false);
            ui->pushButton->setText("已关闭");
        }
        else
        {
            ui->textBrowser->clear();
        }
    }
    else
    {
        ui->comboBox_ports->setEnabled(true);
        ui->comboBox_bauds->setEnabled(true);
        ui->comboBox_stopBits->setEnabled(true);
        ui->comboBox_parity->setEnabled(true);
        ui->comboBox_dataBits->setEnabled(true);
        ui->comboBox_flowCtrl->setEnabled(true);
        MainWindow::ui->pushButton->setText("已关闭");
        SPort->close();
    }
}

bool MainWindow::eventFilter(QObject *obj,QEvent *event)
{
    if(event->type() == QEvent::MouseButtonPress)
    {
        if(obj == MainWindow::ui->comboBox_ports)
        {
            QComboBox *combox = qobject_cast<QComboBox *>(obj);
            // 添加扫描串口
            combox->clear();
            QList<QSerialPortInfo> ports_available  = SPortInfo->availablePorts();
            foreach (QSerialPortInfo port_info,ports_available)
            {
                combox->addItem(port_info.portName());
            }
        }

    }
    return QWidget::eventFilter(obj,event);
}

void MainWindow::on_comboBox_ports_currentIndexChanged(int index)
{
    SPort->setPortName(ui->comboBox_ports->itemText(index));
}


void MainWindow::on_comboBox_bauds_currentIndexChanged(int index)
{
    if (ui->comboBox_bauds->itemText(index) == "1200")
        SPort->setBaudRate(QSerialPort::Baud1200);
    else if (ui->comboBox_bauds->itemText(index) == "2400")
        SPort->setBaudRate(QSerialPort::Baud2400);
    else if (ui->comboBox_bauds->itemText(index) == "4800")
        SPort->setBaudRate(QSerialPort::Baud4800);
    else if (ui->comboBox_bauds->itemText(index) == "9600")
        SPort->setBaudRate(QSerialPort::Baud9600);
    else if (ui->comboBox_bauds->itemText(index) == "19200")
        SPort->setBaudRate(QSerialPort::Baud19200);
    else if (ui->comboBox_bauds->itemText(index) == "38400")
        SPort->setBaudRate(QSerialPort::Baud38400);
    else if (ui->comboBox_bauds->itemText(index) == "57600")
        SPort->setBaudRate(QSerialPort::Baud57600);
    else if (ui->comboBox_bauds->itemText(index) == "115200")
        SPort->setBaudRate(QSerialPort::Baud115200);
    else
        SPort->setBaudRate(QSerialPort::Baud9600);
}

void MainWindow::on_comboBox_dataBits_currentIndexChanged(int index)
{
    if(ui->comboBox_dataBits->itemText(index) == "8")
        SPort->setDataBits(QSerialPort::Data8);
    else if(ui->comboBox_dataBits->itemText(index) == "7")
        SPort->setDataBits(QSerialPort::Data7);
    else if(ui->comboBox_dataBits->itemText(index) == "6")
        SPort->setDataBits(QSerialPort::Data6);
    else if(ui->comboBox_dataBits->itemText(index) == "5")
        SPort->setDataBits(QSerialPort::Data5);
    else
        SPort->setDataBits(QSerialPort::Data8);
}

void MainWindow::on_comboBox_stopBits_currentIndexChanged(int index)
{
    if (ui->comboBox_stopBits->itemText(index)=="1")
        SPort->setStopBits(QSerialPort::OneStop);
    else if (ui->comboBox_stopBits->itemText(index)=="1.5")
        SPort->setStopBits(QSerialPort::OneAndHalfStop);
    else if (ui->comboBox_stopBits->itemText(index)=="2")
        SPort->setStopBits(QSerialPort::TwoStop);
    else
        SPort->setStopBits(QSerialPort::OneStop);
}

void MainWindow::on_comboBox_parity_currentIndexChanged(int index)
{
    if (ui->comboBox_parity->itemText(index) == "None")
        SPort->setParity(QSerialPort::NoParity);
    else if (ui->comboBox_parity->itemText(index) == "Even")
        SPort->setParity(QSerialPort::EvenParity);
    else if (ui->comboBox_parity->itemText(index) == "Odd")
        SPort->setParity(QSerialPort::OddParity);
    else if (ui->comboBox_parity->itemText(index) == "Space")
        SPort->setParity(QSerialPort::SpaceParity);
    else if (ui->comboBox_parity->itemText(index) == "Mark")
        SPort->setParity(QSerialPort::MarkParity);
    else
        SPort->setParity(QSerialPort::NoParity);
}

void MainWindow::on_comboBox_flowCtrl_currentIndexChanged(int index)
{
    if (ui->comboBox_flowCtrl->itemText(index) == "None")
        SPort->setFlowControl(QSerialPort::NoFlowControl);
    else if (ui->comboBox_flowCtrl->itemText(index) == "Hardware")
        SPort->setFlowControl(QSerialPort::HardwareControl);
    else if (ui->comboBox_flowCtrl->itemText(index) == "Software")
        SPort->setFlowControl(QSerialPort::SoftwareControl);
    else
        SPort->setFlowControl(QSerialPort::NoFlowControl);
}



void MainWindow::on_lineEdit_input_returnPressed()
{
    QString input = ui->lineEdit_input->text();
    if(SPort->isOpen())
    {
        SPort->write(input.toLocal8Bit().data());
        ui->lineEdit_input->clear();
    }
    else
        QMessageBox::critical(this,"错误","串口未打开","关闭");
}

void MainWindow::receiveData()
{
        if(SPort->isOpen()&&SPort->bytesAvailable())
        {
            QByteArray recvData = SPort->readAll();
            //删除接收到的负数(为解决，接收到的数据位-91)和空格
            recvData = recvData.trimmed()+"\r\n";
            this->ui->textBrowser->insertPlainText( QString(recvData));
            QTextCursor cursor = ui->textBrowser->textCursor();
            cursor.movePosition(QTextCursor::End);
            this->ui->textBrowser->setTextCursor(cursor);
        }
        else
        {
            Sleep(1);
        }
}

void MainWindow::onClickClear()
{
    ui->textBrowser->clear();
}
