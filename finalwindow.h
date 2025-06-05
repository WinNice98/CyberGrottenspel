#ifndef FINALWINDOW_H
#define FINALWINDOW_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QString>
#include <QTextStream>

namespace Ui {
class FinalWindow;
}

class FinalWindow : public QDialog
{
    Q_OBJECT

public:
    explicit FinalWindow(QWidget *parent = nullptr);
    void set_final(int final_id);
    bool clicked = false;
    ~FinalWindow();

private slots:
    void on_endbutton_clicked();

private:
    Ui::FinalWindow *ui;
    QSqlDatabase db;
};

#endif // FINALWINDOW_H
