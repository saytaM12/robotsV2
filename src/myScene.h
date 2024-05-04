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
    bool simulating; /**< Flag indicating whether simulation is active. */
    QPointer<Menu> menu; /**< Pointer to the menu object. */
    QPointer<MenuIcon> menuIcon; /**< Pointer to the menu icon object. */
    QPointer<QTimer> gameTickTimer; /**< Pointer to the timer used for game ticks. */
    QList<QPointer<MyItem>> itemList; /**< List of items in the scene. */
    QPointer<Robot> player1; /**< Pointer to player 1 robot object. */
    QPointer<Robot> player2; /**< Pointer to player 2 robot object. */

  public:
    /**
     * @brief Constructor for MyScene object.
     * @param size Size of the scene.
     * @param parent Parent QGraphicsScene object.
     */
    MyScene(QSize size, QGraphicsScene *parent = nullptr);

    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
        if (items().size() > 0) {
        }
        QGraphicsScene::mouseMoveEvent(event);
    }

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
     * @brief Get the menu object.
     * @return Menu* Pointer to the menu object.
     */
    inline Menu *getMenu() const { return menu; }

    /**
     * @brief Get the menu icon object.
     * @return MenuIcon* Pointer to the menu icon object.
     */
    inline MenuIcon *getMenuIcon() const { return menuIcon; }

    /**
     * @brief Get a list of items in the scene.
     * @return QList<MyItem *> List of items in the scene.
     */
    QList<MyItem *> items() const;

    /**
     * @brief Get player 1 robot object.
     * @return Robot* Pointer to player 1 robot object.
     */
    Robot *getPlayer1() const { return player1; }

    /**
     * @brief Get player 2 robot object.
     * @return Robot* Pointer to player 2 robot object.
     */
    Robot *getPlayer2() const { return player2; }

    /**
     * @brief Add an item to the scene and the items list.
     * @param item Item to be added.
     */
    void addItem(MyItem *item);

    /**
     * @brief Remove all items from the scene (excluding menu and menu icon).
     *        Also clears the items list.
     */
    void clear();

  public slots:
    /**
     * @brief Slot called when an item is dropped on the scene.
     *        Used to check whether to remove an item because it was dropped on the menu.
     * @param item Item that was dropped.
     */
    void itemDropped(MyItem *item);

    /**
     * @brief Slot called when the simulation button is pressed.
     */
    void simulationPressed();

    /**
     * @brief Ensure there is only one player of a certain type.
     * @param robot Pointer to the robot.
     * @param player Player type.
     */
    void ensureOnePlayer(Robot *robot, int player);
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
     *        Used to create a new item when the sample robot or the sample wall is clicked.
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
