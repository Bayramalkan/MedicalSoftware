#include "hastabilgi.h"
#include "ui_hastabilgi.h"
#include <QMessageBox>

HastaBilgi::HastaBilgi(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HastaBilgi)
{
    ui->setupUi(this);
    MainWindow conn;
            if(!conn.connOpen())

                ui->label_sec_status->setText("VERİ TABANINA BAĞLANILAMADI");
            else
                ui->label_sec_status->setText("VERİ TABANINA BAĞLANILDI");
}

HastaBilgi::~HastaBilgi()
{
    delete ui;
}

void HastaBilgi::on_pushButton_clicked()
{
    MainWindow conn;
    QString sira,ad,soyad,tc,doktor,klinik;
    sira=ui->txt_sira->text();
    ad=ui->txt_ad->text();
    soyad=ui->txt_soyad->text();
    tc=ui->txt_tc->text();
    doktor=ui->txt_doktor->text();
    klinik=ui->txt_klinik->text();


    if(!conn.connOpen()){
        qDebug()<<"VERİ TABANI HATASI";
        return;
    }

    conn.connOpen();
    QSqlQuery qry;
    qry.prepare("insert into hastalar (sira,ad,soyad,tc,doktor,klinik) values ('"+sira+"','"+ad+"','"+soyad+"','"+tc+"','"+doktor+"','"+klinik+"')");

    if(qry.exec())
    {
        QMessageBox::information(this,tr("Kayıt"),tr("HASTA KAYDEDİLDİ!"));
        conn.connClose();
    }
    else
    {
        QMessageBox::information(this,tr("HATA"),qry.lastError().text());

    }

}

void HastaBilgi::on_pushButton_edit_clicked()
{
    MainWindow conn;
    QString sira,ad,soyad,tc,doktor,klinik;
    sira=ui->txt_sira->text();
    ad=ui->txt_ad->text();
    soyad=ui->txt_soyad->text();
    tc=ui->txt_tc->text();
    doktor=ui->txt_doktor->text();
    klinik=ui->txt_klinik->text();


    if(!conn.connOpen()){
        qDebug()<<"VERİ TABANI HATASI";
        return;
    }

    conn.connOpen();
    QSqlQuery qry;
    qry.prepare("select * from hastalar where tc='"+tc+"'");
    //qry.prepare("update hastalar set sira='"+sira+"',ad='"+ad+"',soyad='"+soyad+"',doktor='"+doktor+"',klinik='"+klinik+"' where tc='"+tc+"'");

    if(qry.exec())
    {
        int count = 0;
        while(qry.next()){
            count++;
        }
        if(count==1){
        qry.exec("UPDATE hastalar SET sira='"+sira+"',ad='"+ad+"',soyad='"+soyad+"',tc='"+tc+"',doktor='"+doktor+"',klinik='"+klinik+"' where tc='"+tc+"'");
        //qry.prepare("update hastalar set sira='"+sira+"',ad='"+ad+"',soyad='"+soyad+"',tc='"+tc+"',doktor='"+doktor+"',klinik='"+klinik+"' where tc='"+tc+"'");
        QMessageBox::information(this,tr("Güncelleme"),tr("HASTA GÜNCELLENDİ!"));
        conn.connClose();
        }
        else if(count>=1){
        qry.exec("UPDATE hastalar SET sira='"+sira+"',ad='"+ad+"',soyad='"+soyad+"',tc='"+tc+"',doktor='"+doktor+"',klinik='"+klinik+"' where sira='"+sira+"' ");
            QMessageBox::information(this,tr("Güncelleme"),tr("HASTA                  GÜNCELLENDİ!"));
            conn.connClose();
        }
        else
        {
            QMessageBox::critical(this,tr("HATA"),tr("HASTA BULUNAMADIĞI İÇİN \nHASTA GÜNCELLEME İŞLEMİ GERÇEKLEŞEMEDİ !"));
        }
    }

}


void HastaBilgi::on_pushButton_sil_clicked()
{
    MainWindow conn;
    QString sira,ad,soyad,tc,doktor,klinik;
    sira=ui->txt_sira->text();
    //ad=ui->txt_ad->text();
   //soyad=ui->txt_soyad->text();
   tc=ui->txt_tc->text();
   //doktor=ui->txt_doktor->text();
   //klinik=ui->txt_klinik->text();




    if(!conn.connOpen()){
        qDebug()<<"VERİ TABANI HATASI";
        return;
    }

    conn.connOpen();
    QSqlQuery qry;
    qry.prepare("select * from hastalar where sira='"+sira+"' and tc='"+tc+"'");


    if(qry.exec())
    {
        int count=0;
        while(qry.next())
        {
            count++;
        }
        if(count >= 1){
        qry.exec("Delete from hastalar where sira='"+sira+"'");
        QMessageBox::information(this,tr("Sil"),tr("HASTA KAYDI SİLİNDİ!"));
        conn.connClose();
        }
        else
        {
            QMessageBox::critical(this,tr("HATA"),tr("HASTA BULUNAMADIĞI İÇİN \n SİLME İŞLEMİ GERÇEKLEŞEMEDİ !"));

        }
    }

}

void HastaBilgi::on_pushButton_goster_clicked()
{
   MainWindow conn;
   QSqlQueryModel * modal= new QSqlQueryModel();

   conn.connOpen();
   QSqlQuery* qry=new QSqlQuery(conn.mydb);

   qry->prepare("select * from hastalar");

   qry->exec();
   modal->setQuery(*qry);
   ui->tableView->setModel(modal);

   conn.connClose();
   qDebug() <<(modal->rowCount());
}

void HastaBilgi::on_pushButton_arama_clicked()
{
    MainWindow conn;
    QSqlQueryModel * modal= new QSqlQueryModel();
    conn.connOpen();

    QString tc;
    tc=ui->txt_arama->text();


    QSqlQuery* qry=new QSqlQuery(conn.mydb);
    qry->prepare("select * from hastalar where tc='"+tc+"'");

    //qry->exec();
    if(qry->exec())
    {
        int count=0;
        while(qry->next())
        {
            count++;
        }
        if(count >= 1){
        QMessageBox::information(this,tr("Arama"),tr("HASTA BULUNDU!"));
        modal->setQuery(*qry);
        ui->tableView->setModel(modal);
        conn.connClose();
        qDebug() <<(modal->rowCount());
        }
        else if(count==0)
        {
        QMessageBox::critical(this,tr("Hata"),tr("HASTA BULUNAMADI!"));
        }
    }

}

void HastaBilgi::on_tableView_activated(const QModelIndex &index)
{
    QString secim=ui->tableView->model()->data(index).toString();

    MainWindow conn;
    if(!conn.connOpen()){
        qDebug()<<"VERİ TABANI HATASI";

        return;
    }
    conn.connOpen();
    QSqlQuery qry;
    qry.prepare("select * from hastalar where sira='"+secim+"' or ad='"+secim+"' or soyad='"+secim+"' or tc='"+secim+"' or doktor='"+secim+"' or klinik='"+secim+"'");

    if(qry.exec()){
        while(qry.next())
        {
            ui->txt_sira->setText(qry.value(0).toString());
            ui->txt_ad->setText(qry.value(1).toString());
            ui->txt_soyad->setText(qry.value(2).toString());
            ui->txt_tc->setText(qry.value(3).toString());
            ui->txt_doktor->setText(qry.value(4).toString());
            ui->txt_klinik->setText(qry.value(5).toString());
        }
    }
    else
    {
        QMessageBox::critical(this,tr("HATA"),tr("SEÇİM YAPILAMADI"));
    }
}

void HastaBilgi::on_pushButton_Temiz_clicked()
{

    ui->txt_sira->clear();
    ui->txt_ad->clear();
    ui->txt_soyad->clear();
    ui->txt_tc->clear();
    ui->txt_doktor->clear();
    ui->txt_klinik->clear();

}
