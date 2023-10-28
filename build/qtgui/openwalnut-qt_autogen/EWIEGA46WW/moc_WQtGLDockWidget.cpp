/****************************************************************************
** Meta object code from reading C++ file 'WQtGLDockWidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../src/qtgui/WQtGLDockWidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'WQtGLDockWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_WQtGLDockWidget_t {
    QByteArrayData data[5];
    char stringdata0[72];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_WQtGLDockWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_WQtGLDockWidget_t qt_meta_stringdata_WQtGLDockWidget = {
    {
QT_MOC_LITERAL(0, 0, 15), // "WQtGLDockWidget"
QT_MOC_LITERAL(1, 16, 23), // "openScreenCaptureConfig"
QT_MOC_LITERAL(2, 40, 0), // ""
QT_MOC_LITERAL(3, 41, 22), // "handleVisibilityChange"
QT_MOC_LITERAL(4, 64, 7) // "visible"

    },
    "WQtGLDockWidget\0openScreenCaptureConfig\0"
    "\0handleVisibilityChange\0visible"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_WQtGLDockWidget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   24,    2, 0x0a /* Public */,
       3,    1,   25,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    4,

       0        // eod
};

void WQtGLDockWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<WQtGLDockWidget *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->openScreenCaptureConfig(); break;
        case 1: _t->handleVisibilityChange((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject WQtGLDockWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<WQtDockWidget::staticMetaObject>(),
    qt_meta_stringdata_WQtGLDockWidget.data,
    qt_meta_data_WQtGLDockWidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *WQtGLDockWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *WQtGLDockWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_WQtGLDockWidget.stringdata0))
        return static_cast<void*>(this);
    return WQtDockWidget::qt_metacast(_clname);
}

int WQtGLDockWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = WQtDockWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
