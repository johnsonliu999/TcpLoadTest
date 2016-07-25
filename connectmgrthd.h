#ifndef CONNECTMGRTHD_H
#define CONNECTMGRTHD_H

#include <QThread>
#include <QMutex>

#include "mgrthd.h"

struct ConnectForm
{
    QString ip;
    uint16_t port;

    ConnectForm(const QString& ip, const uint16_t& port) :
        ip(ip),port(port)
    {

    }

    ConnectForm(const ConnectForm& form) :
        ip(form.ip),port(form.port)
    {

    }
};

class ConnectMgrThd : public MgrThd
{
    Q_OBJECT
public:
    ConnectMgrThd(int num, const ConnectForm& form, QObject *parent = 0);

    void run();

    static uint32_t timeout;

private:
    const ConnectForm m_form;
};

#endif // CONNECTMGRTHD_H
