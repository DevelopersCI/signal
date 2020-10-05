#include "printerscreen.h"
#include <QPushButton>
#include <QComboBox>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QSerialPortInfo>
#include <QSpinBox>
PrinterScreen::PrinterScreen(QWidget *parent)
    : QWidget(parent)
{
        m_serialPortLabel = new QLabel(this);
        m_serialPortLabel->setText("Impresora");
        m_serialPortComboBox = new QComboBox();
        start = new QPushButton();
        start->setText("Start");

        QWidget *centralWidget = new QWidget(this);
        QGridLayout *mainLayout = new QGridLayout();
        mainLayout->addWidget(m_serialPortLabel,0,0,Qt::AlignTop);
        mainLayout->addWidget(m_serialPortComboBox,1,0,Qt::AlignTop);
        mainLayout->addWidget(start,2,0,Qt::AlignTop);
        centralWidget->setLayout(mainLayout);
        setLayout(mainLayout);

}
