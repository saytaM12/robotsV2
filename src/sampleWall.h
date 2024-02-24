#ifndef SAMPLEWALL
#define SAMPLEWALL

#include "wall.h"

#include <QGraphicsSceneMouseEvent>
#include <QGraphicsView>
#include <QMouseEvent>
#include <QEvent>

class SampleWall : public Wall {

    Q_OBJECT

    public:
        SampleWall(QRectF r, int s, QGraphicsRectItem *parent = nullptr);

        SampleWall(SampleWall *wall, QGraphicsRectItem *parent = nullptr);

        //void mousePressEvent(QGraphicsSceneMouseEvent *event);

        //void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
};

#endif // SAMPLEWALL
