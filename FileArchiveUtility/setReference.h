/* 
 * File:   setReference.h
 * Author: lee
 *
 * Created on 23 September 2015, 9:37 PM
 */

#ifndef _SETREFERENCE_H
#define	_SETREFERENCE_H

#include "ui_setReference.h"

class setReference : public QDialog {
    Q_OBJECT
public:
    setReference();
    virtual ~setReference();
private:
    Ui::setReference widget;
};

#endif	/* _SETREFERENCE_H */
