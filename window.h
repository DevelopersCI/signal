#ifndef WINDOW_H
#define WINDOW_H

#include <QSystemTrayIcon>
#include <QDialog>

#include "bascula.h"
#include <QDialog>
#include <QMainWindow>
#include "server.h"
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

    void transaction();
    void showResponse(const QString &s);
    void processError(const QString &s);
    void processTimeout(const QString &s);
    void onClient(const bool &s);
    void clientConnect();
    void clientDesconect();

private:
    void setControlsEnabled(bool enable);
    void handleLeftSideBarChanged(int index);
    void createActions();
    void createTrayIcon();

private:
    LeftSideBar *m_leftSideBar;
    QStackedLayout *m_stackedLayout;
    ServerScreen *serverScreen;
    BasculaScreen *basculaScreen;
    PrinterScreen *printerScreen;

    Bascula m_thread;
    EchoServer *server;

    QAction *minimizeAction;
    QAction *maximizeAction;
    QAction *restoreAction;
    QAction *quitAction;

    QSystemTrayIcon *trayIcon;
    QMenu *trayIconMenu;

};

#endif // QT_NO_SYSTEMTRAYICON

