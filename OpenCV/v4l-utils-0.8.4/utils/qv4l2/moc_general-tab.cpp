/****************************************************************************
** Meta object code from reading C++ file 'general-tab.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "general-tab.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'general-tab.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_GeneralTab[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x08,
      30,   11,   11,   11, 0x08,
      49,   11,   11,   11, 0x08,
      72,   11,   11,   11, 0x08,
      96,   11,   11,   11, 0x08,
     117,   11,   11,   11, 0x08,
     136,   11,   11,   11, 0x08,
     158,   11,   11,   11, 0x08,
     182,   11,   11,   11, 0x08,
     199,   11,   11,   11, 0x08,
     224,   11,   11,   11, 0x08,
     244,   11,   11,   11, 0x08,
     265,   11,   11,   11, 0x08,
     287,   11,   11,   11, 0x08,
     313,   11,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_GeneralTab[] = {
    "GeneralTab\0\0inputChanged(int)\0"
    "outputChanged(int)\0inputAudioChanged(int)\0"
    "outputAudioChanged(int)\0standardChanged(int)\0"
    "presetChanged(int)\0freqTableChanged(int)\0"
    "freqChannelChanged(int)\0freqChanged(int)\0"
    "vidCapFormatChanged(int)\0frameWidthChanged()\0"
    "frameHeightChanged()\0frameSizeChanged(int)\0"
    "frameIntervalChanged(int)\0"
    "vidOutFormatChanged(int)\0"
};

void GeneralTab::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        GeneralTab *_t = static_cast<GeneralTab *>(_o);
        switch (_id) {
        case 0: _t->inputChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->outputChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->inputAudioChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->outputAudioChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->standardChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->presetChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->freqTableChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->freqChannelChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->freqChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->vidCapFormatChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: _t->frameWidthChanged(); break;
        case 11: _t->frameHeightChanged(); break;
        case 12: _t->frameSizeChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 13: _t->frameIntervalChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 14: _t->vidOutFormatChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData GeneralTab::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject GeneralTab::staticMetaObject = {
    { &QGridLayout::staticMetaObject, qt_meta_stringdata_GeneralTab,
      qt_meta_data_GeneralTab, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &GeneralTab::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *GeneralTab::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *GeneralTab::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_GeneralTab))
        return static_cast<void*>(const_cast< GeneralTab*>(this));
    if (!strcmp(_clname, "v4l2"))
        return static_cast< v4l2*>(const_cast< GeneralTab*>(this));
    return QGridLayout::qt_metacast(_clname);
}

int GeneralTab::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGridLayout::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
