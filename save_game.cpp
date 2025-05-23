#include "save_game.h"
#include "ui_save_game.h"
#include <QDebug>
#include <QAbstractItemView>
#include <QSqlError>
#include <QSqlQuery>
#include <QMessageBox>

save_game::save_game(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::save_game)
{
    ui->setupUi(this);
    QSqlDatabase users = QSqlDatabase::addDatabase("QSQLITE");
    users.setDatabaseName("users.sqlite");
    if(!users.open()){
        qDebug() << users.lastError().text();
    }
    model = new QSqlTableModel(this, users);
    model->setTable("users");
    model->select();
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    ui->tableView->setModel(model);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    model->submitAll();
}

void save_game::input_player(player input){
    QSqlDatabase users = QSqlDatabase::addDatabase("QSQLITE");
    users.setDatabaseName("users.sqlite");
    if(!users.open()){
        qDebug() << users.lastError().text();
    }
    QSqlQuery query;
    query.prepare("UPDATE users SET name = ?, level = ?, money = ?, items = ?, hp = ?, stamina = ?, xp = ?, sleep = ?, current_location = ?, dialogs = ?, attitude = ? WHERE id = ?");
    query.addBindValue(input.stats());
    query.addBindValue(input.whats_lvl());
    query.addBindValue(input.whats_money());
    QString items = "";
    for(int i = 0; i < 50; i++){
        items.append(QString::number(input.give_item(i).give_item_id()));
        items.append(" ");
        items.append(QString::number(input.give_item(i).give_item_durability()));
        items.append(" ");
        items.append(QString::number(input.give_item(i).give_item_num()));
        items.append(" ");
        items.append(QString::number(input.give_item(i).give_item_chosen()));
        items.append("\n");
    }
    query.addBindValue(items);
    query.addBindValue(input.whats_hp());
    query.addBindValue(input.whats_sleep());
    query.addBindValue(input.whats_place());
    QString dialogs = "", attitude = "";
    for(int i = 0; i < 15; i++){
        dialogs.append(QString::number(input.whats_dialog(i)));
        dialogs.append(" ");
        attitude.append(QString::number(input.whats_attitude(i)));
        attitude.append(" ");
    }
    query.addBindValue(dialogs);
    query.addBindValue(attitude);
    query.addBindValue(id);
    if(query.exec()){

    } else {
        qDebug() << "Ошибка при сохраннении: " << query.lastError().text();
    }
}

save_game::~save_game()
{
    delete ui;
}

void save_game::on_buttonBox_accepted()
{
    QItemSelectionModel *selected = ui->tableView->selectionModel();
    if(!selected->hasSelection()){
        QMessageBox::warning(this, "Вы не выбрали сохранение для сохранения", "Для выбора выделите строку и нажмите ОК");
        return;
    }
    QModelIndex index = ui->tableView->currentIndex();
    int row = index.row();
    QString name = model->data(model->index(row, 1)).toString();
    id = model->data(model->index(row, 0)).toInt();
}


void save_game::on_addnewbutton_clicked()
{
    int row = model->rowCount();
    model->insertRow(row);

    model->setData(model->index(row, 1), "");
}

