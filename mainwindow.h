#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMovie>
#include <QResizeEvent>

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
    void add_to_str(QString text);
    ~MainWindow();

protected:
    void resizeEvent(QResizeEvent *event) override {
        int w = event->size().width();
        int h = w * 9 / 16; // Высчитываем высоту на основе ширины
        resize(w, h); // Фиксируем размеры
    }

private slots:
    void on_aboutbutton_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
