#pragma once

#include <QEvent>
#include <QGraphicsGridLayout>
#include <QGraphicsLinearLayout>
#include <QGraphicsProxyWidget>
#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsView>
#include <QGraphicsWidget>
#include <QMouseEvent>
#include <QObject>
#include <QPainter>
#include <QPointer>
#include <QPushButton>
#include <QStyleOptionGraphicsItem>

#include "guiMacros.h"
#include "qgraphicslayoutitem.h"
#include "robot.h"
#include "wall.h"

#define SAMPLE_WALL_SIZE 100

class SampleRobot;
class SampleWall;
class MyPushButton;

class Menu : public QGraphicsWidget, public QGraphicsRectItem {

    Q_OBJECT

  private:
    QPointer<MyPushButton> saveButton;
    QPointer<MyPushButton> loadButton;
    QPointer<MyPushButton> simulationButton;
    QPointer<SampleWall> sampleWall;
    QPointer<SampleRobot> sampleRobot;

  public:
    /**
     * @brief Constructor for creating a new menu.
     * @param menuWidth The width of the menu.
     * @param menuHeight The height of the menu.
     * @param parent The parent of this object.
     */
    Menu(int menuWidth, int menuHeight, QGraphicsScene *parent = nullptr);

    /**
     * @brief Returns the sample robot.
     * @return SampleRobot*
     */
    inline SampleRobot *getSampleRobot() const { return sampleRobot; }

    /**
     * @brief Returns the sample wall.
     * @return SampleWall*
     */
    inline SampleWall *getSampleWall() const { return sampleWall; }

    /**
     * @brief This method is called to paint the menu.
     * @param painter The painter to be used.
     * @param option The option to be used.
     * @param widget The widget that is painted on. Omit for global painting.
     */
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

  public slots:
    /**
     * @brief Toggles the visibility of the menu.
     */
    void toggle();

  signals:
    void savePressed();
    void loadPressed();
    void simulationPressed();
};

class SampleRobot : public Robot, public QGraphicsLayoutItem {

  public:
    /**
     * @brief Constructor for SampleRobot. Creates a new SampleRobot.
     * @param parent The parent of this object.
     */
    SampleRobot(Menu *parent) : Robot(0, 0, static_cast<QGraphicsRectItem *>(parent)) {
        MyItem::setFlag(QGraphicsItem::ItemIsMovable, false);
        setOwnedByLayout(false);
    }

    void contextMenuEvent(QGraphicsSceneContextMenuEvent *) override {}

    QSizeF sizeHint(Qt::SizeHint which, const QSizeF &constraint = QSizeF()) const override {
        switch (which) {
        case Qt::MinimumSize:
        case Qt::PreferredSize:
            return rect().size();
        case Qt::MaximumSize:
            return QSizeF(1000, 1000);
        default:
            break;
        }
        return constraint;
    }

    void setGeometry(const QRectF &geom) override {
        MyItem::prepareGeometryChange();
        QGraphicsLayoutItem::setGeometry(geom);
        MyItem::setPos(geom.topLeft());
    }
};

class SampleWall : public Wall, public QGraphicsLayoutItem {

  public:
    /**
     * @brief Constructor for SampleWall. Creates a new SampleWall.
     * @param parent The parent of this object.
     */
    SampleWall(Menu *parent) : Wall(0, 0, 100, 100, static_cast<QGraphicsRectItem *>(parent)) {
        MyItem::setFlag(QGraphicsItem::ItemIsMovable, false);
        setOwnedByLayout(false);
    }

    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override { MyItem::mouseMoveEvent(event); }

    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override { MyItem::hoverEnterEvent(event); }

    void hoverMoveEvent(QGraphicsSceneHoverEvent *event) override { MyItem::hoverMoveEvent(event); }

    QSizeF sizeHint(Qt::SizeHint which, const QSizeF &constraint = QSizeF()) const override {
        switch (which) {
        case Qt::MinimumSize:
        case Qt::PreferredSize:
            return rect().size();
        case Qt::MaximumSize:
            return QSizeF(1000, 1000);
        default:
            break;
        }
        return constraint;
    }

    void setGeometry(const QRectF &geom) override {
        MyItem::prepareGeometryChange();
        QGraphicsLayoutItem::setGeometry(geom);
        MyItem::setPos(geom.topLeft());
    }
};

class MyPushButton : public QPushButton, public QGraphicsLayoutItem {

    Q_OBJECT

  private:
    Menu *menu;

  public:
    /**
     * @brief Constructor for MyPushButton. Creates a new MyPushButton.
     * @param text The text to be displayed on the button.
     * @param menu The parent menu of this button.
     */
    MyPushButton(const QString &text, Menu *menu) : QPushButton(text), menu(menu) {}

    QSize sizeHint() const override { return QPushButton::sizeHint(); }

    QSizeF sizeHint(Qt::SizeHint which, const QSizeF &constraint = QSizeF()) const override {
        switch (which) {
        case Qt::MinimumSize:
        case Qt::PreferredSize:
            return QSizeF(menu->QGraphicsRectItem::rect().width() / 3,
                          menu->QGraphicsRectItem::rect().width() / 6);
        case Qt::MaximumSize:
            return QSizeF(1000, 1000);
        default:
            break;
        }
        return constraint;
    }

    void setGeometry(const QRectF &geom) override {
        QPushButton::setGeometry(geom.toRect());
        QGraphicsLayoutItem::setGeometry(geom);
        move(geom.x(), geom.y());
    }
};
