/****************************************************************************
** Meta object code from reading C++ file 'WQtNetworkItemGrid.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../src/qtgui/networkEditor/WQtNetworkItemGrid.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'WQtNetworkItemGrid.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_WQtNetworkItemGrid_t {
    QByteArrayData data[8];
    char stringdata0[100];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_WQtNetworkItemGrid_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_WQtNetworkItemGrid_t qt_meta_stringdata_WQtNetworkItemGrid = {
    {
QT_MOC_LITERAL(0, 0, 18), // "WQtNetworkItemGrid"
QT_MOC_LITERAL(1, 19, 13), // "updatedBounds"
QT_MOC_LITERAL(2, 33, 0), // ""
QT_MOC_LITERAL(3, 34, 7), // "blendIn"
QT_MOC_LITERAL(4, 42, 8), // "blendOut"
QT_MOC_LITERAL(5, 51, 20), // "animationBlendInTick"
QT_MOC_LITERAL(6, 72, 5), // "value"
QT_MOC_LITERAL(7, 78, 21) // "animationBlendOutTick"

    },
    "WQtNetworkItemGrid\0updatedBounds\0\0"
    "blendIn\0blendOut\0animationBlendInTick\0"
    "value\0animationBlendOutTick"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_WQtNetworkItemGrid[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   39,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,   40,    2, 0x0a /* Public */,
       4,    0,   41,    2, 0x0a /* Public */,
       5,    1,   42,    2, 0x08 /* Private */,
       7,    1,   45,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QReal,    6,
    QMetaType::Void, QMetaType::QReal,    6,

       0        // eod
};

void WQtNetworkItemGrid::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<WQtNetworkItemGrid *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->updatedBounds(); break;
        case 1: _t->blendIn(); break;
        case 2: _t->blendOut(); break;
        case 3: _t->animationBlendInTick((*reinterpret_cast< qreal(*)>(_a[1]))); break;
        case 4: _t->animationBlendOutTick((*reinterpret_cast< qreal(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (WQtNetworkItemGrid::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WQtNetworkItemGrid::updatedBounds)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject WQtNetworkItemGrid::staticMetaObject = { {
    QMetaObject::SuperData::link<QGraphicsObject::staticMetaObject>(),
    qt_meta_stringdata_WQtNetworkItemGrid.data,
    qt_meta_data_WQtNetworkItemGrid,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *WQtNetworkItemGrid::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *WQtNetworkItemGrid::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_WQtNetworkItemGrid.stringdata0))
        return static_cast<void*>(this);
    return QGraphicsObject::qt_metacast(_clname);
}

int WQtNetworkItemGrid::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGraphicsObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void WQtNetworkItemGrid::updatedBounds()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
