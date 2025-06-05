#include "finalwindow.h"
#include "ui_finalwindow.h"
#include <QDebug>
#include <QMovie>


FinalWindow::FinalWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::FinalWindow)
{
    ui->setupUi(this);
}

void FinalWindow::set_final(int final_id){
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("game.sqlite");
    if (!db.open()){
        qDebug() << "Ошибка подключения к БД:" << db.lastError().text();
    } else {
        qDebug() << "База подключена успешно.";
    }
    QSqlQuery query;
    query.prepare("SELECT * FROM finals WHERE id = ?");
    query.addBindValue(final_id);
    qDebug() << final_id;
    if(query.exec()){
        while(query.next()){
            QMovie *movie = new QMovie(query.value("background").toString());
            qDebug() << query.value("background").toString() << query.value("text").toString();
            ui->background->setMovie(movie);
            movie->start();
            ui->text->setText(query.value("text").toString());
        }
    } else {
        qDebug() << "error final query exec" << query.lastError().text();
    }
}

FinalWindow::~FinalWindow()
{
    delete ui;
}

void FinalWindow::on_endbutton_clicked()
{
    clicked = true;
    this->close();
}

