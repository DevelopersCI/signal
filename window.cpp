#include "window.h"
#include <QDebug>
#include <QCloseEvent>
#include "server.h"
#include <QtCore/QCoreApplication>
#include <QJsonDocument>
#include <QJsonObject>
#include <QAction>
#include <QMessageBox>
#include <QMenu>

Window::Window(QWidget *parent) :
    QMainWindow(parent),
    m_leftSideBar(new LeftSideBar),
    m_stackedLayout(new QStackedLayout),
    serverScreen(new ServerScreen),
    basculaScreen(new BasculaScreen),
    printerScreen(new PrinterScreen)
{
    createActions();
    createTrayIcon();

    QWidget *centralWidget = new QWidget();
    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);
    mainLayout->addWidget(m_leftSideBar);
    mainLayout->addLayout(m_stackedLayout);

    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);

    m_stackedLayout->addWidget(serverScreen);
    m_stackedLayout->addWidget(basculaScreen);
    m_stackedLayout->addWidget(printerScreen);
    m_stackedLayout->setCurrentIndex(1);
    connect(m_leftSideBar, &LeftSideBar::buttonClicked, this, &Window::handleLeftSideBarChanged);

    trayIcon->setIcon(QIcon(":/assets/server.svg"));
    setWindowIcon(QIcon(":/assets/server.svg"));
    trayIcon->setToolTip("Hola");
    trayIcon->show();
    /*

    bool debug = true;
    int port = 3500;
    server = new class EchoServer(port, debug);


    connect(server, &EchoServer::onClientConnected, this, &MainWindow::onClient);
    connect(start, &QPushButton::clicked, this, &MainWindow::transaction);
    connect(stop, &QPushButton::clicked, this, &MainWindow::clientDesconect);
    connect(&m_thread, &MasterThread::response, this, &MainWindow::showResponse);
    connect(&m_thread, &MasterThread::error, this, &MainWindow::processError);
    connect(&m_thread, &MasterThread::timeout, this, &MainWindow::processTimeout);*/
}

void Window::handleLeftSideBarChanged(int index)
{
    m_stackedLayout->setCurrentIndex(index);
}
void Window::onClient(const bool &s){
    if(s){
        clientConnect();
    } else {
        clientDesconect();
    }
}

void Window::clientConnect(){
    setControlsEnabled(false);
    /*m_statusLabel->setText(tr("Status: Running",
                              "\nconnected to port %1.")
                           .arg(m_serialPortComboBox->currentText()));
    m_thread.transaction(m_serialPortComboBox->currentText(),
                         m_waitResponseSpinBox->value(),
                         m_requestLineEdit->text());*/
}

void Window::clientDesconect(){
    /*qDebug() << "cliente desconectado";
    m_statusLabel->setText(tr("Status: Stop",
                              "\nconnected to port %1.")
                           .arg(m_serialPortComboBox->currentText()));
    m_thread.stopReading();
    start->setEnabled(false);*/
}

void Window::transaction()
{
    /*setControlsEnabled(false);
    start->setEnabled(false);
    m_statusLabel->setText(tr("Status: Running",
                              "\nconnected to port %1.")
                           .arg(m_serialPortComboBox->currentText()));
    m_thread.transaction(m_serialPortComboBox->currentText(),
                         m_waitResponseSpinBox->value(),
                         m_requestLineEdit->text());*/
}

void Window::showResponse(const QString &s)
{
    /*server->processTextMessage(s);
    setControlsEnabled(true);
    QJsonDocument temp = QJsonDocument::fromJson(s.toUtf8());

    QJsonObject jsonObj = temp.object();
    m_trafficLabel->setText(tr("Transaction: %1"
                               "\nQuantity: %2"
                               "\nType: %3")
                            .arg(++m_transactionCount)
                            .arg(jsonObj["quantity"].toString())
            .arg(jsonObj["type"].toString()));*/
}

void Window::processError(const QString &s)
{
    /*setControlsEnabled(true);
    m_statusLabel->setText(tr("Status: Not running, %1.").arg(s));
    m_trafficLabel->setText(tr("No traffic."));*/
}

void Window::processTimeout(const QString &s)
{
   /* setControlsEnabled(true);
    m_statusLabel->setText(tr("Status: Running, %1.").arg(s));
    m_trafficLabel->setText(tr("No traffic."));*/
}

void Window::setControlsEnabled(bool enable)
{
    /*start->setEnabled(enable);
    m_serialPortComboBox->setEnabled(enable);
    m_waitResponseSpinBox->setEnabled(enable);
    m_requestLineEdit->setEnabled(enable);*/
}

void Window::closeEvent(QCloseEvent *event)
{

    if (trayIcon->isVisible()) {
        QMessageBox::information(this, tr("Systray"),
                                 tr("The program will keep running in the "
                                    "system tray. To terminate the program, "
                                    "choose <b>Quit</b> in the context menu "
                                    "of the system tray entry."));
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

    maximizeAction = new QAction(tr("Ma&ximize"), this);
    connect(maximizeAction, &QAction::triggered, this, &QWidget::showMaximized);

    restoreAction = new QAction(tr("&Restore"), this);
    connect(restoreAction, &QAction::triggered, this, &QWidget::showNormal);

    quitAction = new QAction(tr("&Quit"), this);
    connect(quitAction, &QAction::triggered, qApp, &QCoreApplication::quit);
}

void Window::createTrayIcon()
{
    trayIconMenu = new QMenu(this);
    trayIconMenu->addAction(minimizeAction);
    trayIconMenu->addAction(maximizeAction);
    trayIconMenu->addAction(restoreAction);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(quitAction);

    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setContextMenu(trayIconMenu);
}
