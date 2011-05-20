TEMPLATE = lib
CONFIG   += static create_prl
QT       -= gui
QT       += network
TARGET   = gtasks
DESTDIR  = $$OUT_PWD/../lib

VERSION = 0.1

CONFIG(static) {
	DEFINES += GTASKS_STATIC_LIB
} else {
	DEFINES += MAKE_GTASKS_LIB
}

DEFINES += SIMPLEOAUTH_STATIC_LIB

HEADERS += \
    gtasks_export.h \
    cache.h \
    jobs.h \
    service.h \
    task_p.h \
    task.h \
    model.h

SOURCES += \
    jobs.cpp \
    service.cpp \
    task.cpp
