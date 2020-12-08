#ifndef HASTABILGI_H
#define HASTABILGI_H

#include <QDialog>
#include "mainwindow.h"
namespace Ui {
class HastaBilgi;
}

class HastaBilgi : public QDialog
{
    Q_OBJECT

public:

    explicit HastaBilgi(QWidget *parent = nullptr);
    ~HastaBilgi();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_edit_clicked();

    void on_pushButton_sil_clicked();

    void on_pushButton_goster_clicked();

    void on_pushButton_arama_clicked();

    void on_tableView_activated(const QModelIndex &index);

    void on_pushButton_Temiz_clicked();

private:
    Ui::HastaBilgi *ui;
};

#endif // HASTABILGI_H
