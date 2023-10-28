/****************************************************************************
** Meta object code from reading C++ file 'WTransferFunction2DBoxWidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../src/qtgui/controlPanel/transferFunction2D/oldCode/WTransferFunction2DBoxWidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'WTransferFunction2DBoxWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_WTransferFunction2DBoxWidget_t {
    QByteArrayData data[8];
    char stringdata0[95];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_WTransferFunction2DBoxWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_WTransferFunction2DBoxWidget_t qt_meta_stringdata_WTransferFunction2DBoxWidget = {
    {
QT_MOC_LITERAL(0, 0, 28), // "WTransferFunction2DBoxWidget"
QT_MOC_LITERAL(1, 29, 13), // "colorSelected"
QT_MOC_LITERAL(2, 43, 0), // ""
QT_MOC_LITERAL(3, 44, 5), // "color"
QT_MOC_LITERAL(4, 50, 15), // "setResizeHandle"
QT_MOC_LITERAL(5, 66, 12), // "ResizePoints"
QT_MOC_LITERAL(6, 79, 6), // "handle"
QT_MOC_LITERAL(7, 86, 8) // "position"

    },
    "WTransferFunction2DBoxWidget\0colorSelected\0"
    "\0color\0setResizeHandle\0ResizePoints\0"
    "handle\0position"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_WTransferFunction2DBoxWidget[] = {

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
       1,    1,   24,    2, 0x0a /* Public */,
       4,    2,   27,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::QColor,    3,
    QMetaType::Void, 0x80000000 | 5, QMetaType::QPointF,    6,    7,

       0        // eod
};

void WTransferFunction2DBoxWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<WTransferFunction2DBoxWidget *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->colorSelected((*reinterpret_cast< const QColor(*)>(_a[1]))); break;
        case 1: _t->setResizeHandle((*reinterpret_cast< ResizePoints(*)>(_a[1])),(*reinterpret_cast< QPointF(*)>(_a[2]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject WTransferFunction2DBoxWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<QGraphicsObject::staticMetaObject>(),
    qt_meta_stringdata_WTransferFunction2DBoxWidget.data,
    qt_meta_data_WTransferFunction2DBoxWidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *WTransferFunction2DBoxWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *WTransferFunction2DBoxWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_WTransferFunction2DBoxWidget.stringdata0))
        return static_cast<void*>(this);
    return QGraphicsObject::qt_metacast(_clname);
}

int WTransferFunction2DBoxWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGraphicsObject::qt_metacall(_c, _id, _a);
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
