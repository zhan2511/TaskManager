#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "EditTask.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    connect(this->ui->tableWidget->horizontalHeader(),&QHeaderView::sectionClicked,this,&MainWindow::OnSectionClicked);
    this->TaskList = new LinkedList;
    this->row = -1;
    this->column = -1;
}

MainWindow::~MainWindow()
{
    TaskList->ClearList();
    delete ui;
}


void MainWindow::on_Add_clicked()
{
    NewTask* newtask = new NewTask();
    newtask->setAttribute(Qt::WA_DeleteOnClose);
    connect(newtask,&NewTask::task,this,&MainWindow::AddTask);
    newtask->show();
}


void MainWindow::on_Edit_clicked()
{
    if(this->row == -1){
        return;
    }
    QDate DL = QDate::fromString(this->ui->tableWidget->item(row,3)->text(),"yyyy-MM-dd");
    qDebug()<<DL;
    NewTask* newtask = new NewTask(this->ui->tableWidget->item(row,0)->text(),this->ui->tableWidget->item(row,1)->text(),
                                   this->ui->tableWidget->item(row,2)->text().toInt(),DL.year(),DL.month(),DL.day());
    qDebug()<<"On_Edit_clicked";
    newtask->setAttribute(Qt::WA_DeleteOnClose);
    connect(newtask,&NewTask::task,this,&MainWindow::EditTask);
    newtask->show();
}

void MainWindow::AddTask(QString name, QString description, int priority, int y, int m, int d)
{
    qDebug()<<"to add task";
    Task task(name.toStdString(),description.toStdString(),priority,y,m,d);
    qDebug()<<"new task"<<name<<" "<<description<<" "<<priority<<" "<<y<<" "<<m<<" "<<d;
    this->TaskList->InsertAtTail(task);
    qDebug()<<"add to list"<<"ListLength"<<this->TaskList->GetLength();
    int r = this->ui->tableWidget->rowCount();
    qDebug()<< r ;
    this->ui->tableWidget->insertRow(r);
    QTableWidgetItem *Item0 = new QTableWidgetItem(name);
    this->ui->tableWidget->setItem(r, 0, Item0);
    // qDebug()<<"add name";
    QTableWidgetItem *Item1 = new QTableWidgetItem(description);
    this->ui->tableWidget->setItem(r, 1, Item1);
    // qDebug()<<"add description";
    QTableWidgetItem *Item2 = new QTableWidgetItem(QString::number(priority));
    this->ui->tableWidget->setItem(r, 2, Item2);
    // qDebug()<<"add priority";
    QTableWidgetItem *Item3 = new QTableWidgetItem(QDate(y,m,d).toString("yyyy-MM-dd"));
    this->ui->tableWidget->setItem(r, 3, Item3);
    // qDebug()<<"add Dl";

}

void MainWindow::EditTask(QString name, QString description, int priority, int y, int m, int d)
{
    // this->TaskList->DeleteElem(row+1);
    // qDebug()<<"ListLength"<<this->TaskList->GetLength();
    // Task task(name.toStdString(),description.toStdString(),priority,y,m,d);
    // qDebug()<<"new task"<<name<<" "<<description<<" "<<priority<<" "<<y<<" "<<m<<" "<<d;
    // qDebug()<<"ListLength"<<this->TaskList->GetLength();
    // this->TaskList->InsertElem(task,row+1);
    // qDebug()<<"ListLength"<<this->TaskList->GetLength();

    this->TaskList->TakeNode(row+1)->data.name = name.toStdString();
    this->TaskList->TakeNode(row+1)->data.description = description.toStdString();
    this->TaskList->TakeNode(row+1)->data.priority = priority;
    this->TaskList->TakeNode(row+1)->data.time->setDate(y,m,d);

    this->ui->tableWidget->item(row,0)->setText(name);
    this->ui->tableWidget->item(row,1)->setText(description);
    this->ui->tableWidget->item(row,2)->setText(QString::number(priority));
    this->ui->tableWidget->item(row,3)->setText(QDate(y,m,d).toString("yyyy-MM-dd"));
    row = column = -1;
}


void MainWindow::on_tableWidget_cellPressed(int row, int column)
{
    this->row = row;
    this->column = column;
    qDebug()<<"select"<<row<<" "<<column;
}


void MainWindow::on_Delete_clicked()
{
    if(this->row == -1){
        return;
    }
    Task t = this->TaskList->DeleteElem(row+1);
    qDebug()<<t.name;
    qDebug()<<"ListLength"<<this->TaskList->GetLength();
    this->ui->tableWidget->removeRow(row);
    row = column = -1;
}


void MainWindow::on_Import_clicked()
{
    QString CSVfilename = QFileDialog::getOpenFileName(this, "选择 CSV 文件", "", "CSV Files (*.csv);;All Files (*)");
    ImportTasks(CSVfilename);
}

void MainWindow::ImportTasks(QString CSVfilename)
{
    if (CSVfilename.isEmpty()){
        return;
    }
    QFile file(CSVfilename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        return;
    }
    QTextStream in(&file);
    QStringList rowValues;
    for (int i = 0; i<100 && !in.atEnd(); ++i) {
        QString line = in.readLine();
        rowValues = line.split(",");
        if(i == 0){
            continue;
        }
        int r = this->ui->tableWidget->rowCount();
        QDate DL = QDate::fromString(rowValues[3],"yyyy/M/d");
        qDebug()<<DL;
        this->TaskList->InsertAtTail(Task(rowValues[0].toStdString(),rowValues[1].toStdString(),
                                          rowValues[2].toInt(),DL.year(),DL.month(),DL.day()));
        this->ui->tableWidget->insertRow(r);
        QTableWidgetItem *Item0 = new QTableWidgetItem(rowValues[0]);
        this->ui->tableWidget->setItem(r, 0, Item0);
        // qDebug()<<"add name";
        QTableWidgetItem *Item1 = new QTableWidgetItem(rowValues[1]);
        this->ui->tableWidget->setItem(r, 1, Item1);
        // qDebug()<<"add description";
        QTableWidgetItem *Item2 = new QTableWidgetItem(rowValues[2]);
        this->ui->tableWidget->setItem(r, 2, Item2);
        // qDebug()<<"add priority";
        QTableWidgetItem *Item3 = new QTableWidgetItem(DL.toString("yyyy-MM-dd"));
        this->ui->tableWidget->setItem(r, 3, Item3);
        r++;
    }
    file.close();
}

void MainWindow::ReloadTasks()
{
    this->ui->tableWidget->clearContents();
    this->ui->tableWidget->setRowCount(this->TaskList->GetLength());
    qDebug()<<"ReloadTasks";
    Node* t = this->TaskList->GetHead();
    for(int r = 0; r < this->TaskList->GetLength(); ++r){
        this->ui->tableWidget->setItem(r,0,new QTableWidgetItem(QString::fromStdString(t->data.name)));
        this->ui->tableWidget->setItem(r,1,new QTableWidgetItem(QString::fromStdString(t->data.description)));
        this->ui->tableWidget->setItem(r,2,new QTableWidgetItem(QString::number(t->data.priority)));
        this->ui->tableWidget->setItem(r,3,new QTableWidgetItem(QDate(t->data.time->year(),t->data.time->month(),t->data.time->day()).toString("yyyy-MM-dd")));
        t = t->next;
    }
}

void MainWindow::OnSectionClicked(int column)
{
    qDebug()<<"Seclect Column "<<column;
    if(column == 2){
        this->TaskList->OrderByPrior();
        ReloadTasks();
    }else if(column == 3){
        this->TaskList->OrderByDL();
        ReloadTasks();
    }
}


void MainWindow::on_Check_clicked()
{
    this->ui->tableWidget->clearContents();
}

