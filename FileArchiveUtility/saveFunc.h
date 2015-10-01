/* 
 * File:   saveFunc.h
 * Author: lee
 *
 * Created on 1 October 2015, 1:07 PM
 */

#ifndef _SAVEFUNC_H
#define	_SAVEFUNC_H

#include "ui_saveFunc.h"
#include <string>

class saveFunc : public QDialog {
    Q_OBJECT
public:
    saveFunc();
    virtual ~saveFunc();
    void setMessage(const char* mess);
private:
    Ui::saveFunc widget;
    const char* message;
};

#endif	/* _SAVEFUNC_H */
