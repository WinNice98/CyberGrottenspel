#ifndef LOAD_GAME_H
#define LOAD_GAME_H

#include <QDialog>
#include <QSqlTableModel>
#include "game.h"

namespace Ui {
class load_game;
}

class load_game : public QDialog
{
    Q_OBJECT

public:
    explicit load_game(QWidget *parent = nullptr);
    QSqlTableModel *model;
    player input_player;
    ~load_game();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::load_game *ui;
};

#endif // LOAD_GAME_H
