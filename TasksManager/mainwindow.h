#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTime>
#include <QDateTime>
#include <QDate>
#include <Task.h>
#include <QFileDialog>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    LinkedList* TaskList;

    int row;
    int column;




private slots:

    void on_Add_clicked();

    void on_Edit_clicked();

    void AddTask(QString name,QString description,int priority,int y,int m,int d);

    void EditTask(QString name,QString description,int priority,int y,int m,int d);

    void on_tableWidget_cellPressed(int row, int column);

    void on_Delete_clicked();

    void on_Import_clicked();

    void ImportTasks(QString CSVfilename);

    void ReloadTasks();

    void OnSectionClicked(int columnc);

    void on_Check_clicked();

signals:
    void select(int row, int column);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
