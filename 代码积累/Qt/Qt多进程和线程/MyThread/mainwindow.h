#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "mythread.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    
private slots:
    void on_pushButton_clicked();
    
    void on_pushButton_2_clicked();
    
private:
    Ui::MainWindow *ui;
    MyThread *m_thread;
    QThread *thread;
};

#endif // MAINWINDOW_H
