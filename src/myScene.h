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
        QList<Robot *> players;
        QList<Robot *> robots;
        QList<Wall *> walls;

    public:
        MyScene(QGraphicsScene *parent = nullptr);

        Menu *getMenu();

        MenuIcon *getMenuIcon();

        QList<Robot *> getPlayers();

        QList<Robot *> getRobots();

        QList<Wall *> getWalls();

        void newItem(Wall *wall);

        void newItem(Robot *robot);

        void clear();
};
