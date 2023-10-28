/****************************************************************************
** Meta object code from reading C++ file 'WPropertyIntWidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../src/qtgui/controlPanel/WPropertyIntWidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'WPropertyIntWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_WPropertyIntWidget_t {
    QByteArrayData data[8];
    char stringdata0[82];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_WPropertyIntWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_WPropertyIntWidget_t qt_meta_stringdata_WPropertyIntWidget = {
    {
QT_MOC_LITERAL(0, 0, 18), // "WPropertyIntWidget"
QT_MOC_LITERAL(1, 19, 13), // "sliderChanged"
QT_MOC_LITERAL(2, 33, 0), // ""
QT_MOC_LITERAL(3, 34, 5), // "value"
QT_MOC_LITERAL(4, 40, 11), // "editChanged"
QT_MOC_LITERAL(5, 52, 10), // "textEdited"
QT_MOC_LITERAL(6, 63, 4), // "text"
QT_MOC_LITERAL(7, 68, 13) // "minMaxUpdated"

    },
    "WPropertyIntWidget\0sliderChanged\0\0"
    "value\0editChanged\0textEdited\0text\0"
    "minMaxUpdated"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_WPropertyIntWidget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x0a /* Public */,
       4,    0,   37,    2, 0x0a /* Public */,
       5,    1,   38,    2, 0x0a /* Public */,
       7,    0,   41,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::Void,

       0        // eod
};

void WPropertyIntWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<WPropertyIntWidget *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->sliderChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->editChanged(); break;
        case 2: _t->textEdited((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: _t->minMaxUpdated(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject WPropertyIntWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<WPropertyWidget::staticMetaObject>(),
    qt_meta_stringdata_WPropertyIntWidget.data,
    qt_meta_data_WPropertyIntWidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *WPropertyIntWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *WPropertyIntWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_WPropertyIntWidget.stringdata0))
        return static_cast<void*>(this);
    return WPropertyWidget::qt_metacast(_clname);
}

int WPropertyIntWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = WPropertyWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
