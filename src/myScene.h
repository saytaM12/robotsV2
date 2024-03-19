#pragma once

#include <QDebug>

#include <QGraphicsScene>
#include <QGraphicsView>

#include "menu.h"
#include "menuIcon.h"

class MyScene : public QGraphicsScene {

    Q_OBJECT

  private:
    QPointer<Menu> menu;
    QPointer<MenuIcon> menuIcon;
    QList<QPointer<MyItem>> itemList;

  public:
    /* This constructor is used to create a new MyScene object.
     * @param QGraphicsScene *parent: The parent of this object.
     */
    MyScene(QSize size, QGraphicsScene *parent = nullptr);

    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
        qDebug() << "mouse: " << event->scenePos();
        if (items().size() > 0) {
            qDebug() << "item: x: " << items()[0]->x() << ", y: " << items()[0]->y()
                     << ", width: " << items()[0]->boundingRect().width()
                     << ", height: " << items()[0]->boundingRect().height();
        }
        QGraphicsScene::mouseMoveEvent(event);
    }

    /* This method is used to get the width of the scene.
     * @return: qreal
     */
    inline qreal getWidth() { return this->width(); }

    /* This method is used to get the height of the scene.
     * @return: qreal
     */
    inline qreal getHeight() { return this->height(); }

    /* This method returns the menu.
     * @return: Menu*
     */
    inline Menu *getMenu() { return this->menu; }

    /* This method returns the menu icon.
     * @return: MenuIcon*
     */
    inline MenuIcon *getMenuIcon() { return this->menuIcon; }

    /* This method returns the items in the scene. (excluding the menu and the
     * menu icon)
     * @return: QList<MyItem *>
     */
    inline QList<MyItem *> items() {
        QList<MyItem *> returnItems;
        for (MyItem *item : this->itemList) {
            returnItems.push_back(item);
        }
        return returnItems;
    }

    /* This methos adds an item to the scene and to the items list.
     * @param MyItem *item: The item to be added.
     * @return: void
     */
    void addItem(MyItem *item);

    /* This methos removes all items from the scene. (excluding the menu and the
     * menu icon). It also clears the items list.
     * @return: void
     */
    void clear();

  public slots:
    /* This slot is called when an item is dropped on the scene.
     * It is used to check whether to remove an item, because it was dropped on
     * the menu.
     * @param MyItem *item: The item that was dropped.
     * @return: void
     */
    void itemDropped(MyItem *item);
};

class MyView : public QGraphicsView {

  private:
    MyScene *scene;

  public:
    /* This constructor is used to create a new MyView object.
     * @param MyScene *scene: The scene to be displayed.
     */
    MyView(MyScene *scene = nullptr);

    /* This method is called when the mouse is pressed.
     * It is used to create a new item when the sample robot or the sample wall is
     * clicked.
     * @param QMouseEvent *e: The mouse event.
     * @return: void
     */
    void mousePressEvent(QMouseEvent *e);
};
