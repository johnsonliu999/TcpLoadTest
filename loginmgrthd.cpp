#include "loginmgrthd.h"
#include "logintask.h"

#include <QThreadPool>
#include <QTimer>
#include <QDebug>

volatile uint32_t LoginMgrThd::succeed = 0;
volatile uint32_t LoginMgrThd::failed = 0;

LoginMgrThd::LoginMgrThd(const LoginForm &form, QObject *parent) : QThread(parent),
    m_form(form),
    mp_timer(new QTimer)
{
    succeed = failed = 0;
    connect(this, SIGNAL(startTimer(int)), mp_timer, SLOT(start(int)));
    connect(mp_timer, &QTimer::timeout, this, &LoginMgrThd::timeout);
}

LoginMgrThd::~LoginMgrThd()
{
    delete mp_timer;
}

void LoginMgrThd::run()
{
    QThreadPool::globalInstance()->setMaxThreadCount(m_form.num);
    LoginTask* task = new LoginTask(m_form);
    for (uint32_t i = 0; i < m_form.num; i++)
        QThreadPool::globalInstance()->start(task);
    emit startTimer(3000);
    exec();
}

void LoginMgrThd::timeout()
{
    qDebug() << "Enter time out";\
    m_mutex.lock();
    uint32_t total = succeed+failed;
    m_mutex.unlock();
    //emit updateProgress(total*100/m_form.num);
    qDebug() << "Succeed :" << succeed;
    qDebug() << "Failed :" << failed;
    if (total == m_form.num)
    {
        mp_timer->stop();
        emit testFinished(succeed, failed);
    }
}


