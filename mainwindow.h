#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QtSql>
#include<QtDebug>
#include<QFileInfo>
#include"hastabilgi.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    QSqlDatabase mydb;

    void connClose()
{
        mydb.close();
        mydb.removeDatabase(QSqlDatabase::defaultConnection);
}
    bool connOpen()
{
        mydb = QSqlDatabase::addDatabase("QSQLITE");
        mydb.setDatabaseName("C:/Users/PC/Desktop/MASAÜSTÜ/db/mydb.db");

        if(!mydb.open())
        {
            qDebug()<<("VERİ TABANINA BAĞLANILAMADI");
            return false;
        }
        else
            qDebug()<<("VERİ TABANINA BAĞLANILDI");
            return true;
}

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();


private:
    Ui::MainWindow *ui;

};
#endif // MAINWINDOW_H
