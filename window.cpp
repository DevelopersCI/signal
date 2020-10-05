#include "dialog.h"

#include <QComboBox>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QSerialPortInfo>
#include <QSpinBox>
#include <QDebug>
#include "echoserver.h"
#include <QtCore/QCoreApplication>
#include <QJsonDocument>
#include <QJsonObject>
Dialog::Dialog(QWidget *parent) :
    QMainWindow(parent)    /*
        m_serialPortLabel(new QLabel(tr("Serial port:"))),
        m_serialPortComboBox(new QComboBox),
        m_waitResponseLabel(new QLabel(tr("Wait response, msec:"))),
        m_waitResponseSpinBox(new QSpinBox),
        m_requestLabel(new QLabel(tr("Request:"))),
        m_requestLineEdit(new QLineEdit(tr("Who are you?"))),
        m_trafficLabel(new QLabel(tr("No traffic."))),
        m_statusLabel(new QLabel(tr("Status: Not running."))),
        m_runButton(new QPushButton(tr("Start")))*/{

    m_serialPortLabel = new QLabel(this);
    m_serialPortLabel->setText(tr("Serial port:"));
    // m_serialPortLabel->setGeometry(10,20,20,25);

    m_serialPortComboBox = new QComboBox();
    m_waitResponseLabel = new QLabel();
    m_waitResponseLabel->setText(tr("Wait response, msec:"));

    m_waitResponseSpinBox = new QSpinBox();
    m_requestLineEdit = new QLineEdit();
    m_requestLineEdit->setText(tr("Who are you?"));
    m_trafficLabel = new QLabel();
    m_trafficLabel->setText(tr("Transaction: 0"
                               "\nQuantity: 0.000"
                               "\nType: kg"));
    m_statusLabel = new QLabel();
    m_statusLabel->setText(tr("Status: Not running."));
    start = new QPushButton();
    start->setText(tr("Start"));

    stop = new QPushButton();
    stop->setText(tr("Stop"));

    const auto infos = QSerialPortInfo::availablePorts();
    for (const QSerialPortInfo &info : infos)
        m_serialPortComboBox->addItem(info.portName());
    m_waitResponseSpinBox->setRange(0, 10000);
    m_waitResponseSpinBox->setValue(1000);


    QWidget *content = new QWidget;
    QGridLayout *mainLayout = new QGridLayout();
    mainLayout->addWidget(m_serialPortLabel,0,0,1,1);
    mainLayout->addWidget(m_serialPortComboBox,1,0,1,2);
    mainLayout->addWidget(m_waitResponseLabel,2,0,1,2);
    mainLayout->addWidget(m_waitResponseSpinBox,3,0,1,2);
    mainLayout->addWidget(m_trafficLabel,4,0,1,2);
    mainLayout->addWidget(m_statusLabel,5,0,1,2);
    mainLayout->addWidget(start);
    mainLayout->addWidget(stop);


            content->setLayout(mainLayout);

    setLayout(mainLayout);
    setCentralWidget(content);

    m_requestLineEdit->hide();
    m_serialPortComboBox->setFocus();
    bool debug = true;
    int port = 3500;
    server = new class EchoServer(port, debug);
    // QObject::connect(server, &EchoServer::closed, this, &QCoreApplication::quit);


    connect(server, &EchoServer::onClientConnected, this, &Dialog::onClient);
    connect(start, &QPushButton::clicked, this, &Dialog::transaction);
    connect(stop, &QPushButton::clicked, this, &Dialog::clientDesconect);
    connect(&m_thread, &MasterThread::response, this, &Dialog::showResponse);
    connect(&m_thread, &MasterThread::error, this, &Dialog::processError);
    connect(&m_thread, &MasterThread::timeout, this, &Dialog::processTimeout);
    //connect(&m_thread, &MasterThread::response,this,&serve-> (QString));
    //connect(&m_thread, &MasterThread::response,this,SLOT(server mensajerecibido(QString)));
}

void Dialog::onClient(const bool &s){
    if(s){
        clientConnect();
    } else {
        clientDesconect();
    }
}

void Dialog::clientConnect(){
    setControlsEnabled(false);
    m_statusLabel->setText(tr("Status: Running",
                              "\nconnected to port %1.")
                           .arg(m_serialPortComboBox->currentText()));
    m_thread.transaction(m_serialPortComboBox->currentText(),
                         m_waitResponseSpinBox->value(),
                         m_requestLineEdit->text());
}

void Dialog::clientDesconect(){
    qDebug() << "cliente desconectado";
    m_statusLabel->setText(tr("Status: Stop",
                              "\nconnected to port %1.")
                           .arg(m_serialPortComboBox->currentText()));
    m_thread.stopReading();
    start->setEnabled(false);
}

void Dialog::transaction()
{
    setControlsEnabled(false);
    start->setEnabled(false);
    m_statusLabel->setText(tr("Status: Running",
                              "\nconnected to port %1.")
                           .arg(m_serialPortComboBox->currentText()));
    m_thread.transaction(m_serialPortComboBox->currentText(),
                         m_waitResponseSpinBox->value(),
                         m_requestLineEdit->text());
}

void Dialog::showResponse(const QString &s)
{
    server->processTextMessage(s);
    setControlsEnabled(true);
    QJsonDocument temp = QJsonDocument::fromJson(s.toUtf8());

    QJsonObject jsonObj = temp.object();
    m_trafficLabel->setText(tr("Transaction: %1"
                               "\nQuantity: %2"
                               "\nType: %3")
                            .arg(++m_transactionCount)
                            .arg(jsonObj["quantity"].toString())
            .arg(jsonObj["type"].toString()));
}

void Dialog::processError(const QString &s)
{
    setControlsEnabled(true);
    m_statusLabel->setText(tr("Status: Not running, %1.").arg(s));
    m_trafficLabel->setText(tr("No traffic."));
}

void Dialog::processTimeout(const QString &s)
{
    setControlsEnabled(true);
    m_statusLabel->setText(tr("Status: Running, %1.").arg(s));
    m_trafficLabel->setText(tr("No traffic."));
}

void Dialog::setControlsEnabled(bool enable)
{
    start->setEnabled(enable);
    m_serialPortComboBox->setEnabled(enable);
    m_waitResponseSpinBox->setEnabled(enable);
    m_requestLineEdit->setEnabled(enable);
}
