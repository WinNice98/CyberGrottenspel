#include "about.h"
#include "ui_about.h"

about::about(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::about)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Window);
    setWindowTitle("О программе");
}

about::~about()
{
    delete ui;
}
