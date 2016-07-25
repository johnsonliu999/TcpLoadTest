#include "connectmgrthd.h"
#include "connecttask.h"

#include <QThreadPool>

uint32_t ConnectMgrThd::timeout;

ConnectMgrThd::ConnectMgrThd(int num, const ConnectForm &form, QObject *parent) :
    MgrThd(num, parent),
    m_form(form)
{
    ConnectMgrThd::timeout = 0;
}

void ConnectMgrThd::run()
{
    QThreadPool::globalInstance()->setMaxThreadCount(1000);
    ConnectTask* task;
    for (uint32_t i = 0; i < num; i++)
    {
        task = new ConnectTask(m_form);
        QThreadPool::globalInstance()->start(task);
    }
    qDebug() << "Num :" << num;
    emit startTimer(3000);
    QThreadPool::globalInstance()->waitForDone(-1);
    qDebug() << "Timeout :" << timeout;
//    exec();
}
