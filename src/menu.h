/*
 * Authors: Matyáš Oujezdský (xoujez04), Milan Vrbas (xvrbas01)
 * ICP 2024
 */
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

/**
 * @brief The Menu class is a QGraphicsWidget that is used to create a menu for the simulation.
 *
 * It inherits from QGraphicsWidget and QGraphicsRectItem.
 */
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
     * @brief Returns a pointer to the sample robot.
     * @return SampleRobot*
     */
    inline SampleRobot *getSampleRobot() const { return sampleRobot; }

    /**
     * @brief Returns a pointer to the sample wall.
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
    /**
     * @brief Signal emitted when the save button is pressed.
     */
    void savePressed();
    /**
     * @brief Signal emitted when the load button is pressed.
     */
    void loadPressed();
    /**
     * @brief Signal emitted when the simulation button is pressed.
     */
    void simulationPressed();
};

/**
 * @brief A specific robot that is displayed in the menu
 *
 * It inherits from Robot and QGraphicsLayoutItem.
 */
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

    /**
     * @brief This method is called when the context menu is requested.
     */
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *) override {}

    /**
     * @brief Method used to return the size hint of the SampleRobot.
     * @param which The size hint type.
     * @param constraint Maximum size limit.
     */
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

    /**
     * @brief Method tu update the rect of SampleRobot.
     * @param geom The new rect.
     */
    void setGeometry(const QRectF &geom) override {
        MyItem::prepareGeometryChange();
        QGraphicsLayoutItem::setGeometry(geom);
        MyItem::setPos(geom.topLeft());
    }
};

/**
 * @brief A specific wall that is displayed in the menu
 *
 * It inherits from Wall and QGraphicsLayoutItem.
 */
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

    /**
     * @brief Method used to handle mouse drag events.
     * It removes the Walls ability to be moved.
     *
     * @param event The mouse event.
     */
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override { MyItem::mouseMoveEvent(event); }

    /**
     * @brief Method used to handle mouse entering the Wall.
     * It removes the Walls ability to be resized.
     *
     * @param event The mouse event.
     */
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override { MyItem::hoverEnterEvent(event); }

    /**
     * @brief Method used to handle mouse moving inside the Wall.
     * It removes the Walls ability to be resized.
     *
     * @param event The mouse event.
     */
    void hoverMoveEvent(QGraphicsSceneHoverEvent *event) override { MyItem::hoverMoveEvent(event); }

    /**
     * @brief Method used to get the size hint of the SampleWall.
     *
     * @param which The size hint type.
     * @param constraint Maximum size limit.
     * @return QSizeF The size hint of the SampleWall.
     */
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

    /**
     * @brief Method tu update the rect of SampleWall.
     * @param geom The new rect.
     */
    void setGeometry(const QRectF &geom) override {
        MyItem::prepareGeometryChange();
        QGraphicsLayoutItem::setGeometry(geom);
        MyItem::setPos(geom.topLeft());
    }
};

/**
 * @brief A custom implementation of QPushButton that can be used in a QGraphicsLayout.
 *
 * It inherits from QPushButton and QGraphicsLayoutItem.
 */
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

    /**
     * @brief This method is called to get the size hint of the button.
     * It calls the size hint of the QPushButton.
     *
     * @return QSize The size hint of the button.
     */
    QSize sizeHint() const override { return QPushButton::sizeHint(); }

    /**
     * @brief This method is called to get the size hint of the button.
     *
     * @param which The size hint type.
     * @param constraint Maximum size limit.
     */
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

    /**
     * @brief This method is called to set a new rect for the button.
     *
     * @param geom The new rect.
     */
    void setGeometry(const QRectF &geom) override {
        QPushButton::setGeometry(geom.toRect());
        QGraphicsLayoutItem::setGeometry(geom);
        move(geom.x(), geom.y());
    }
};
