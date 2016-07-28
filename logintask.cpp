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

LoginTask::~LoginTask()
{
    delete mp_form;
}

void LoginTask::run()
{
    if (!TGClient_Init())
    {
        qDebug() << QThread::currentThreadId() << ": Init failed";
        m_mutex.lock();
        LoginMgrThd::failed++;
        m_mutex.unlock();
        QThread::currentThread()->quit();
    }

    m_mutex.lock();
    long handle = TGClient_AsyncLogin((char*)mp_form->ip.toStdString().data(),
                                      mp_form->port,
                                      mp_form->username.toStdString().data(),
                                      mp_form->pwd.toStdString().data(),
                                      mp_form->nodeID,
                                      nullptr, nullptr);
    m_mutex.unlock();
    if (!handle)
    {
        m_mutex.lock();
        LoginMgrThd::failed++;
        m_mutex.unlock();
        qDebug() << QThread::currentThreadId() << ": Login failed";
    }
    else
    {
        m_mutex.lock();
        LoginMgrThd::succeed++;
        m_mutex.unlock();
        qDebug() << QThread::currentThreadId() << ": Login succeed";
    }
}
