#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    /*QPixmap bkgnd("C:/Users/PC/Desktop/qt için resimler/arkaplan.jpg");
        bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
        QPalette palette;
        palette.setBrush(QPalette::Background, bkgnd);
        this->setPalette(palette);*/


   if(!connOpen())
       ui->label->setText("VERİ TABANINA BAĞLANILAMADI");
   else
       ui->label->setText("VERİ TABANINA BAĞLANILDI");
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    QString kullanici,sifre;
    kullanici=ui->lineEdit_kullanici->text();
    sifre=ui->lineEdit_sifre->text();

    if(!connOpen()){
        qDebug()<<"VERİ TABANI HATASI";
        return;
    }

    connOpen();
    QSqlQuery qry;
    qry.prepare("select * from personeller where kullanici='"+kullanici+"' and sifre='"+sifre+"'");

    if(qry.exec())
    {

        int count=0;
        while(qry.next())
        {
            count ++;
        }
        if(count==1){
            QMessageBox::information(this,tr("Hoşgeldiniz..."),tr("GİRİŞ BAŞARILI!"));
            //ui->label->setText("Giriş Başarılı");
            connClose();
            this->hide();
            HastaBilgi hastabilgi;
            hastabilgi.setModal(true);
            hastabilgi.exec();
        }
        if(count>1)
            QMessageBox::critical(this,tr("HATA"),tr("Başka bir Kullanıcı adı ve Şifre deneyin!"));
            //ui->label->setText("Başka bir Kullanıcı adı ve Şifre deneyin!");
        if(count<1)
            QMessageBox::critical(this,tr("HATA"),tr("Kullanıcı adı veya Şifre YANLIŞ!"));
           // ui->label->setText("Kullanıcı adı veya Şifre YANLIŞ!");

    }

}
