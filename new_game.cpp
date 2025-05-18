#include "new_game.h"
#include "ui_new_game.h"
#include <QMessageBox>
new_game::new_game(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::new_game)
{
    ui->setupUi(this);
}

QString new_game::give_name(){
    return ui->lineEdit->text();
}

new_game::~new_game()
{
    delete ui;
}

void new_game::on_buttonBox_accepted()
{
    if (ui->lineEdit->text().trimmed().isEmpty()){
        QMessageBox::warning(this, "Ошибка ввода!", "Перед началом игры введите имя игрока!");
    }
}

