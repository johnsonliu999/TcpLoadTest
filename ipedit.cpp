#include "ipedit.h"

#include <QWidget>
#include <QRegExp>
#include <QValidator>
#include <QPainter>
#include <QDebug>

SegIPEdit::SegIPEdit(QWidget *parent) :
    QLineEdit(parent)
{
    setAlignment(Qt::AlignCenter);
    setMaxLength(3);

    QRegExp rx("(2[0-5]{2}|2[0-4][0-9]|1?[0-9]{1,2})");

    setValidator(new QRegExpValidator(rx, this));
}

SegIPEdit::~SegIPEdit()
{

}

IPEdit::IPEdit(QWidget* parent) :
    QLineEdit(parent)
{
    for (int i = 0; i < 4; i++)
    {
        mp_segIPEdit[i] = new SegIPEdit(this);
        mp_segIPEdit[i]->setFrame(false);
    }
    mp_segIPEdit[0]->setText("121");
    mp_segIPEdit[1]->setText("201");
    mp_segIPEdit[2]->setText("5");
    mp_segIPEdit[3]->setText("141");
}

IPEdit::~IPEdit()
{

}

void IPEdit::paintEvent(QPaintEvent *e)
{
    QLineEdit::paintEvent(e);

    int segWidth = (width()-5)/4;
    int segHeight = height()-2;

    for (int i = 0; i < 4; i++)
        mp_segIPEdit[i]->setGeometry(1+(segWidth+1)*i, 1, segWidth, segHeight);

    QPainter painter(this);
    painter.save();
    painter.setPen(QPen(Qt::black));

    for (int i = 0; i < 3; i++)
        painter.drawPoint((segWidth+1)*(i+1),height()/2);
    painter.restore();
}

QString IPEdit::text() const
{
    QString text;
    for (int i = 0; i < 3; i++)
    {
        text += mp_segIPEdit[i]->text();
        text += ".";
    }
    text += mp_segIPEdit[3]->text();

    return text;
}
