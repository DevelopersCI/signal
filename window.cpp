#include "window.h"
#include <QDebug>
#include <QCloseEvent>
#include "utils/server.h"
#include <QtCore/QCoreApplication>
#include <QAction>
#include <QMessageBox>
#include <QMenu>

Window::Window(QWidget *parent) :
    QMainWindow(parent),

    m_leftSideBar(new LeftSideBar),
    m_stackedLayout(new QStackedLayout),
    serverScreen(new ServerScreen),
    printerScreen(new PrinterScreen),
    basculaScreen(new BasculaScreen)
{
    qDebug() << "start app";
    createActions();
    createTrayIcon();
    server = new EchoServer(3500,true);


    QWidget *centralWidget = new QWidget();
    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);
    mainLayout->addWidget(m_leftSideBar);
    mainLayout->addLayout(m_stackedLayout);

    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);

    //m_stackedLayout->addWidget(serverScreen);

    m_stackedLayout->addWidget(printerScreen);
    m_stackedLayout->addWidget(basculaScreen);
    m_stackedLayout->setCurrentIndex(1);
    connect(m_leftSideBar, &LeftSideBar::buttonClicked, this, &Window::handleLeftSideBarChanged);
    connect(basculaScreen, &BasculaScreen::getInfobyBascula, this, &Window::setMessage);
    connect(printerScreen, &PrinterScreen::notification, this, &Window::notification);
    connect(server, &EchoServer::onClientConnected, this, &Window::onClient);
    connect(server, &EchoServer::binaryMessage, this, &Window::binaryMessage);
    connect(server, &EchoServer::turnOnOffBascula, this, &Window::turnOnOffBascula);
    connect(trayIcon, &QSystemTrayIcon::activated, this, &Window::iconActivated);
    trayIcon->setIcon(QIcon(":/assets/peso.svg"));
    setWindowIcon(QIcon(":/assets/peso.svg"));
    trayIcon->setToolTip(tr("By Amir Marin",
                            "\namisael.amir.misael@gmail.com"));
    trayIcon->show();

}

void Window::handleLeftSideBarChanged(int index)
{
    m_stackedLayout->setCurrentIndex(index);
}
void Window::onClient(const bool &s){
    //m_stackedLayout->setCurrentIndex(0);
    //m_leftSideBar->setChecked(0);
    /*if(s){
        clientConnect();
    } else {
       clientDesconect();
    }*/
}

void Window::turnOnOffBascula(const bool &s){
   if(s){
        startBascula();
    } else {
       stopBascula();
    }
}

void Window::startBascula(){
    basculaScreen->transaction();
    qDebug() << "Cliente Conectado";
    //setControlsEnabled(false);
    /*m_statusLabel->setText(tr("Status: Running",
                              "\nconnected to port %1.")
                           .arg(m_serialPortComboBox->currentText()));
    m_thread.transaction(m_serialPortComboBox->currentText(),
                         m_waitResponseSpinBox->value(),
                         m_requestLineEdit->text());*/
}


void Window::stopBascula(){
    basculaScreen->clientDesconect();
    qDebug() << "Cliente desconectado";
}



void Window::setMessage(QString msg)
{
    //qDebug() << "in window server" <<msg;
    server->sendMessage(msg);
}

void Window::binaryMessage(QByteArray message)
{
    printerScreen->setImg(message);
    qDebug() << "Binary Message received:" ;
    //qDebug() << "Binary Message received:" << message;
}

void Window::notification()
{

    QSystemTrayIcon::MessageIcon msgIcon = QSystemTrayIcon::MessageIcon(2);
    trayIcon->showMessage("Printer", "Can't connect to printer",msgIcon, 1000);

}










void Window::closeEvent(QCloseEvent *event)
{

    if (trayIcon->isVisible()) {
        /*
        QMessageBox::information(this, tr("Systray"),
                                 tr("The program will keep running in the "
                                    "system tray. To terminate the program, "
                                    "choose <b>Quit</b> in the context menu "
                                    "of the system tray entry."));*/
        hide();
        event->ignore();
    }
}


void Window::setIcon()
{

}

void Window::iconActivated(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason) {
    case QSystemTrayIcon::Trigger:
    case QSystemTrayIcon::DoubleClick:
        qDebug() << "click en inco";
        show();
        //iconComboBox->setCurrentIndex((iconComboBox->currentIndex() + 1) % iconComboBox->count());
        break;
    case QSystemTrayIcon::MiddleClick:
        showMessage();
        break;
    default:
        ;
    }
}

void Window::showMessage()
{
    /*showIconCheckBox->setChecked(true);
    int selectedIcon = typeComboBox->itemData(typeComboBox->currentIndex()).toInt();
    QSystemTrayIcon::MessageIcon msgIcon = QSystemTrayIcon::MessageIcon(selectedIcon);

    if (selectedIcon == -1) { // custom icon
        QIcon icon(iconComboBox->itemIcon(iconComboBox->currentIndex()));
        trayIcon->showMessage(titleEdit->text(), bodyEdit->toPlainText(), icon,
                          durationSpinBox->value() * 1000);
    } else {
        trayIcon->showMessage(titleEdit->text(), bodyEdit->toPlainText(), msgIcon,
                          durationSpinBox->value() * 1000);
    }*/
}

void Window::messageClicked()
{
    QMessageBox::information(nullptr, tr("Systray"),
                             tr("Sorry, I already gave what help I could.\n"
                                "Maybe you should try asking a human?"));
}

void Window::createActions()
{
    minimizeAction = new QAction(tr("Mi&nimize"), this);
    connect(minimizeAction, &QAction::triggered, this, &QWidget::hide);

    /* maximizeAction = new QAction(tr("Ma&ximize"), this);
    connect(maximizeAction, &QAction::triggered, this, &QWidget::showMaximized);
    */
    restoreAction = new QAction(tr("&Restore"), this);
    connect(restoreAction, &QAction::triggered, this, &QWidget::showNormal);

    quitAction = new QAction(tr("&Quit"), this);
    connect(quitAction, &QAction::triggered, qApp, &QCoreApplication::quit);
}

void Window::createTrayIcon()
{
    trayIconMenu = new QMenu(this);
    trayIconMenu->addAction(minimizeAction);
    //trayIconMenu->addAction(maximizeAction);
    trayIconMenu->addAction(restoreAction);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(quitAction);

    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setContextMenu(trayIconMenu);
}
