#ifndef LOGINMGRTHD_H
#define LOGINMGRTHD_H

#include <QThread>
#include <QMutex>

class QTimer;

struct LoginForm
{
    QString ip;
    QString username;
    QString pwd;
    uint32_t num;
    uint16_t port;
    int64_t nodeID;

    LoginForm(const QString& ip, const QString& username, const QString& pwd, const uint32_t& num, const uint16_t& port, const uint64_t& nodeID):
        ip(ip),username(username),pwd(pwd),num(num),port(port),nodeID(nodeID)
    {
    }

    LoginForm(const LoginForm& form) :
        ip(form.ip),username(form.username),pwd(form.pwd),num(form.num),port(form.port),nodeID(form.nodeID)
    {

    }
};

class LoginMgrThd : public QThread
{
    Q_OBJECT
public:
    explicit LoginMgrThd(const LoginForm& m_form, QObject *parent = 0);
    ~LoginMgrThd();
    void run();

    volatile static uint32_t succeed;
    volatile static uint32_t failed;

private:
    const LoginForm m_form;
    QTimer* mp_timer;
    QMutex m_mutex;

signals:
    void startTimer(int msec);
    //void updateProgress(int value);
    void testFinished(uint32_t succeed, uint32_t failed);

public slots:

private slots:
    void timeout();

};

#endif // LOGINMGRTHD_H
