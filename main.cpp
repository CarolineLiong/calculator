/**#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}**/

#include "mainwindow.h"
#include <QApplication>
#include <iostream>

int main(int argc, char *argv[])
{

  std::cout <<  bigint() << std::endl;
  std::cout << -bigint() << std::endl;
  std::cout <<  bigint(1) << std::endl;
  std::cout << -bigint(1) << std::endl;
  std::cout <<  bigint("1234567890") << std::endl;
  std::cout <<  bigint("-1234567890") << std::endl;
    for (int e1 = -1; e1 <= 1; ++e1)
        for (int e2 = -1; e2 <= 1; ++e2)
        {
            std::cout << e1 << ", " << e2 << ": ";
            std::cout << (bigint(e1) < bigint(e2)) << " ";
            std::cout << (bigint(e1) <= bigint(e2)) << " ";
            std::cout << (bigint(e1) == bigint(e2)) << " ";
            std::cout << (bigint(e1) != bigint(e2)) << " ";
            std::cout << (bigint(e1) >= bigint(e2)) << " ";
            std::cout << (bigint(e1) >  bigint(e2)) << " ";
            std::cout << bigint(e1) + bigint(e2) << " ";
            std::cout << bigint(e1) - bigint(e2) << " ";
            std::cout << bigint(e2) - bigint(e1) << " ";
            std::cout << bigint(e1) * bigint(e2) << " ";
            std::cout << std::endl;
        }

    bigint x("1234567890"), y("9876543210");

    std::cout << x + y << " ";
    std::cout << x - y << " ";
    std::cout << y - x << " ";
    std::cout << x*y << std::endl;


    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
