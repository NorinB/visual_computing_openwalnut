/****************************************************************************
** Meta object code from reading C++ file 'WPropertyMatrix4X4Widget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../src/qtgui/controlPanel/WPropertyMatrix4X4Widget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'WPropertyMatrix4X4Widget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_WPropertyMatrix4X4Widget_t {
    QByteArrayData data[5];
    char stringdata0[54];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_WPropertyMatrix4X4Widget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_WPropertyMatrix4X4Widget_t qt_meta_stringdata_WPropertyMatrix4X4Widget = {
    {
QT_MOC_LITERAL(0, 0, 24), // "WPropertyMatrix4X4Widget"
QT_MOC_LITERAL(1, 25, 11), // "editChanged"
QT_MOC_LITERAL(2, 37, 0), // ""
QT_MOC_LITERAL(3, 38, 10), // "textEdited"
QT_MOC_LITERAL(4, 49, 4) // "text"

    },
    "WPropertyMatrix4X4Widget\0editChanged\0"
    "\0textEdited\0text"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_WPropertyMatrix4X4Widget[] = {

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
       3,    1,   25,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    4,

       0        // eod
};

void WPropertyMatrix4X4Widget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<WPropertyMatrix4X4Widget *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->editChanged(); break;
        case 1: _t->textEdited((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject WPropertyMatrix4X4Widget::staticMetaObject = { {
    QMetaObject::SuperData::link<WPropertyWidget::staticMetaObject>(),
    qt_meta_stringdata_WPropertyMatrix4X4Widget.data,
    qt_meta_data_WPropertyMatrix4X4Widget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *WPropertyMatrix4X4Widget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *WPropertyMatrix4X4Widget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_WPropertyMatrix4X4Widget.stringdata0))
        return static_cast<void*>(this);
    return WPropertyWidget::qt_metacast(_clname);
}

int WPropertyMatrix4X4Widget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = WPropertyWidget::qt_metacall(_c, _id, _a);
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
