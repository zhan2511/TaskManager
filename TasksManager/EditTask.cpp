#include "EditTask.h"
#include "ui_EditTask.h"
#include <QDebug>

NewTask::NewTask(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::NewTask)
{
    ui->setupUi(this);

    this->setModal(1);

    this->name = "name";
    this->description = "description";
    this->priority = 1;
    this->y = 2000;
    this->m = 1;
    this->d = 1;

    this->ui->Name->setText(name);
    this->ui->Descri->setText(description);
    this->ui->Prior->setValue(priority);
    this->ui->DL->setDate(QDate(y,m,d));
}

NewTask::NewTask(QString name, QString description, int priority, int y, int m, int d)
{
    ui = new Ui::NewTask;
    ui->setupUi(this);

    this->setModal(1);

    this->name = name;
    this->description = description;
    this->priority = priority;
    this->y = y;
    this->m = m;
    this->d = d;

    this->ui->Name->setText(name);
    this->ui->Descri->setText(description);
    this->ui->Prior->setValue(priority);
    this->ui->DL->setDate(QDate(y,m,d));
}

NewTask::~NewTask()
{
    delete ui;
}

void NewTask::on_OK_clicked()
{
    QString name = this->ui->Name->toPlainText();
    QString description = this->ui->Descri->toPlainText();
    int priority = this->ui->Prior->value();
    QDate Deadline = this->ui->DL->date();
    qDebug()<<Deadline;
    qDebug()<<name<<" "<<description<<" "<<priority<<" "<<Deadline.year()<<" "<<Deadline.month()<<" "<<Deadline.day();
    emit task(name,description,priority,Deadline.year(),Deadline.month(),Deadline.day());
    qDebug()<< " emit task";
    this->close();
}


void NewTask::on_Cancel_clicked()
{
    this->close();
}

