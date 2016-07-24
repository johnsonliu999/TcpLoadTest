#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "logintask.h"
#include "loginmgrthd.h"

#include <QThreadPool>
#include <QDebug>



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
    mp_mgr->quit();
    mp_mgr->wait();
    delete mp_mgr;

    ui->nameEdit->setEnabled(true);
    ui->pwdEdit->setEnabled(true);
    ui->IPEdit->setEnabled(true);
    ui->portEdit->setEnabled(true);
    ui->numEdit->setEnabled(true);
    ui->nodeIDEdit->setEnabled(true);
    ui->startBtn->setEnabled(true);
    ui->progressBar->hide();
}

void MainWindow::on_startBtn_clicked()
{
    QString username = ui->nameEdit->text();
    QString pwd = ui->pwdEdit->text();
    QString ip = ui->IPEdit->text();
    uint16_t port = ui->portEdit->text().toShort();
    uint32_t num = ui->numEdit->text().toUInt();
    uint64_t nodeID = ui->nodeIDEdit->text().toULongLong();

    mp_mgr = new LoginMgrThd(LoginForm(ip, username, pwd, num, port, nodeID));
    //connect(mp_mgr, &LoginMgrThd::updateProgress, ui->progressBar, &QProgressBar::setValue);
    connect(mp_mgr, &LoginMgrThd::testFinished, this, &MainWindow::on_testFinished);

    mp_mgr->start();

    ui->progressBar->show();
    ui->nameEdit->setEnabled(false);
    ui->pwdEdit->setEnabled(false);
    ui->IPEdit->setEnabled(false);
    ui->portEdit->setEnabled(false);
    ui->numEdit->setEnabled(false);
    ui->nodeIDEdit->setEnabled(false);
    ui->succeedEdit->clear();
    ui->failedEdit->clear();

    ui->startBtn->setEnabled(false);
}


