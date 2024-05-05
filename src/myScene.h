/*
 * Authors: Matyáš Oujezdský (xoujez04), Milan Vrbas (xvrbas01)
 * ICP 2024
 */
#pragma once

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTimer>

#include "menu.h"
#include "menuIcon.h"
#include "qevent.h"

class MyScene : public QGraphicsScene {

    Q_OBJECT

  private:
    bool simulating;                  /**< Flag indicating whether simulation is active. */
    QPointer<Menu> menu;              /**< Pointer to the menu object. */
    QPointer<MenuIcon> menuIcon;      /**< Pointer to the menu icon object. */
    QPointer<QTimer> gameTickTimer;   /**< Pointer to the timer used for game ticks. */
    QList<QPointer<MyItem>> itemList; /**< List of pointers to items in the scene. */
    QPointer<Robot> player1;          /**< Pointer to player 1 robot object. */
    QPointer<Robot> player2;          /**< Pointer to player 2 robot object. */

  public:
    /**
     * @brief Constructor for MyScene object.
     * @param size Size of the scene.
     * @param parent Parent QGraphicsScene object.
     */
    MyScene(QSize size, QGraphicsScene *parent = nullptr);

    /**
     * @brief Get the width of the scene.
     * @return qreal Width of the scene.
     */
    inline qreal getWidth() const { return width(); }

    /**
     * @brief Get the height of the scene.
     * @return qreal Height of the scene.
     */
    inline qreal getHeight() const { return height(); }

    /**
     * @brief Get a pointer to the menu object.
     * @return Menu* Pointer to the menu object.
     */
    inline Menu *getMenu() const { return menu; }

    /**
     * @brief Get a pointer to the menu icon object.
     * @return MenuIcon* Pointer to the menu icon object.
     */
    inline MenuIcon *getMenuIcon() const { return menuIcon; }

    /**
     * @brief Get a list of pointers to the wall and robot objects in the scene.
     * @return QList<MyItem *> List of items in the scene.
     */
    QList<MyItem *> items() const;

    /**
     * @brief Get a pointer to the player 1 robot object.
     * @return Robot* Pointer to player 1 robot object.
     */
    Robot *getPlayer1() const { return player1; }

    /**
     * @brief Get a pointer to the player 2 robot object.
     * @return Robot* Pointer to player 2 robot object.
     */
    Robot *getPlayer2() const { return player2; }

    /**
     * @brief Add an item to the scene and the items list.
     * @param item Item to be added.
     */
    void addItem(MyItem *item);

    /**
     * @brief Remove all walls and robots from the scene
     *        Also clears the items list.
     */
    void clear();

  public slots:
    /**
     * @brief Slot called when an item is dropped on the scene.
     *        Used to check whether to remove an item because it was dropped on the menu.
     */
    void itemDropped();

    /**
     * @brief Slot called when the simulation button is pressed.
     */
    void simulationPressed();

    /**
     * @brief Slot called for robots to check if they detect an obstacle in front.
     */
    bool detectObjects();

    /**
     * @brief Ensure there is only one player of a certain type.
     * @param player Player type.
     */
    void ensureOnePlayer(int player);
  signals:
    /**
     * @brief Signal emitted on each game tick.
     */
    void gameTick();
};

class MyView : public QGraphicsView {

  private:
    MyScene *scene; /**< Pointer to the scene displayed in the view. */

  public:
    /**
     * @brief Constructor for MyView object.
     * @param scene Pointer to the scene to be displayed.
     */
    MyView(MyScene *scene = nullptr);

    /**
     * @brief Method called when the mouse is pressed.
     *        Used to create a new item if the sample robot or the sample wall is clicked.
     * @param e Mouse event.
     */
    void mousePressEvent(QMouseEvent *e);

    /**
     * @brief Method called when a key is pressed.
     * @param e Key event.
     */
    void keyPressEvent(QKeyEvent *e);

    /**
     * @brief Method called when a key is released.
     * @param e Key event.
     */
    void keyReleaseEvent(QKeyEvent *e);
};
