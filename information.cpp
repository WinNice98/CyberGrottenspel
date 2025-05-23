#include "information.h"
#include "ui_information.h"

information::information(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::information)
{
    ui->setupUi(this);
}

information::~information()
{
    delete ui;
}
