#include <QGraphicsScene>
#include <QGraphicsView>
#include <QApplication>

#include "savedData.h"
#include "menuIcon.h"
#include "menu.h"

QSize windowSize(1280, 920);

int main(int argc, char **argv) {

    QApplication app (argc, argv);

    QGraphicsScene scene;
    scene.setSceneRect(0, 0, windowSize.width() - 10, windowSize.height() - 10);
    if (loadData(&scene) != 0) {
        return -1;
    }

    Menu *menu = new Menu;
    scene.addItem(menu);

    MenuIcon *menuIcon = new MenuIcon;
    scene.addItem(menuIcon);

    QObject::connect(menuIcon, &MenuIcon::menuToggled, menu, &Menu::toggle);

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
