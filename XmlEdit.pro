QT += widgets
QT += xml
requires(qtConfig(filedialog))

HEADERS       = mainwindow.h \
                xmledit.h \
                watchers.h
SOURCES       = main.cpp \
                mainwindow.cpp \
                xmledit.cpp
#! [0]
RESOURCES     = application.qrc
#! [0]

RC_ICONS = icons/windows.ico
ICON = icons/mac.icns

# install
target.path = $$[QT_INSTALL_EXAMPLES]/widgets/mainwindows/application
INSTALLS += target
