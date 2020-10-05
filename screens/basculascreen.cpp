#include "basculascreen.h"
#include <QPushButton>
#include <QComboBox>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QSerialPortInfo>
#include <QSpinBox>
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
        for (const QSerialPortInfo &info : infos)
            m_serialPortComboBox->addItem(info.portName());
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

}
