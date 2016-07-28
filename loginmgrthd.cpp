#include "loginmgrthd.h"
#include "logintask.h"

#include <QThreadPool>
#include <QTimer>
#include <QDebug>

LoginMgrThd::LoginMgrThd(const int num, const LoginForm &form, QObject *parent) :
    MgrThd(num, parent),
    m_form(form)
{
}

LoginMgrThd::~LoginMgrThd()
{
}

void LoginMgrThd::run()
{
    QThreadPool::globalInstance()->setMaxThreadCount(1000);
    LoginTask* task;
    for (uint32_t i = 0; i < num; i++)
    {
        task = new LoginTask(m_form);
        QThreadPool::globalInstance()->start(task);
    }
    emit startTimer(3000);
    exec();
}

