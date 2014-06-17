!isEmpty(FRAMEWORK_PRI):error("framework.pri already included")
FRAMEWORK_PRI = 1

BIN_PATH        = $$PWD/bin
SRC_PATH        = $$PWD
COMPONENT_PATH  = $$BIN_PATH/components

LIBS        *= -L$$BIN_PATH

INCLUDEPATH += $$SRC_PATH $$SRC_PATH/components $$SRC_PATH/libs
