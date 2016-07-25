#include "mgrthd.h"

#include <QTimer>
#include <QDebug>
#include <QThreadPool>

volatile uint32_t MgrThd::succeed;
volatile uint32_t MgrThd::failed;

MgrThd::MgrThd(const int num, QObject *parent) :
    QThread(parent),
    mp_timer(new QTimer(this)),
    num(num)
{
    succeed = failed = 0;
    connect(this, SIGNAL(startTimer(int)), mp_timer, SLOT(start(int)));
    connect(mp_timer, &QTimer::timeout, this, &MgrThd::timeout);
}

MgrThd::~MgrThd()
{
}

void MgrThd::timeout()
{
    qDebug() << "Enter time out";
    qDebug() << "Active :" << QThreadPool::globalInstance()->activeThreadCount();
    qDebug() << "Max :" << QThreadPool::globalInstance()->maxThreadCount();
    m_mutex.lock();
    uint32_t total = succeed+failed;
    m_mutex.unlock();
    qDebug() << "Succeed :" << succeed;
    qDebug() << "Failed :" << failed;
    if (total == num)
    {
        mp_timer->stop();
        emit testFinished(succeed, failed);
    }
}
