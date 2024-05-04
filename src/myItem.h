#pragma once

#include <QAbstractGraphicsShapeItem>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QWidget>

class MyItem : public QObject, public QAbstractGraphicsShapeItem {

    Q_OBJECT

  private:
    bool selectedFromHover; /**< Flag indicating whether the item was selected from hover. */

  public:
    /**
     * @brief Constructor for creating a new item.
     * @param x The x position of the item.
     * @param y The y position of the item.
     * @param parent The parent of this object.
     */
    MyItem(qreal x, qreal y, QGraphicsItem *parent = nullptr);

    /**
     * @brief Pure virtual method to be implemented by subclasses to determine if the item is a wall.
     * @return bool True if the item is a wall, otherwise false.
     */
    virtual inline bool isWall() const = 0;

    /**
     * @brief Called when the mouse enters the item.
     * If the item wasn't selected, it will become selected and the fact that it
     * was selected from mouse hover will be stored. This is so that the item
     * cannot be unselected by hoverLeaveEvent if it was selected by group
     * selection.
     */
    inline void hoverEnterEvent(QGraphicsSceneHoverEvent *) override {
        if (!isSelected()) {
            setSelected(true);
            selectedFromHover = true;
        }
    }

    /**
     * @brief Called when the mouse leaves the item.
     * If the item was selected from hover, it will be unselected.
     */
    inline void hoverLeaveEvent(QGraphicsSceneHoverEvent *) override {
        if (selectedFromHover) {
            setSelected(false);
            selectedFromHover = false;
        }
    }

    /**
     * @brief Called when the user presses the mouse button.
     * Changes the cursor, and puts the item on top of all other items (for
     * painting purposes).
     * @param event The event that triggered this.
     */
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

    /**
     * @brief Called when the user releases the mouse button.
     * Changes the cursor and puts the item back the bottom layer (for painting
     * purposes). This method also emits the mouseReleased signal.
     * @param event The event that triggered this.
     */
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

    /**
     * @brief Called when the item is changed in any way.
     * Here it is used to check if the item is being moved out of the scene.
     * If so, it will be stopped from going further.
     * @param change The type of change.
     * @param value The value of the change.
     * @return QVariant
     */
    QVariant itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value) override;

  signals:
    /**
     * @brief Signal emitted when the mouse is released on the item.
     * @param item The item where the mouse was released.
     */
    void mouseReleased(MyItem *item);
};
