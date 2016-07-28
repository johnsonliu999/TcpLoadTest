#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTime>

class MgrThd;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void on_testFinished(uint32_t succeed, uint32_t failed);

private slots:
    void on_startBtn_clicked();

private:
    Ui::MainWindow *ui;

    QTime m_time;
    MgrThd* mp_mgr;
};

#endif // MAINWINDOW_H
