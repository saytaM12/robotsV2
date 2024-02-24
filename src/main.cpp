#include <QGraphicsView>
#include <QApplication>

#include "savedData.h"

int main(int argc, char **argv) {

    QApplication app (argc, argv);

    MyScene scene;

    Data data(&scene);

    MyView view(&scene);
    view.setDragMode(QGraphicsView::RubberBandDrag);
    view.setMinimumSize(scene.getSize().width(), scene.getSize().height());
    view.setMaximumSize(scene.getSize().width(), scene.getSize().height());
    view.setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view.setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    view.show();

    return app.exec();
}
