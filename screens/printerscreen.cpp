#include "printerscreen.h"
#include <QPushButton>
#include <QComboBox>
#include <QGridLayout>
#include <QLabel>
#include <QDebug>
#include <QPushButton>
#include <QPrinterInfo>
#include <QSpinBox>
#include <QImage>
#include <QPrinter>
#include <QPainter>
#include <QSystemTrayIcon>
PrinterScreen::PrinterScreen(QWidget *parent)
    : QWidget(parent)
{
    m_serialPortLabel = new QLabel("amir");
    pix = new QPixmap();

    m_serialPortLabel->setText("Impresora");
    m_serialPortComboBox = new QComboBox();
    start = new QPushButton();
    start->setText("Start");
    QWidget *centralWidget = new QWidget(this);
    QGridLayout *mainLayout = new QGridLayout();
    mainLayout->addWidget(m_serialPortLabel,0,0,Qt::AlignTop);
    mainLayout->addWidget(m_serialPortComboBox,1,0,Qt::AlignTop);
    mainLayout->addWidget(start,2,0,Qt::AlignTop);
    mainLayout->addWidget(start,2,0,Qt::AlignTop);
    centralWidget->setLayout(mainLayout);
    setLayout(mainLayout);



}

void PrinterScreen::setImg(QByteArray img)
{

    int count = 0;
    bool printconnect = false;
    QList <QPrinterInfo> info_list = QPrinterInfo :: availablePrinters ();
    foreach (QPrinterInfo info, info_list){
        count ++;
        qDebug() << "Printer _" << count << ":" << info.printerName () << "State:" << info.state ();

        // if(info.printerName() == printerName)
        // {
        if (info.state() == 0)
            qDebug()<< "Printer Idle";
        else if (info.state() == 1){
            qDebug()<< "Printer Active";
            printconnect = true;
            break;
        }
        else if (info.state() == 2)
            qDebug()<< "Printer Aborted";
        else if (info.state() == 3)
            qDebug()<< "Printer Error";
        else
            qDebug()<< "Printer Undefined Error";
        //}

    }
    if(printconnect){
        pix->loadFromData(img,"JPG");

        QPrinter printer(QPrinter::ScreenResolution);
        QPainter painter;
        printer.setPaperSize(QSizeF(80,105), QPrinter::Millimeter);
        printer.setFullPage(true);
        if (! painter.begin(&printer)) { // failed to open file
            qWarning("failed to open file, is it writable?");
            return;
        }
        painter.drawPixmap(0, 0, *pix);
        painter.end();
    } else {
         qDebug()<< "Menssage";
           emit this->notification();

    }
}
