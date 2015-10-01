/*
 * File:   main.cpp
 * Author: lec725
 *
 * Created on 14 September 2015, 2:29 PM
 */

#include <QApplication>
#include "VersionUI.h"

int main(int argc, char *argv[]) {
    // initialize resources, if needed
    // Q_INIT_RESOURCE(resfile);

    QApplication app(argc, argv);

    //In the voice of Bruce Buffer, "IT'S TIME!"
    //this will initiate VersionUI which starts the UI and the program
    VersionUI mainScr;
    mainScr.show();

    return app.exec();
}
