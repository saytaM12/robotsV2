#include "darkenImage.h"
#include <QDebug>

void darkenImage(QImage &image) {
    for (int y = 0; y < image.height(); y++) {
        for (int x = 0; x < image.width(); x++) {
            QColor color = image.pixel(x, y);

            if (color.red() == 0 || color.green() == 0 || color.blue() == 0) {
                continue;
            }

            color = color.darker(200);
            image.setPixel(x, y, color.rgba());
        }
    }
}
