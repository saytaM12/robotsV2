######################################################################
# Automatically generated by qmake (3.1) Tue Mar 5 12:20:55 2024
######################################################################

TEMPLATE = app
TARGET = robotsV2
INCLUDEPATH += .

QT += widgets
QT += core
QT += gui

# You can make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# Please consult the documentation of the deprecated API in order to know
# how to port your code away from it.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# Input
HEADERS += src/json.hpp \
           src/menu.h \
           src/menuIcon.h \
           src/myItem.h \
           src/myScene.h \
           src/robot.h \
           src/savedData.h \
           src/wall.h
SOURCES += src/main.cpp \
           src/menu.cpp \
           src/menuIcon.cpp \
           src/myItem.cpp \
           src/myScene.cpp \
           src/robot.cpp \
           src/savedData.cpp \
           src/wall.cpp
