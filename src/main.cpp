#include <QGraphicsScene>
#include <QGraphicsView>
#include <QApplication>

#include "savedData.h"

QSize windowSize(1280, 920);

int main(int argc, char **argv) {

    QApplication app (argc, argv);

    MyScene scene;

    Data data(&scene);

    QGraphicsView view(&scene);
    view.setDragMode(QGraphicsView::RubberBandDrag);
    view.setMinimumSize(windowSize.width(), windowSize.height());
    view.setMaximumSize(windowSize.width(), windowSize.height());
    view.setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view.setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //view.showFullScreen();
    view.show();

    return app.exec();
}
