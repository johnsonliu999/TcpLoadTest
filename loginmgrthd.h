#ifndef LOGINMGRTHD_H
#define LOGINMGRTHD_H

#include "mgrthd.h"

#include <QThread>
#include <QMutex>

struct LoginForm
{
    QString ip;
    QString username;
    QString pwd;
    uint16_t port;
    int64_t nodeID;

    LoginForm(const QString& ip, const QString& username, const QString& pwd, const uint16_t& port, const uint64_t& nodeID):
        ip(ip),username(username),pwd(pwd),port(port),nodeID(nodeID)
    {
    }

    LoginForm(const LoginForm& form) :
        ip(form.ip),username(form.username),pwd(form.pwd),port(form.port),nodeID(form.nodeID)
    {

    }
};

class LoginMgrThd : public MgrThd
{
    Q_OBJECT
public:
    explicit LoginMgrThd(const int num, const LoginForm& form, QObject *parent = 0);
    ~LoginMgrThd();
    void run();

private:
    const LoginForm m_form;
};

#endif // LOGINMGRTHD_H
