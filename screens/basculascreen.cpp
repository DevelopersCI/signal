#include "basculascreen.h"
#include <QPushButton>
#include <QComboBox>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QSerialPortInfo>
#include <QSpinBox>
#include <QJsonDocument>
#include <QJsonObject>
#include <QException>

BasculaScreen::BasculaScreen(QWidget *parent)
   : QWidget(parent)
{
    m_serialPortLabel = new QLabel(this);
    m_serialPortLabel->setText(tr("Serial port:"));

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
    qDebug() << "in bascula screen" << infos.length();
    for (const QSerialPortInfo &info : infos){
        qDebug() << "in for";
        m_serialPortComboBox->addItem(info.portName());
    }
    m_waitResponseSpinBox->setRange(0, 10000);
    m_waitResponseSpinBox->setValue(1000);



    QWidget *content = new QWidget(this);
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
    //this->setCentralWidget(content);
    m_requestLineEdit->hide();
    m_serialPortComboBox->setFocus();

    connect(&bascula, &Bascula::response, this, &BasculaScreen::showResponse);
    connect(&bascula, &Bascula::error, this, &BasculaScreen::processError);
    connect(&bascula, &Bascula::timeout, this, &BasculaScreen::processTimeout);
    connect(start, &QPushButton::clicked, this, &BasculaScreen::transaction);
    connect(stop, &QPushButton::clicked, this, &BasculaScreen::clientDesconect);

}

void BasculaScreen::transaction()
{
    setControlsEnabled(false);
    start->setEnabled(false);
    m_statusLabel->setText(tr("Status: Running",
                              "\nconnected to port %1.")
                           .arg(m_serialPortComboBox->currentText()));
    bascula.transaction(m_serialPortComboBox->currentText(),
                         m_waitResponseSpinBox->value(),
                         m_requestLineEdit->text());
}

void BasculaScreen::clientDesconect(){
    qDebug() << "cliente deconectado";
    m_statusLabel->setText(tr("Status: Stop",
                              "\nconnected to port %1.")
                           .arg(m_serialPortComboBox->currentText()));
    bascula.stopReading();
    start->setEnabled(false);
}
void BasculaScreen::showResponse(const QString &s)
{

    emit getInfobyBascula(s);
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

void BasculaScreen::setControlsEnabled(bool enable)
{
    start->setEnabled(enable);
    m_serialPortComboBox->setEnabled(enable);
    m_waitResponseSpinBox->setEnabled(enable);
    m_requestLineEdit->setEnabled(enable);
}

void BasculaScreen::processError(const QString &s)
{
    setControlsEnabled(true);
    m_statusLabel->setText(tr("Status: Not running, %1.").arg(s));
    m_trafficLabel->setText(tr("No traffic."));
}

void BasculaScreen::processTimeout(const QString &s)
{
    setControlsEnabled(true);
    m_statusLabel->setText(tr("Status: Running, %1.").arg(s));
    m_trafficLabel->setText(tr("No traffic."));
}
