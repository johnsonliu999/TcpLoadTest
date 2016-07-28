#ifndef IPEDIT_H
#define IPEDIT_H

#include <QLineEdit>

class SegIPEdit : public QLineEdit
{
    Q_OBJECT
public:
    SegIPEdit(QWidget* parent = 0);
    ~SegIPEdit();
};

class IPEdit : public QLineEdit
{
    Q_OBJECT
public:
    IPEdit(QWidget *parent = 0);
    ~IPEdit();
    QString text() const;

private:
    void paintEvent(QPaintEvent* e);

    SegIPEdit* mp_segIPEdit[4];
};

#endif // IPEDIT_H
