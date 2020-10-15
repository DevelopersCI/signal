#ifndef WINDOW_H
#define WINDOW_H

#include <QSystemTrayIcon>
#include <QDialog>

#include <QDialog>
#include <QMainWindow>
#include "utils/server.h"
#include <QStackedLayout>
#include "widgets/leftsidebar.h"

#include "screens/serverscreen.h"
#include "screens/basculascreen.h"
#include "screens/printerscreen.h"


class Window : public QMainWindow
{
    Q_OBJECT

public:
    explicit Window(QWidget *parent = nullptr);
    //void setVisible(bool visible) override;

protected:
    void closeEvent(QCloseEvent *event) override;
private slots:
    void setIcon();
    void iconActivated(QSystemTrayIcon::ActivationReason reason);
    void showMessage();
    void messageClicked();

    void onClient(const bool &s);
    void turnOnOffBascula(const bool &s);
    void startBascula();
    void stopBascula();
    void setMessage(QString msg);
    void binaryMessage(QByteArray message);
    void notification();

private:
    void handleLeftSideBarChanged(int index);
    void createActions();
    void createTrayIcon();

private:
    LeftSideBar *m_leftSideBar;
    QStackedLayout *m_stackedLayout;
    ServerScreen *serverScreen;
    BasculaScreen *basculaScreen;
    PrinterScreen *printerScreen;


    EchoServer *server;

    QAction *minimizeAction;
    QAction *maximizeAction;
    QAction *restoreAction;
    QAction *quitAction;

    QSystemTrayIcon *trayIcon;
    QMenu *trayIconMenu;

};

#endif // QT_NO_SYSTEMTRAYICON

