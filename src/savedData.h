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
        json data;

    public: 
        Data(MyScene *scene);

        int saveData();

        int loadData();

    public slots:
        void saveDataSlot();

        void loadDataSlot();
};
