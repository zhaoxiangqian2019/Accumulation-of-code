#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QObject>
#include <QThread>

class MyThread : public QObject
{
    Q_OBJECT
public:
    explicit MyThread(QObject *parent = nullptr);    
signals:
    void sig_SendMsg(int);
public slots:
    void DoWork();
    void SetFlag(bool);
private:
    bool m_flag;
    bool m_flagTrue;
    int a;
};

#endif // MYTHREAD_H
