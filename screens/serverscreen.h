#ifndef SERVERSCREEN_H
#define SERVERSCREEN_H
#include <QWidget>
#include <QSpinBox>
#include <QLabel>


class ServerScreen: public QWidget
{
    Q_OBJECT

public:
    explicit ServerScreen(QWidget *parent = nullptr);

private:
    QSpinBox *port;
    QLabel *l_port;
};

#endif // SERVERSCREEN_H
