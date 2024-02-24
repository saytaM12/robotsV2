#ifndef MYSCENE
#define MYSCENE

#include <QGraphicsScene>
#include <QGraphicsView>

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

        QSize getSize();

        Menu *getMenu();

        MenuIcon *getMenuIcon();

        QList<Robot *> getPlayers();

        QList<Robot *> getRobots();

        QList<Wall *> getWalls();

        void addRobot(Robot *robot);

        void addWall(Wall *wall);

        void clear();
};

class MyView : public QGraphicsView {

    Q_OBJECT

    private:
        MyScene *scene;
        bool alreadyClicked;

    public:
        MyView(MyScene *scene = nullptr);

    public slots:
        void mousePressEvent(QMouseEvent *e) override;
};

#endif // MYSCENE
