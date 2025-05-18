#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "about.h"
#include "load_game.h"
#include "new_game.h"

void MainWindow::set_background(int id){
    // нужно из бд брать
    QString name;
    name = ":/gif/defback.gif";
    QMovie *movie = new QMovie(name);
    ui->background->setMovie(movie);
    movie->start();
}

void MainWindow::set_character(int id){
    // нужно из бд брать
    QMovie *img = new QMovie(":/img/august_hart.jpg");
    ui->character->setMovie(img);
    img->start();
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    set_background(1);
    QString dial = "Test Dialog! \nGood Luck, Have Fun!\n";
    QString stat = "Test Status! \nGood Luck, Have Fun!\n";
    ui->text->setText(dial);
    ui->stats->setText(stat);
    ui->fightmod->setHidden(true);
    ui->dialogmod->setHidden(true);
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

void MainWindow::add_to_str(QString text){
    ui->text->setText(ui->text->text().append(text));
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
}

void MainWindow::on_loadbutton_clicked()
{
    load_game *window = new load_game(this);
    if (window->exec() == QDialog::Accepted){
        current_player = window->input_player;
        qDebug() << current_player.stats();
    }
}


void MainWindow::on_f1button_clicked()
{

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

