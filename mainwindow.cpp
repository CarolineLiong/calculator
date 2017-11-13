#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QString>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    display();
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::display()
{
    ui->left_operand->setText(_left_operand);
    ui-> right_operand-> setText(_right_operand);
    ui->memory_value->setText(_memory_value);
    //ui->left_operand->setText(QString::fromStdString());
}

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox m;
    m.setText("Caroline Liongosari (c) 2016");
    m.exec();
}

void MainWindow::on_actionQuit_triggered()
{
    exit(0);
}

void MainWindow::on_subraction_clicked()
{

    bigint l = bigint(_left_operand);
    bigint r = bigint(_right_operand);
    l -= r;
    _left_operand = l.toQString();
    display();
}

void MainWindow::on_addition_clicked()
{
    bigint l = bigint(_left_operand);
    bigint r = bigint(_right_operand);
    l += r;
    _left_operand = l.toQString();
    display();
}

void MainWindow::on_memory_store_clicked()
{
   _memory_value = _left_operand;
    display();
}

void MainWindow::on_memory_recall_clicked()
{
    _right_operand = _memory_value;
    display();
}

void MainWindow::on_left_operand_textChanged(const QString &arg1)
{
   _left_operand = arg1;
   display();
}

void MainWindow::on_right_operand_textChanged(const QString &arg1)
{
    _right_operand = arg1;
    display();
}

void MainWindow::on_multiplication_clicked()
{
    bigint l = bigint(_left_operand);
    bigint r = bigint(_right_operand);
    l *= r;
    _left_operand = l.toQString();
    display();

}
