#ifndef BASCULASCREEN_H
#define BASCULASCREEN_H

#include "utils/bascula.h"
#include <QWidget>
QT_BEGIN_NAMESPACE

class QLabel;
class QLineEdit;
class QSpinBox;
class QPushButton;
class QComboBox;

QT_END_NAMESPACE
class BasculaScreen: public QWidget
{
    Q_OBJECT

public:
    explicit BasculaScreen(QWidget *parent = nullptr);

public slots:
    void showResponse(const QString &s);
    void processError(const QString &s);
    void processTimeout(const QString &s);
    void transaction();
    void clientDesconect();
private:
    void setControlsEnabled(bool enable);

Q_SIGNALS:
    void getInfobyBascula(QString message);
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
    Bascula bascula;
};

#endif // BASCULASCREEN_H
