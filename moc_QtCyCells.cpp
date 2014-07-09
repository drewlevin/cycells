/****************************************************************************
** Meta object code from reading C++ file 'QtCyCells.h'
**
** Created: Tue Apr 24 13:13:50 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "QtCyCells.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QtCyCells.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QtCyCells[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
      24,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      10,       // signalCount

 // signals: signature, parameters, type, tag, flags
      22,   11,   10,   10, 0x05,
      39,   11,   10,   10, 0x05,
      62,   57,   10,   10, 0x05,
      79,   75,   10,   10, 0x05,
      98,   91,   10,   10, 0x05,
     122,  113,   10,   10, 0x05,
     152,  138,   10,   10, 0x05,
     178,   11,   10,   10, 0x05,
     200,   11,   10,   10, 0x05,
     221,   10,   10,   10, 0x05,

 // slots: signature, parameters, type, tag, flags
     233,   10,   10,   10, 0x0a,
     245,   10,   10,   10, 0x0a,
     258,   10,   10,   10, 0x0a,
     266,   10,   10,   10, 0x0a,
     278,   10,   10,   10, 0x0a,
     289,   10,   10,   10, 0x0a,
     303,   10,   10,   10, 0x0a,
     315,   10,   10,   10, 0x0a,
     327,   10,   10,   10, 0x0a,
     344,   10,   10,   10, 0x0a,
     371,  360,   10,   10, 0x0a,
     401,  392,   10,   10, 0x0a,
     430,  425,   10,   10, 0x0a,
     457,  450,   10,   10, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_QtCyCells[] = {
    "QtCyCells\0\0qsFileName\0loadDef(QString)\0"
    "loadInit(QString)\0seed\0setSeed(int)\0"
    "dur\0setDur(int)\0update\0setUpdate(int)\0"
    "timestep\0setStep(double)\0qsView,widget\0"
    "setView(QString,QWidget*)\0"
    "writeHistory(QString)\0writeDetail(QString)\0"
    "toggleRun()\0onLoadDef()\0onLoadInit()\0"
    "onRun()\0onSetSeed()\0onSetDur()\0"
    "onSetUpdate()\0onSetStep()\0onSetView()\0"
    "onWriteHistory()\0onWriteDetail()\0"
    "cells,mols\0updateTypes(int,int)\0"
    "geometry\0updateGeometry(QString)\0time\0"
    "updateTime(QString)\0status\0"
    "updateStatus(QString)\0"
};

const QMetaObject QtCyCells::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_QtCyCells,
      qt_meta_data_QtCyCells, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QtCyCells::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QtCyCells::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QtCyCells::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QtCyCells))
        return static_cast<void*>(const_cast< QtCyCells*>(this));
    return QDialog::qt_metacast(_clname);
}

int QtCyCells::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: loadDef((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: loadInit((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: setSeed((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: setDur((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: setUpdate((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: setStep((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 6: setView((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QWidget*(*)>(_a[2]))); break;
        case 7: writeHistory((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 8: writeDetail((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 9: toggleRun(); break;
        case 10: onLoadDef(); break;
        case 11: onLoadInit(); break;
        case 12: onRun(); break;
        case 13: onSetSeed(); break;
        case 14: onSetDur(); break;
        case 15: onSetUpdate(); break;
        case 16: onSetStep(); break;
        case 17: onSetView(); break;
        case 18: onWriteHistory(); break;
        case 19: onWriteDetail(); break;
        case 20: updateTypes((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 21: updateGeometry((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 22: updateTime((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 23: updateStatus((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 24;
    }
    return _id;
}

// SIGNAL 0
void QtCyCells::loadDef(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void QtCyCells::loadInit(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void QtCyCells::setSeed(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void QtCyCells::setDur(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void QtCyCells::setUpdate(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void QtCyCells::setStep(double _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void QtCyCells::setView(QString _t1, QWidget * _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void QtCyCells::writeHistory(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void QtCyCells::writeDetail(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void QtCyCells::toggleRun()
{
    QMetaObject::activate(this, &staticMetaObject, 9, 0);
}
QT_END_MOC_NAMESPACE
