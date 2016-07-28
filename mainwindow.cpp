#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "logintask.h"
#include "loginmgrthd.h"

#include "connectmgrthd.h"

#include <QThreadPool>
#include <QDebug>
#include <QMessageBox>



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->progressBar->hide();

    QRegExp rx;
    rx.setPattern(R"(\d{18})");
    ui->nodeIDEdit->setValidator(new QRegExpValidator(rx, this));
    rx.setPattern(R"(\d{5})");
    ui->portEdit->setValidator(new QRegExpValidator(rx, this));
    rx.setPattern(R"(\d+)");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_testFinished(uint32_t succeed, uint32_t failed)
{
    ui->succeedEdit->setText(QString::number(succeed));
    ui->failedEdit->setText(QString::number(failed));
    ui->timeEdit->setText(QString::number(m_time.elapsed()) + " msec");
    ui->progressBar->hide();

    mp_mgr->quit();
    mp_mgr->wait();
    delete mp_mgr;

    QMessageBox::information(this, "Test Finished", "Test Finished!", QMessageBox::Ok);

    ui->progressBar->hide();
    ui->nameEdit->setEnabled(true);
    ui->pwdEdit->setEnabled(true);
    ui->ipEdit->setEnabled(true);
    ui->portEdit->setEnabled(true);
    ui->numEdit->setEnabled(true);
    ui->nodeIDEdit->setEnabled(true);
    ui->startBtn->setEnabled(true);
    ui->taskBox->setEnabled(true);

}

void MainWindow::on_startBtn_clicked()
{
    QString username = ui->nameEdit->text();
    QString pwd = ui->pwdEdit->text();
    QString ip = ui->ipEdit->text();
    uint16_t port = ui->portEdit->text().toShort();
    uint32_t num = ui->numEdit->text().toUInt();
    uint64_t nodeID = ui->nodeIDEdit->text().toULongLong();



    switch (ui->taskBox->currentIndex())
    {
    case 0:
        mp_mgr = new ConnectMgrThd(num, ConnectForm(ip, port));
        break;
    case 1:
        mp_mgr = new LoginMgrThd(num, LoginForm(ip, username, pwd, port, nodeID));
        break;
    }

    connect(mp_mgr, &MgrThd::updateProgress, ui->progressBar, &QProgressBar::setValue);
    connect(mp_mgr, &MgrThd::testFinished, this, &MainWindow::on_testFinished);

    mp_mgr->start();
    m_time.start();

    ui->progressBar->setValue(0);
    ui->progressBar->show();
    ui->taskBox->setEnabled(false);
    ui->nameEdit->setEnabled(false);
    ui->pwdEdit->setEnabled(false);
    ui->ipEdit->setEnabled(false);
    ui->portEdit->setEnabled(false);
    ui->numEdit->setEnabled(false);
    ui->nodeIDEdit->setEnabled(false);
    ui->succeedEdit->clear();
    ui->failedEdit->clear();
    ui->timeEdit->clear();

    ui->startBtn->setEnabled(false);
}


