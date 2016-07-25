#include "connecttask.h"
#include "connectmgrthd.h"

#include <QTcpSocket>

ConnectTask::ConnectTask(const ConnectForm &form):
    mp_form(new ConnectForm(form))
{

}

ConnectTask::~ConnectTask()
{
    delete mp_socket;
    delete mp_form;
}

void ConnectTask::run()
{
    mp_socket = new QTcpSocket;
    mp_socket->connectToHost(mp_form->ip, mp_form->port);
    if (mp_socket->waitForConnected(-1))
    {
        qDebug() << QThread::currentThreadId() << ": Connect Succeed";
        m_mutex.lock();
        ConnectMgrThd::succeed++;
        m_mutex.unlock();
    }
    else if (mp_socket->error() == QAbstractSocket::ConnectionRefusedError)
    {
        qDebug() << QThread::currentThreadId() << ": Connect Refused";
        m_mutex.lock();
        ConnectMgrThd::failed++;
        m_mutex.unlock();
    }
    else
    {
        qDebug() << QThread::currentThreadId() << mp_socket->error();
        // network error show connection time out
        if (mp_socket->error() == QAbstractSocket::NetworkError)
        {
            m_mutex.lock();
            ConnectMgrThd::timeout++;
            ConnectMgrThd::failed++;
            m_mutex.unlock();
        }
        else
        {
            m_mutex.lock();
            ConnectMgrThd::failed++;
            m_mutex.unlock();
        }
    }
}
