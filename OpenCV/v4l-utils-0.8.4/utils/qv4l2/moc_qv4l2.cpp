/****************************************************************************
** Meta object code from reading C++ file 'qv4l2.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "qv4l2.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qv4l2.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ApplicationWindow[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      19,   18,   18,   18, 0x08,
      33,   18,   18,   18, 0x08,
      51,   18,   18,   18, 0x08,
      66,   18,   18,   18, 0x08,
      77,   18,   18,   18, 0x08,
      87,   18,   18,   18, 0x08,
     100,   18,   18,   18, 0x08,
     116,   18,   18,   18, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_ApplicationWindow[] = {
    "ApplicationWindow\0\0closeDevice()\0"
    "closeCaptureWin()\0capStart(bool)\0"
    "capFrame()\0opendev()\0openrawdev()\0"
    "ctrlAction(int)\0about()\0"
};

void ApplicationWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ApplicationWindow *_t = static_cast<ApplicationWindow *>(_o);
        switch (_id) {
        case 0: _t->closeDevice(); break;
        case 1: _t->closeCaptureWin(); break;
        case 2: _t->capStart((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->capFrame(); break;
        case 4: _t->opendev(); break;
        case 5: _t->openrawdev(); break;
        case 6: _t->ctrlAction((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->about(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ApplicationWindow::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ApplicationWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_ApplicationWindow,
      qt_meta_data_ApplicationWindow, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ApplicationWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ApplicationWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ApplicationWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ApplicationWindow))
        return static_cast<void*>(const_cast< ApplicationWindow*>(this));
    if (!strcmp(_clname, "v4l2"))
        return static_cast< v4l2*>(const_cast< ApplicationWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int ApplicationWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
