#include "serverscreen.h"
#include <QPushButton>
#include <QGridLayout>
#include <QGroupBox>
ServerScreen::ServerScreen(QWidget *parent)
    : QWidget(parent)
{
    port = new QSpinBox();
    port->setValue(3500);
    l_port = new QLabel();
    l_port->setText(tr("Puerto"));
    QPushButton *buton = new QPushButton();
    buton->setText("server");

    QWidget *centralWidget = new QWidget(this);
    QGridLayout *mainLayout = new QGridLayout();
    mainLayout->addWidget(l_port,0,0,Qt::AlignTop);
    mainLayout->addWidget(port,1,0,Qt::AlignTop);
    mainLayout->addWidget(buton,2,0,Qt::AlignTop);
    centralWidget->setLayout(mainLayout);
    setLayout(mainLayout);


}
