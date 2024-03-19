#include <QApplication>
#include <QGraphicsView>

#include "savedData.h"

int main(int argc, char **argv) {

    QApplication app(argc, argv);

    MyScene scene(QSize(1440, 900));

    Data data(&scene);

    MyView view(&scene);
    view.show();

    return app.exec();
}
