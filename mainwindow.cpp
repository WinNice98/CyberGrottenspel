#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "about.h"
#include "load_game.h"
#include "save_game.h"
#include "new_game.h"
#include "information.h"
#include <QFile>
#include <QTimer>

void MainWindow::connect_db(){
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("game.sqlite");
    if (!db.open()){
        qDebug() << "Ошибка подключения к БД:" << db.lastError().text();
    } else {
        qDebug() << "База подключена успешно.";
    }
}

void MainWindow::set_dialog(int id){
    connect_db();
    QSqlQuery query;
    //query.prepare("SELECT * FROM answers WHERE id = ?")
}

void MainWindow::set_control_mode(bool dialog){
    if(dialog){
        ui->fightmod->setHidden(true);
        ui->dialogmod->setHidden(false);
    } else {
        ui->fightmod->setHidden(false);
        ui->dialogmod->setHidden(true);
    }
}

void MainWindow::show_dialogs(int place_id){
    if(place_id == 5){
        ui->var1->setText("Пойти в общежитие");
        ui->var1->setHidden(false);
        ui->var2->setText("Пойти в трущобы для драки");
        ui->var2->setHidden(false);
        ui->var3->setText("Пойти в лечебницу");
        ui->var3->setHidden(false);
        ui->var4->setText("Пойти поесть");
        ui->var4->setHidden(false);
        ui->var5->setHidden(true);
        ui->var6->setHidden(true);
        ui->var7->setHidden(true);
    } else {
        connect_db();
        QSqlQuery query;
        if (dialog_started){
            query.prepare("SELECT * FROM dialogs WHERE character = ?");
            query.addBindValue(place_id);
            set_character(place_id);
            int dialog_id;
            if(query.exec()){
                int i = 0;
                while(query.next()){
                    if (current_player.whats_dialog(place_id) == i){
                        QSqlQuery query2;
                        query2.prepare("SELECT * FROM characters WHERE id = ?");
                        query2.addBindValue(place_id);
                        if(query2.exec()){
                            QString name = query2.value("name").toString();
                            add_text(name + ": " + query.value("text").toString());
                            query2.finish();
                            dialog_id = query.value("id").toInt();
                        } else {
                            qDebug() << "query2" << query2.lastError().text();
                        }
                        current_dialog_id = dialog_id;
                        current_character_id = place_id;
                        query.finish();
                    }
                    i++;
                }
                if (i > 4){
                    dialog_started = false;
                    show_dialogs(current_player.whats_place());
                    set_character(-1);
                    ui->changebutton->setHidden(false);
                }
            } else {
                qDebug() << query.lastError().text();
            }
            query.finish();
            query.prepare("SELECT * FROM answers WHERE dialog = ?");
            query.addBindValue(dialog_id);
            if(query.exec()){
                int j = 1;
                while(query.next()){
                    ui->dialogmod->findChild<QPushButton*>("var" + QString::number(j))->setText(query.value("text").toString());
                    ui->dialogmod->findChild<QPushButton*>("var" + QString::number(j))->setHidden(false);
                    j++;
                }
                if(j - 1 < 7){
                    while (j < 8){
                        ui->dialogmod->findChild<QPushButton*>("var" + QString::number(j))->setHidden(true);
                        j++;
                    }
                    ui->changebutton->setHidden(true);
                }
            } else {
                qDebug() << query.lastError().text();
            }
        } else {
            query.prepare("SELECT * FROM characters WHERE place = ?");
            query.addBindValue(place_id);
            if (query.exec()){
                int i = 1;
                while(query.next()){
                    ui->dialogmod->findChild<QPushButton*>("var" + QString::number(i))->setText("Поговорить с " + query.value("name").toString());
                    ui->dialogmod->findChild<QPushButton*>("var" + QString::number(i))->setHidden(false);
                    i++;
                }
                if(i - 1 < 7){
                    while (i < 8){
                        ui->dialogmod->findChild<QPushButton*>("var" + QString::number(i))->setHidden(true);
                        i++;
                    }
                    ui->changebutton->setHidden(false);
                }
            } else {
                qDebug() << query.lastError().text();
            }
            ui->changebutton->setText("Сменить локацию");
            set_control_mode(1);
            set_active();
        }
    }
}

void MainWindow::set_background(int id){
    connect_db();
    QSqlQuery query;
    query.prepare("SELECT gif FROM places WHERE id = ?");
    query.addBindValue(id);
    QString path;
    if (query.exec() && query.next()) {
        path = query.value("gif").toString();
    } else {
        qDebug() << "[GIF] Ошибка запроса или место не найдено:" << query.lastError().text();
    }
    query = QSqlQuery();
    QMovie *movie = new QMovie(path);
    ui->background->setMovie(movie);
    movie->start();
    ui->character->raise();
    show_dialogs(id);
    QTimer::singleShot(0, this, [this]() {
        this->resize(this->width() + 1, this->height() + 1);
        this->resize(this->width() - 1, this->height() - 1);
    });
}

void MainWindow::set_character(int id){
    QSqlQuery query;
    query.prepare("SELECT image FROM characters WHERE id = ?");
    query.addBindValue(id);
    QString path;
    if (query.exec() && query.next()) {
        path = query.value("image").toString();
    } else {
        qDebug() << "[Изображение] Ошибка запроса или место не найдено:" << query.lastError().text();
    }
    QMovie *img = new QMovie(path);
    qDebug() << path;
    ui->character->setMovie(img);
    img->start();
    ui->character->raise();
    QTimer::singleShot(0, this, [this]() {
        this->resize(this->width() + 1, this->height() + 1);
        this->resize(this->width() - 1, this->height() - 1);
    });
}

void MainWindow::set_enemy(int id){
    QSqlQuery query;
    query.prepare("SELECT img FROM enemy WHERE id = ?");
    query.addBindValue(id);
    QString path;
    if (query.exec() && query.next()) {
        path = query.value("img").toString();
    } else {
        qDebug() << "[Изображение enemy] Ошибка запроса или место не найдено:" << query.lastError().text();
    }
    QMovie *img = new QMovie(path);
    ui->enemy->setMovie(img);
    img->start();
    ui->enemy->raise();
    QTimer::singleShot(0, this, [this]() {
        this->resize(this->width() + 1, this->height() + 1);
        this->resize(this->width() - 1, this->height() - 1);
    });
}




void MainWindow::add_text(QString input){
    ui->text->append(input);
}

void MainWindow::change_img_geometry_dialog(){
    ui->character->setGeometry(ui->display->width() - 200, ui->display->height()/2 - 100, 200, 200);
}

void MainWindow::change_img_geometry_enemy(){
    ui->enemy->setGeometry(ui->display->width()/2 - 100, ui->display->height() - 200, 200, 200);
}

void MainWindow::change_back_geometry(){
    ui->background->setGeometry(0, 0, ui->display->width(), ui->display->height());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_aboutbutton_clicked()
{
    about *window = new about(this);
    window->show();
}

void MainWindow::set_unactive(){
    ui->but1->setEnabled(false);
    ui->but2->setEnabled(false);
    ui->but3->setEnabled(false);
    ui->but4->setEnabled(false);
    ui->but5->setEnabled(false);
    ui->but6->setEnabled(false);
    ui->but7->setEnabled(false);
    ui->but8->setEnabled(false);
    ui->but9->setEnabled(false);
    ui->var1->setEnabled(false);
    ui->var2->setEnabled(false);
    ui->var3->setEnabled(false);
    ui->var4->setEnabled(false);
    ui->var5->setEnabled(false);
    ui->var6->setEnabled(false);
    ui->var7->setEnabled(false);
    ui->changebutton->setEnabled(false);
}

void MainWindow::set_active(){
    ui->but1->setEnabled(true);
    ui->but2->setEnabled(true);
    ui->but3->setEnabled(true);
    ui->but4->setEnabled(true);
    ui->but5->setEnabled(true);
    ui->but6->setEnabled(true);
    ui->but7->setEnabled(true);
    ui->but8->setEnabled(true);
    ui->but9->setEnabled(true);
    ui->var1->setEnabled(true);
    ui->var2->setEnabled(true);
    ui->var3->setEnabled(true);
    ui->var4->setEnabled(true);
    ui->var5->setEnabled(true);
    ui->var6->setEnabled(true);
    ui->var7->setEnabled(true);
    ui->changebutton->setEnabled(true);
}

void MainWindow::set_status(player current_player){
    ui->stats->setText("Имя: " + current_player.stats() + "\nЗдоровье: " + QString::number(current_player.whats_hp()) + "/" + QString::number(current_player.max_health(current_player.whats_lvl())) + "\nДеньги: " + QString::number(current_player.whats_money()) + "\nСтамина: " +  QString::number(current_player.whats_stamina()) + "/100\nСон: " + QString::number(current_player.whats_sleep()) + "/100\nУровень: " + QString::number(current_player.whats_lvl()) + "\nОпыта до следующего уровня: " + QString::number(current_player.whats_xp()));
}

void MainWindow::set_text(QString input){
    ui->text->setText(input);

}

void MainWindow::on_loadbutton_clicked()
{
    load_game *window = new load_game(this);
    if (window->exec() == QDialog::Accepted && window->input_player.stats() != ""){
        current_player = window->input_player;
        set_status(current_player);
        set_text("");
        int id = current_player.whats_place();
        set_background(id);
    }
}


void MainWindow::on_f1button_clicked()
{
    information *window = new information(this);
    window->exec();
}

void MainWindow::on_newgamebutton_clicked()
{
    new_game *window = new new_game(this);
    if(window->exec() == QDialog::Accepted){
        if (window->give_name() == ""){
            set_unactive();
        } else {
            set_active();
        }
        current_player.set_name(window->give_name());
    }
}


void MainWindow::on_pushButton_2_clicked()
{
    save_game *window = new save_game(this);
    if(window->exec() == QDialog::Accepted){
        window->input_player(current_player);
    } else {

    }
}


void MainWindow::check(){
    QSqlQuery query;

}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect_db();
    ui->character->setAttribute(Qt::WA_TranslucentBackground);
    ui->background->setAttribute(Qt::WA_TranslucentBackground);
    ui->enemy->setAttribute(Qt::WA_TranslucentBackground);
    set_background(5);
    set_enemy(0);
    set_unactive();
    //ui->text->setWordWrap(true);
    ui->text->setFixedWidth(150);
}

void MainWindow::on_var1_clicked()
{
    if (current_player.whats_place() == 5){
        set_background(6);
        current_player.change_place(6);
        ui->var1->setText("Сохранить игру");
        ui->var1->setHidden(false);
        ui->var2->setText("Поспать");
        ui->var1->setHidden(false);
        ui->var4->setHidden(true);
        ui->var5->setHidden(true);
        ui->var6->setHidden(true);
        ui->var7->setHidden(true);
    } else {
        if (current_player.whats_place() == 6){
            save_game *window = new save_game(this);
            window->exec();
        }
        connect_db();
        if(dialog_started){
            QSqlQuery query;
            query.prepare("SELECT * FROM answers WHERE id = ?");
            query.addBindValue(current_dialog_id);
            if(query.exec()){
                int i = 0;
                while(query.next()){
                    if(i == 0){
                        current_player.change_attitude(current_character_id, query.value("attitude").toInt());
                        add_text("\n\nПоследствие ответа: " + query.value("feelings").toString() + "\n\n");
                    }
                    i++;
                }
            } else {
                qDebug() << query.lastError().text();
            }
            query.finish();
            current_player.change_dialog(current_character_id);
            show_dialogs(current_character_id);
        } else {
            dialog_started = true;
            show_dialogs(0);
        }
    }
}

void MainWindow::on_var2_clicked()
{
    if (current_player.whats_place() == 5){
        set_background(8);
        set_control_mode(false);
        set_enemy(1);
    } else {
        if (current_player.whats_place() == 6){

        } else {
            connect_db();
            if(dialog_started){
                QSqlQuery query;
                query.prepare("SELECT * FROM answers WHERE id = ?");
                query.addBindValue(current_dialog_id);
                if(query.exec()){
                    int i = 0;
                    while(query.next()){
                        if(i == 1){
                            current_player.change_attitude(current_character_id, query.value("attitude").toInt());
                            add_text("Последствие ответа: " + query.value("feelings").toString());
                        }
                        i++;
                    }
                } else {
                    qDebug() << query.lastError().text();
                }
                query.finish();
                current_player.change_dialog(current_character_id);
                show_dialogs(1);
            } else {
                dialog_started = true;
                show_dialogs(1);
            }
        }
    }

}

void MainWindow::on_var3_clicked()
{
    connect_db();
    if(dialog_started){
        QSqlQuery query;
        query.prepare("SELECT * FROM answers WHERE id = ?");
        query.addBindValue(current_dialog_id);
        if(query.exec()){
            int i = 0;
            while(query.next()){
                if(i == 2){
                    current_player.change_attitude(current_character_id, query.value("attitude").toInt());
                    add_text("Последствие ответа: " + query.value("feelings").toString());
                }
                i++;
            }
        } else {
            qDebug() << query.lastError().text();
        }
        query.finish();
        current_player.change_dialog(current_character_id);
        show_dialogs(2);
    } else {
        dialog_started = true;
        show_dialogs(2);
    }
}


void MainWindow::on_var4_clicked()
{
    connect_db();
    if(dialog_started){
        QSqlQuery query;
        query.prepare("SELECT * FROM answers WHERE id = ?");
        query.addBindValue(current_dialog_id);
        if(query.exec()){
            int i = 0;
            while(query.next()){
                if(i == 3){
                    current_player.change_attitude(current_character_id, query.value("attitude").toInt());
                    add_text("Последствие ответа: " + query.value("feelings").toString());
                }
                i++;
            }
        } else {
            qDebug() << query.lastError().text();
        }
        query.finish();
        current_player.change_dialog(current_character_id);
        show_dialogs(3);
    } else {
        dialog_started = true;
        show_dialogs(3);
    }
}


void MainWindow::on_var5_clicked()
{
    connect_db();
    if(dialog_started){
        QSqlQuery query;
        query.prepare("SELECT * FROM answers WHERE id = ?");
        query.addBindValue(current_dialog_id);
        if(query.exec()){
            int i = 0;
            while(query.next()){
                if(i == 4){
                    current_player.change_attitude(current_character_id, query.value("attitude").toInt());
                    add_text("Последствие ответа: " + query.value("feelings").toString());
                }
                i++;
            }
        } else {
            qDebug() << query.lastError().text();
        }
        query.finish();
        current_player.change_dialog(current_character_id);
        show_dialogs(4);
    } else {
        dialog_started = true;
        show_dialogs(4);
    }
}


void MainWindow::on_var6_clicked()
{
    connect_db();
    if(dialog_started){
        QSqlQuery query;
        query.prepare("SELECT * FROM answers WHERE id = ?");
        query.addBindValue(current_dialog_id);
        if(query.exec()){
            int i = 0;
            while(query.next()){
                if(i == 5){
                    current_player.change_attitude(current_character_id, query.value("attitude").toInt());
                    add_text("\n\nПоследствие ответа: " + query.value("feelings").toString());
                }
                i++;
            }
        } else {
            qDebug() << query.lastError().text();
        }
        query.finish();
        current_player.change_dialog(current_character_id);
        show_dialogs(5);
    } else {
        dialog_started = true;
        show_dialogs(5);
    }
}


void MainWindow::on_var7_clicked()
{
    connect_db();
    if(dialog_started){
        QSqlQuery query;
        query.prepare("SELECT * FROM answers WHERE id = ?");
        query.addBindValue(current_dialog_id);
        if(query.exec()){
            int i = 0;
            while(query.next()){
                if(i == 6){
                    current_player.change_attitude(current_character_id, query.value("attitude").toInt());
                    add_text("Последствие ответа: " + query.value("feelings").toString());
                }
                i++;
            }
        } else {
            qDebug() << query.lastError().text();
        }
        query.finish();
        current_player.change_dialog(current_character_id);
        show_dialogs(6);
    } else {
        dialog_started = true;
        show_dialogs(6);
    }
}


void MainWindow::on_changebutton_clicked()
{
    current_player.change_place();
    set_background(current_player.whats_place());
}

