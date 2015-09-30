/****************************************************************************
** Meta object code from reading C++ file 'VersionUI.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "VersionUI.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'VersionUI.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_VersionUI[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      11,   10,   10,   10, 0x0a,
      27,   22,   10,   10, 0x0a,
      60,   10,   10,   10, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_VersionUI[] = {
    "VersionUI\0\0openFile()\0vers\0"
    "createTable(vector<VersionRec>*)\0"
    "saveFile()\0"
};

void VersionUI::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        VersionUI *_t = static_cast<VersionUI *>(_o);
        switch (_id) {
        case 0: _t->openFile(); break;
        case 1: _t->createTable((*reinterpret_cast< vector<VersionRec>*(*)>(_a[1]))); break;
        case 2: _t->saveFile(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData VersionUI::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject VersionUI::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_VersionUI,
      qt_meta_data_VersionUI, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &VersionUI::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *VersionUI::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *VersionUI::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_VersionUI))
        return static_cast<void*>(const_cast< VersionUI*>(this));
    return QDialog::qt_metacast(_clname);
}

int VersionUI::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
