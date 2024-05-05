/*
 * Authors: Matyáš Oujezdský (xoujez04), Milan Vrbas (xvrbas01)
 * ICP 2024
 */
#pragma once

#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QObject>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QWidget>
#include <cmath>

class MenuIcon : public QObject, public QGraphicsRectItem {

    Q_OBJECT

  private:
    bool menuUp; /**< Flag indicating whether the menu is visible. */

  public:
    /**
     * @brief Constructor for creating a new MenuIcon object.
     * @param parent The parent of this object.
     */
    MenuIcon(QGraphicsScene *parent = nullptr);

    /**
     * @brief This method is called when the mouse is pressed on the menu icon.
     * It does nothing, but if it isn't implemented, the `mouseReleaseEvent`
     * method won't ever be called.
     */
    inline void mousePressEvent(QGraphicsSceneMouseEvent *) override {}

    /**
     * @brief This method is called when the mouse, which was pressed on the menu icon,
     * is released. It emits a signal (menuToggled) to toggle the menu.
     */
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *) override {
        emit menuToggled();
        menuUp = !menuUp;
        setOpacity(menuUp ? 1 : 0.5);
    }

    /**
     * @brief This method is called to paint the menu icon.
     * @param painter The painter to be used.
     * @param option The option to be used.
     * @param widget The widget on which the painting will be done. Omit for global painting.
     */
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

  signals:
    /**
     * @brief Signal emitted to toggle the menu.
     */
    void menuToggled();
};
