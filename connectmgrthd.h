#ifndef CONNECTMGRTHD_H
#define CONNECTMGRTHD_H

#include <QThread>
#include <QMutex>

class QTimer;

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

class ConnectMgrThd : public QThread
{
    Q_OBJECT
public:
    ConnectMgrThd(const ConnectForm& form);

    void run();

private:
    const ConnectForm m_form;
};

#endif // CONNECTMGRTHD_H
