#ifndef EDITTASK_H
#define EDITTASK_H

#include <QDialog>

namespace Ui {
class NewTask;
}

class NewTask : public QDialog
{
    Q_OBJECT

public:
    explicit NewTask(QWidget *parent = nullptr);
    NewTask(QString name, QString description, int priority, int y, int m, int d);
    ~NewTask();

    QString name;
    QString description;
    int priority;
    int y;
    int m;
    int d;

private slots:
    void on_OK_clicked();

    void on_Cancel_clicked();

signals:
    // void task(QString,QString,int,time_t);
    void task(QString name,QString description,int priority,int y,int m,int d);

private:
    Ui::NewTask *ui;
};

#endif // EDITTASK_H
