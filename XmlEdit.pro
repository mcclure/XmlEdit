QT += widgets
requires(qtConfig(filedialog))

HEADERS       = mainwindow.h \
                xmledit.h
SOURCES       = main.cpp \
                mainwindow.cpp \
                xmledit.cpp
#! [0]
RESOURCES     = application.qrc
#! [0]

# install
target.path = $$[QT_INSTALL_EXAMPLES]/widgets/mainwindows/application
INSTALLS += target
