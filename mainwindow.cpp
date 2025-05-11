#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "about.h"

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

