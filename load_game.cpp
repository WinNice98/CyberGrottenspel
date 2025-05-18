#include "load_game.h"
#include "ui_load_game.h"
#include "game.h"
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QItemSelectionModel>
#include <QMessageBox>

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
    // name, level, money, items, hp, stamina, xp, sleep
    item input_inv[50];
    input_player.load(model->data(model->index(row, 0)).toString(), model->data(model->index(row,1)).toInt(), model->data(model->index(row,2)).toInt(), input_inv, model->data(model->index(row, 3)).toInt(), model->data(model->index(row,4)).toInt(),  model->data(model->index(row, 5)).toInt() , model->data(model->index(row, 6)).toInt());
}

