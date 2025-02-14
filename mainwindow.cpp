#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "about.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QMovie *movie = new QMovie(":/gif/defback.gif");
    ui->background->setMovie(movie);
    ui->background->setScaledContents(true);
    QString dial = "Test Dialog! \nGood Luck, Have Fun!\n";
    QString stat = "Test Status! \nGood Luck, Have Fun!\n";
    ui->text->setText(dial);
    ui->stats->setText(stat);
    movie->start();
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

