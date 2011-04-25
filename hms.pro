HEADERS       = mainwindow.h \
                keyboard.h \
                hidapi.h
SOURCES       = mainwindow.cpp \
                main.cpp \
                keyboard.cpp \
                hid-libusb.c

DESTDIR = bin/
LIBS += -L./BIN

LIBS += -L/usr/local/lib -lusb-1.0
INCLUDEPATH += $$quote(/usr/include/libusb-1.0)

# install
target.path = $$[QT_INSTALL_EXAMPLES]/mainwindows/menus
sources.files = $$SOURCES $$HEADERS $$RESOURCES $$FORMS menus.pro
sources.path = $$[QT_INSTALL_EXAMPLES]/mainwindows/menus
INSTALLS += target sources

symbian {
    TARGET.UID3 = 0xA000CF66
    include($$PWD/../../symbianpkgrules.pri)
}
maemo5: include($$PWD/../../maemo5pkgrules.pri)

simulator: warning(This example might not fully work on Simulator platform)
