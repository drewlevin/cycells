/****************************************************************************
** Meta object code from reading C++ file 'QtEngineThread.h'
**
** Created: Tue Apr 24 13:13:52 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "QtEngineThread.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QtEngineThread.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QtEngineThread[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: signature, parameters, type, tag, flags
      27,   16,   15,   15, 0x05,
      57,   48,   15,   15, 0x05,
      86,   81,   15,   15, 0x05,
     113,  106,   15,   15, 0x05,
     142,  135,   15,   15, 0x05,

 // slots: signature, parameters, type, tag, flags
     175,  164,   15,   15, 0x0a,
     194,  164,   15,   15, 0x0a,
     219,  214,   15,   15, 0x0a,
     243,  234,   15,   15, 0x0a,
     264,  257,   15,   15, 0x0a,
     290,  281,   15,   15, 0x0a,
     322,  308,   15,   15, 0x0a,
     350,  164,   15,   15, 0x0a,
     374,  164,   15,   15, 0x0a,
     397,   15,   15,   15, 0x0a,
     409,   15,   15,   15, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_QtEngineThread[] = {
    "QtEngineThread\0\0cells,mols\0"
    "updateTypes(int,int)\0geometry\0"
    "updateGeometry(QString)\0time\0"
    "updateTime(QString)\0status\0"
    "updateStatus(QString)\0tissue\0"
    "updateDialog(Tissue*)\0qsFileName\0"
    "onLoadDef(QString)\0onLoadInit(QString)\0"
    "seed\0onSetSeed(int)\0duration\0onSetDur(int)\0"
    "update\0onSetUpdate(int)\0timestep\0"
    "onSetStep(double)\0qsView,widget\0"
    "onSetView(QString,QWidget*)\0"
    "onWriteHistory(QString)\0onWriteDetail(QString)\0"
    "toggleRun()\0onIdle()\0"
};

const QMetaObject QtEngineThread::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_QtEngineThread,
      qt_meta_data_QtEngineThread, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QtEngineThread::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QtEngineThread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QtEngineThread::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QtEngineThread))
        return static_cast<void*>(const_cast< QtEngineThread*>(this));
    return QThread::qt_metacast(_clname);
}

int QtEngineThread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: updateTypes((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: updateGeometry((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: updateTime((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: updateStatus((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: updateDialog((*reinterpret_cast< Tissue*(*)>(_a[1]))); break;
        case 5: onLoadDef((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 6: onLoadInit((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 7: onSetSeed((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: onSetDur((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: onSetUpdate((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: onSetStep((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 11: onSetView((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QWidget*(*)>(_a[2]))); break;
        case 12: onWriteHistory((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 13: onWriteDetail((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 14: toggleRun(); break;
        case 15: onIdle(); break;
        default: ;
        }
        _id -= 16;
    }
    return _id;
}

// SIGNAL 0
void QtEngineThread::updateTypes(int _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void QtEngineThread::updateGeometry(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void QtEngineThread::updateTime(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void QtEngineThread::updateStatus(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void QtEngineThread::updateDialog(Tissue * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_END_MOC_NAMESPACE
