#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMovie>
#include <QResizeEvent>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include "game.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void set_control_mode(bool dialog);
    void set_background(int id);
    void set_character(int id);
    void set_enemy(int id);
    void add_text(QString input);
    void set_text(QString input);
    player current_player;
    void set_unactive();
    void set_active();
    void set_status(player current_player);
    QSqlDatabase db;
    void connect_db();
    void change_img_geometry_dialog();
    void change_img_geometry_enemy();
    void change_back_geometry();
    void check();
    void set_dialog(int id);
    void show_dialogs(int place_id);
    bool dialog_started = false;
    int current_dialog_id;
    int current_character_id;
    ~MainWindow();

protected:
    void resizeEvent(QResizeEvent *event) override {
        int w = event->size().width();
        int h = w * 9 / 16; // Высчитываем высоту на основе ширины
        resize(w, h); // Фиксируем размеры
        change_img_geometry_dialog();
        change_img_geometry_enemy();
        change_back_geometry();
    }

private slots:
    void on_aboutbutton_clicked();

    void on_loadbutton_clicked();

    void on_f1button_clicked();

    void on_newgamebutton_clicked();

    void on_pushButton_2_clicked();

    void on_var1_clicked();

    void on_var2_clicked();

    void on_var3_clicked();

    void on_var4_clicked();

    void on_var5_clicked();

    void on_var6_clicked();

    void on_var7_clicked();

    void on_changebutton_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
