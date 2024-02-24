#ifndef SAVEDDATA
#define SAVEDDATA

#include <QFileDialog>
#include <QObject>
#include <iostream>
#include <fstream>

#include "json.hpp"

#include "myScene.h"
#include "wall.h"
#include "robot.h"

using json = nlohmann::json;

class Data : public QObject {

    Q_OBJECT

    private:
        MyScene *scene;

    public: 
        Data(MyScene *scene);

    public slots:
        int saveData();

        int loadData();
};

#endif // SAVEDDATA
