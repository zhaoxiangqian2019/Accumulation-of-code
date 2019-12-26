#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_thread = new MyThread;
    connect(m_thread, &MyThread::sig_SendMsg, 
            [=](int a)
    {
        ui->lineEdit->clear();
        ui->lineEdit->setText(QString::number(a));
    });
    
    thread = new QThread;
    connect(thread, &QThread::started, m_thread, &MyThread::DoWork);
    m_thread->moveToThread(thread);
    thread->start();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    m_thread->SetFlag(true);
}

void MainWindow::on_pushButton_2_clicked()
{
    m_thread->SetFlag(false);
}
