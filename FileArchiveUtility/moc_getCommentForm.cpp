/****************************************************************************
** Meta object code from reading C++ file 'getCommentForm.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "getCommentForm.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'getCommentForm.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_getCommentForm[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      16,   15,   15,   15, 0x0a,
      38,   15,   26,   15, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_getCommentForm[] = {
    "getCommentForm\0\0pressOK()\0std::string\0"
    "get()\0"
};

void getCommentForm::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        getCommentForm *_t = static_cast<getCommentForm *>(_o);
        switch (_id) {
        case 0: _t->pressOK(); break;
        case 1: { std::string _r = _t->get();
            if (_a[0]) *reinterpret_cast< std::string*>(_a[0]) = _r; }  break;
        default: ;
        }
    }
}

const QMetaObjectExtraData getCommentForm::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject getCommentForm::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_getCommentForm,
      qt_meta_data_getCommentForm, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &getCommentForm::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *getCommentForm::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *getCommentForm::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_getCommentForm))
        return static_cast<void*>(const_cast< getCommentForm*>(this));
    return QDialog::qt_metacast(_clname);
}

int getCommentForm::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
