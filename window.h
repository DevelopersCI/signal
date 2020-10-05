#ifndef DIALOG_H
#define DIALOG_H

#include "masterthread.h"
#include <QDialog>
#include <QMainWindow>
#include "echoserver.h"
QT_BEGIN_NAMESPACE

class QLabel;
class QLineEdit;
class QSpinBox;
class QPushButton;
class QComboBox;

QT_END_NAMESPACE

class Dialog : public QMainWindow
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);


private slots:
    void transaction();
    void showResponse(const QString &s);
    void processError(const QString &s);
    void processTimeout(const QString &s);
    void onClient(const bool &s);
    void clientConnect();
    void clientDesconect();

private:
    void setControlsEnabled(bool enable);

private:
    int m_transactionCount = 0;
    QLabel *m_serialPortLabel;
    QComboBox *m_serialPortComboBox;
    QLabel *m_waitResponseLabel;
    QSpinBox *m_waitResponseSpinBox;
    QLabel *m_requestLabel;
    QLineEdit *m_requestLineEdit;
    QLabel *m_trafficLabel;
    QLabel *m_statusLabel;
    QPushButton *start;
    QPushButton *stop;

    MasterThread m_thread;
    EchoServer *server;

};

#endif // DIALOG_H
