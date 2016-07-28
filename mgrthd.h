#ifndef MGRTHD_H
#define MGRTHD_H

#include <QThread>
#include <QMutex>
#include <QObject>

class QTimer;

struct Form
{
    uint32_t num;
};

class MgrThd : public QThread
{
    Q_OBJECT
public:
    explicit MgrThd(const int num, QObject* parent = 0);
    ~MgrThd();
    virtual void run() = 0;

    volatile static uint32_t succeed;
    volatile static uint32_t failed;
    uint32_t num;

private:
    QTimer* mp_timer;
    QMutex m_mutex;

signals:
    void startTimer(int msec);
    void testFinished(uint32_t succeed, uint32_t failed);
    void updateProgress(int value);

private slots:
    void on_timeout();
};

#endif // MGRTHD_H
