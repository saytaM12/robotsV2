#include <QApplication>
#include <QGraphicsView>

#include "savedData.h"

int main(int argc, char **argv) {

  QApplication app(argc, argv);

  MyScene scene(QSize(1440, 900));

  Data data(&scene);

  MyView view(&scene);
  view.show();

  return app.exec();
}

/* TODO
 * 0. code review
 * 1. wall resize correctly
 * 2. robot change angle
 * 3. robot change automove parameters (from requirements) (on right click idk)
 * 4. collisions (+ if dropped in wrong place, move it)
 * 5. scene sizing (with args during startup)
 * 6. robot moving
 * 7. player controls
 */
