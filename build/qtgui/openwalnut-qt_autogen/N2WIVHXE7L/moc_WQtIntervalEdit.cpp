/****************************************************************************
** Meta object code from reading C++ file 'WQtIntervalEdit.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../src/qtgui/guiElements/WQtIntervalEdit.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'WQtIntervalEdit.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_WQtIntervalEditBase_t {
    QByteArrayData data[8];
    char stringdata0[115];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_WQtIntervalEditBase_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_WQtIntervalEditBase_t qt_meta_stringdata_WQtIntervalEditBase = {
    {
QT_MOC_LITERAL(0, 0, 19), // "WQtIntervalEditBase"
QT_MOC_LITERAL(1, 20, 14), // "minimumChanged"
QT_MOC_LITERAL(2, 35, 0), // ""
QT_MOC_LITERAL(3, 36, 14), // "maximumChanged"
QT_MOC_LITERAL(4, 51, 16), // "minSliderChanged"
QT_MOC_LITERAL(5, 68, 16), // "maxSliderChanged"
QT_MOC_LITERAL(6, 85, 14), // "minEditChanged"
QT_MOC_LITERAL(7, 100, 14) // "maxEditChanged"

    },
    "WQtIntervalEditBase\0minimumChanged\0\0"
    "maximumChanged\0minSliderChanged\0"
    "maxSliderChanged\0minEditChanged\0"
    "maxEditChanged"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_WQtIntervalEditBase[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   44,    2, 0x06 /* Public */,
       3,    0,   45,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,   46,    2, 0x09 /* Protected */,
       5,    0,   47,    2, 0x09 /* Protected */,
       6,    0,   48,    2, 0x09 /* Protected */,
       7,    0,   49,    2, 0x09 /* Protected */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void WQtIntervalEditBase::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<WQtIntervalEditBase *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->minimumChanged(); break;
        case 1: _t->maximumChanged(); break;
        case 2: _t->minSliderChanged(); break;
        case 3: _t->maxSliderChanged(); break;
        case 4: _t->minEditChanged(); break;
        case 5: _t->maxEditChanged(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (WQtIntervalEditBase::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WQtIntervalEditBase::minimumChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (WQtIntervalEditBase::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WQtIntervalEditBase::maximumChanged)) {
                *result = 1;
                return;
            }
        }
    }
    (void)_a;
}

QT_INIT_METAOBJECT const QMetaObject WQtIntervalEditBase::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_WQtIntervalEditBase.data,
    qt_meta_data_WQtIntervalEditBase,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *WQtIntervalEditBase::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *WQtIntervalEditBase::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_WQtIntervalEditBase.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int WQtIntervalEditBase::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void WQtIntervalEditBase::minimumChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void WQtIntervalEditBase::maximumChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
