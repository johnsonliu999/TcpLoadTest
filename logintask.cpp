#include "logintask.h"
#include "TGClientSDK.h"

#include <QThread>
#include <QDebug>
#include <QThreadPool>

#include "loginmgrthd.h"

LoginTask::LoginTask(const LoginForm& form) :
    mp_form(new LoginForm(form))
{

}

void LoginTask::run()
{
    qDebug() << "Active :" << QThreadPool::globalInstance()->activeThreadCount();

    if (!TGClient_Init())
    {
        qDebug() << QThread::currentThreadId() << ": Init failed";
        QThread::currentThread()->quit();
    }

    mutex.lock();
    long handle = TGClient_AsyncLogin((char*)mp_form->ip.toStdString().data(),
                                      mp_form->port,
                                      mp_form->username.toStdString().data(),
                                      mp_form->pwd.toStdString().data(),
                                      mp_form->nodeID,
                                      nullptr, nullptr);
    mutex.unlock();
    if (!handle)
    {
        mutex.lock();
        LoginMgrThd::failed++;
        mutex.unlock();
        qDebug() << QThread::currentThreadId() << ": Login failed";
        QThread::currentThread()->quit();
    }
    else
    {
        mutex.lock();
        LoginMgrThd::succeed++;
        mutex.unlock();
        qDebug() << QThread::currentThreadId() << ": Login succeed";
    }
}
