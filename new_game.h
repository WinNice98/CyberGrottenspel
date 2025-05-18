#ifndef NEW_GAME_H
#define NEW_GAME_H

#include <QDialog>

namespace Ui {
class new_game;
}

class new_game : public QDialog
{
    Q_OBJECT

public:
    explicit new_game(QWidget *parent = nullptr);
    QString give_name();
    ~new_game();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::new_game *ui;
};

#endif // NEW_GAME_H
