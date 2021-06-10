#include <QApplication>
#include "easy.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    easy app;

    app.setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
    app.setFixedSize(1400, 900);
    app.show();

    return a.exec();
}
