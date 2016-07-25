#ifndef CONNECTTASK_H
#define CONNECTTASK_H

#include <QRunnable>
#include <QMutex>
#include <QObject>
#include <QAbstractSocket>

struct ConnectForm;
class QTcpSocket;

class ConnectTask : public QRunnable
{
public:
    ConnectTask(const ConnectForm& form);
    ~ConnectTask();
    void run();

private:
    QMutex m_mutex;
    ConnectForm* mp_form;
    QTcpSocket* mp_socket;
};

#endif // CONNECTTASK_H
