#include <QGraphicsScene>
#include <QGraphicsView>
#include <QApplication>

#include "menu.h"
#include "menuIcon.h"

class MyScene : public QGraphicsScene {

    Q_OBJECT

    private:
        QSize size;
        Menu *menu;
        MenuIcon *menuIcon;
        QList<QGraphicsItem *> items;

    public:
        MyScene(QGraphicsScene *parent = nullptr);

        Menu *getMenu();

        MenuIcon *getMenuIcon();

        void newItem(QGraphicsItem *item);

        void clear();
};
