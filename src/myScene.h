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
  QPointer<Menu> menu;
  QPointer<MenuIcon> menuIcon;
  QList<QPointer<MyItem>> items;

public:
  /*
   * This constructor is used to create a new MyScene object.
   * @param QGraphicsScene *parent: The parent of this object.
   */
  MyScene(QGraphicsScene *parent = nullptr);

  /*
   * This method is used to get the size of the scene.
   * @return: QSize
   */
  QSize getSize();

  /*
   * This method returns the menu.
   * @return: Menu*
   */
  Menu *getMenu();

  /*
   * This method returns the menu icon.
   * @return: MenuIcon*
   */
  MenuIcon *getMenuIcon();

  /*
   * This method returns the items in the scene. (excluding the menu and the
   * menu icon)
   * @return: QList<QPointer<MyItem>>
   */
  QList<QPointer<MyItem>> getItems();

  /*
   * This methos adds an item to the scene and to the items list.
   * @param MyItem *item: The item to be added.
   * @return: void
   */
  void addItem(MyItem *item);

  /*
   * This methos removes all items from the scene. (excluding the menu and the
   * menu icon). It also clears the items list.
   * @return: void
   */
  void clear();

public slots:
  /*
   * This slot is called when an item is dropped on the scene.
   * It is used to check whether to remove an item, because it was dropped on
   * the menu.
   * @param MyItem *item: The item that was dropped.
   * @return: void
   */
  void itemDropped(MyItem *item);
};

class MyView : public QGraphicsView {

  Q_OBJECT

private:
  MyScene *scene;

public:
  /*
   * This constructor is used to create a new MyView object.
   * @param MyScene *scene: The scene to be displayed.
   */
  MyView(MyScene *scene = nullptr);

public slots:
  /*
   * This slot is called when the mouse is pressed on the view.
   * If the click was on a sample item a new item will be created and added to
   * the scene.
   * @param QMouseEvent *e: The event that was triggered.
   * @return: void
   */
  void mousePressEvent(QMouseEvent *e) override;
};

#endif // MYSCENE
