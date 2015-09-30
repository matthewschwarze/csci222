/* 
 * File:   retrieveVersion.h
 * Author: lee
 *
 * Created on 23 September 2015, 9:32 PM
 */

#ifndef _RETRIEVEVERSION_H
#define	_RETRIEVEVERSION_H

#include "ui_retrieveVersion.h"
#include <iostream>
#include <QFileDialog>

class retrieveVersion : public QDialog {
    Q_OBJECT
public:
    retrieveVersion();
    virtual ~retrieveVersion();
public slots:
    void openFile(); 
    void pressOK();
private:
    Ui::retrieveVersion widget;
    const char* strName;
};

#endif	/* _RETRIEVEVERSION_H */
