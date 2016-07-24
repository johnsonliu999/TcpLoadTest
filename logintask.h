#ifndef LOGINTASK_H
#define LOGINTASK_H

#include <QRunnable>
#include <QMutex>

struct LoginForm;

class LoginTask : public QRunnable
{
public:
    LoginTask(const LoginForm& form);
    void run();

private:
    QMutex mutex;
    LoginForm* mp_form;
};

#endif // LOGINTASK_H
