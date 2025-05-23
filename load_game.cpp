#include "load_game.h"
#include "ui_load_game.h"
#include "game.h"
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QItemSelectionModel>
#include <QMessageBox>
#include <QSqlQuery>
#include <QTextStream>

load_game::load_game(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::load_game)
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

load_game::~load_game()
{
    delete ui;
}

void load_game::on_buttonBox_accepted()
{
    QItemSelectionModel *selected = ui->tableView->selectionModel();
    if(!selected->hasSelection()){
        QMessageBox::warning(this, "Вы не выбрали сохранение для загрузки", "Для выбора выделите строку и нажмите ОК");
        return;
    }
    int row = selected->selectedRows().first().row();
    // id, name, level, money, items, hp, stamina, xp, sleep, date
    QString input_iventory = model->data(model->index(row, 4)).toString();
    item input_inv[50];
    for(int i = 0; i < 50; i++){
        QTextStream stream(&input_iventory);
        int id, durability, num, chosen_int;
        stream >> id >> durability >> num >> chosen_int;
        bool chosen;
        if (chosen_int){
            chosen = true;
        } else {
            chosen = false;
        }
        input_inv[i].set_item(id, durability, num, chosen);
    }
    int input_attitude[15], input_dialogs[15];
    QString dialogs = model->data(model->index(row, 11)).toString(), attitude = model->data(model->index(row, 12)).toString();
    QTextStream stream1(&dialogs);
    QTextStream stream2(&attitude);
    for(int i = 0; i < 15; i++){
        stream1 >> dialogs[i];
        stream2 >> attitude[i];
    }
    input_player.load(model->data(model->index(row, 1)).toString(), model->data(model->index(row,2)).toInt(), model->data(model->index(row,3)).toInt(), input_inv, model->data(model->index(row, 5)).toInt(), model->data(model->index(row,6)).toInt(),  model->data(model->index(row, 7)).toInt() ,model->data(model->index(row, 8)).toInt(), model->data(model->index(row, 10)).toInt(), input_dialogs, input_attitude);
}

