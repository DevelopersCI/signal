#include "leftsidebar.h"
#include "pushbutton.h"
#include <QPushButton>
#include <QPainter>
#include <QMap>

LeftSideBar::LeftSideBar(QWidget *parent)
    : QWidget(parent), m_layout(new QVBoxLayout),
      m_buttonGroup(new QButtonGroup)
{
    m_buttonNameList << tr("Impresora") << tr("Bascula");
    m_layout->setSpacing(5);

    setLayout(m_layout);
    setFixedWidth(160);
    initButtons();

    connect(m_buttonGroup, static_cast<void (QButtonGroup::*)(int)>(&QButtonGroup::buttonClicked), this, &LeftSideBar::buttonClicked);
}

void LeftSideBar::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);

    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor("#FFFFFF"));
    painter.drawRect(rect());
}

void LeftSideBar::initButtons()
{
    const QMap<int, QString> icons = {
        {0, ":/assets/printer.svg"},
        {1, ":/assets/bascula.png"},

    };

    for (int i = 0; i < m_buttonNameList.size(); ++i) {
        PushButton *btn = new PushButton;
        btn->setText(m_buttonNameList.at(i));
        btn->setObjectName("SideButton");
        btn->setCheckable(true);
        btn->setFixedHeight(45);
        // btn->setIcon(QIcon(icons.value(i)));
        // btn->setIconSize(QSize(30, 30));

        btn->setIcon(icons.value(i), QSize(30, 30));

        m_buttonGroup->addButton(btn, i);
        m_layout->addWidget(btn);

    }

    setChecked(1);
    m_layout->addStretch();
}

void LeftSideBar::setChecked(int index)
{
    m_buttonGroup->button(index)->setChecked(true);
}
