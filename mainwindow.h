#ifndef MAINWINDOW_H
#include "bigint.h"
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionAbout_triggered();

    void on_actionQuit_triggered();

    void on_subraction_clicked();

    void on_addition_clicked();

    void on_memory_store_clicked();

    void on_memory_recall_clicked();

    void on_left_operand_textChanged(const QString &arg1);

    void on_right_operand_textChanged(const QString &arg1);

    void on_multiplication_clicked();

private:
    Ui::MainWindow *ui;
    QString _left_operand, _right_operand, _memory_value;
    //invariants:
    //  _left_operand, _right_operand, _memory_value are the left right operands and memory values as Qstrings

    //pre:none
    //post: takes the entered _left_operand, _right_operand, and _memory_value strings and display them in their corresponding screens
    void display();
};

#endif // MAINWINDOW_H
