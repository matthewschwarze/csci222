# This file is generated automatically. Do not edit.
# Use project properties -> Build -> Qt -> Expert -> Custom Definitions.
TEMPLATE = app
DESTDIR = dist/Debug/GNU-Linux-x86
TARGET = FileArchiveUtility
VERSION = 1.0.0
CONFIG -= debug_and_release app_bundle lib_bundle
CONFIG += debug 
PKGCONFIG +=
QT = core gui widgets
SOURCES += FileHash.cpp FileRec.cpp VersionRec.cpp VersionUI.cpp archiveTableView.cpp commentDialog.cpp fileArchiver.cpp getCommentForm.cpp main.cpp retrieveVersion.cpp setReference.cpp
HEADERS += FileHash.h FileRec.h VersionRec.h VersionUI.h archiveTableView.h commentDialog.h fileArchiver.h getCommentForm.h retrieveVersion.h setReference.h
FORMS += VersionUI.ui commentDialog.ui getCommentForm.ui retrieveVersion.ui setReference.ui
RESOURCES +=
TRANSLATIONS +=
OBJECTS_DIR = build/Debug/GNU-Linux-x86
MOC_DIR = 
RCC_DIR = 
UI_DIR = 
QMAKE_CC = gcc
QMAKE_CXX = g++
DEFINES += 
INCLUDEPATH += /lib/x86_64-linux-gnu/mongo-client-install/include /usr/include/qt4 
LIBS += /lib/x86_64-linux-gnu/mongo-client-install/lib/libmongoclient.a -lboost_thread -lboost_filesystem -lboost_system -lboost_program_options -lboost_regex -lpthread -lQtCore -lQtGui  
