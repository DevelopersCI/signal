#ifndef PRINTERSCREEN_H
#define PRINTERSCREEN_H
#include <QWidget>
QT_BEGIN_NAMESPACE

class QLabel;
class QLineEdit;
class QSpinBox;
class QPushButton;
class QComboBox;

QT_END_NAMESPACE

class PrinterScreen : public QWidget
{
    Q_OBJECT

public:
    explicit PrinterScreen(QWidget *parent = nullptr);

private:
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
};

#endif // PRINTERSCREEN_H
