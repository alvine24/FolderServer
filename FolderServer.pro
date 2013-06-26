#The file .pro to build and run the project must contain at least :

QT       += core gui network xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FolderServer
TEMPLATE = app


SOURCES += FolderServer.cpp \
    main.cpp \
    ../../../../Desktop/Cairnsmith13/CairnSmith/CairnSmith/Server/ClientLib/sheer_cloud.cpp \
    Dialog.cpp

HEADERS  += FolderServer.h \
    ../../../../Desktop/Cairnsmith13/CairnSmith/CairnSmith/Server/ClientLib/sheer_cloud.h \
    Dialog.h \
    LocalData.h

INCLUDEPATH += C:/Users/sheerServer/Projets/Qt/FileHash
LIBS+=  -LC:/Users/sheerServer/Projets/Qt/FileHash-build-Desktop_Qt_5_0_1_MSVC2010_32bit-Debug/debug -lFileHash

#INCLUDEPATH += C:/Users/sheerServer/Desktop/Cairnsmith13/CairnSmith/CairnSmith/Server/ClientLib

FORMS += \
    Dialog.ui
