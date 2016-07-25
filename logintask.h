#ifndef LOGINTASK_H
#define LOGINTASK_H

#include <QRunnable>
#include <QMutex>

struct LoginForm;

class LoginTask : public QRunnable
{
public:
    LoginTask(const LoginForm& form);
    ~LoginTask();
    void run();

private:
    QMutex m_mutex;
    LoginForm* mp_form;
};

#endif // LOGINTASK_H
