#include <QApplication>
#include <QIcon>
#include "view.h"

int main(int argc, char** argv)
{
    QApplication a(argc, argv);
    View v;
    v.setWindowTitle("Sudoku Qt/C++");
    v.setWindowIcon(QIcon(":/res/img/icon.png"));
    v.show();
    a.exec();
}
