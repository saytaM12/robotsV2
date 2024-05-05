/*
 * Authors: Matyáš Oujezdský (xoujez04), Milan Vrbas (xvrbas01)
 * ICP 2024
 */
#include <QApplication>
#include <QGraphicsView>

#include "savedData.h"

int main(int argc, char **argv) {

    QApplication app(argc, argv);
    app.setApplicationName("Robot and Walls, What more could you want?");

    MyScene scene(QSize(1440, 900));

    Data data(&scene);

    MyView view(&scene);
    view.show();

    return app.exec();
}
