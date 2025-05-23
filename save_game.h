#ifndef SAVE_GAME_H
#define SAVE_GAME_H

#include <QDialog>
#include "game.h"
#include <QSqlTableModel>

namespace Ui {
class save_game;
}

class save_game : public QDialog
{
    Q_OBJECT

public:
    explicit save_game(QWidget *parent = nullptr);
    QSqlTableModel *model;
    void input_player(player input);
    int id;
    ~save_game();

private slots:
    void on_buttonBox_accepted();

    void on_addnewbutton_clicked();

private:
    Ui::save_game *ui;
};

#endif // SAVE_GAME_H
