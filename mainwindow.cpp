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
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_testFinished(uint32_t succeed, uint32_t failed)
{
    ui->succeedEdit->setText(QString::number(succeed));
    ui->failedEdit->setText(QString::number(failed));
    ui->progressBar->hide();

    mp_mgr->quit();
    mp_mgr->wait();
    delete mp_mgr;

    QMessageBox::information(this, "Test Finished", "Test Finished!", QMessageBox::Ok);

    ui->nameEdit->setEnabled(true);
    ui->pwdEdit->setEnabled(true);
    ui->ipEdit->setEnabled(true);
    ui->portEdit->setEnabled(true);
    ui->numEdit->setEnabled(true);
    ui->nodeIDEdit->setEnabled(true);
    ui->startBtn->setEnabled(true);

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
        connect(mp_mgr, &MgrThd::testFinished, this, &MainWindow::on_testFinished);
        break;
    case 1:
        mp_mgr = new LoginMgrThd(num, LoginForm(ip, username, pwd, port, nodeID));
        connect(mp_mgr, &MgrThd::testFinished, this, &MainWindow::on_testFinished);
    }

    mp_mgr->start();

    ui->progressBar->show();
    ui->nameEdit->setEnabled(false);
    ui->pwdEdit->setEnabled(false);
    ui->ipEdit->setEnabled(false);
    ui->portEdit->setEnabled(false);
    ui->numEdit->setEnabled(false);
    ui->nodeIDEdit->setEnabled(false);
    ui->succeedEdit->clear();
    ui->failedEdit->clear();

    ui->startBtn->setEnabled(false);
}


