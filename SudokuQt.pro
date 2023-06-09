greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

OBJECTS_DIR = obj
MOC_DIR     = moc
DESTDIR     = bin

SOURCES += \
    src/board.cpp \
    src/button.cpp \
    src/fontmanager.cpp \
    src/gamescene.cpp \
    src/main.cpp \
    src/pixmapmanager.cpp \
    src/square.cpp \
    src/sudoku.cpp \
    src/view.cpp

HEADERS += \
    src/board.h \
    src/button.h \
    src/fontmanager.h \
    src/gamescene.h \
    src/pixmapmanager.h \
    src/resource_holder.h \
    src/square.h \
    src/sudoku.h \
    src/utils.h \
    src/view.h

RESOURCES += \
    resource.qrc
