/****************************************************************************
** Meta object code from reading C++ file 'WQtModuleConfig.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../src/qtgui/WQtModuleConfig.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'WQtModuleConfig.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_WQtModuleConfig_t {
    QByteArrayData data[14];
    char stringdata0[204];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_WQtModuleConfig_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_WQtModuleConfig_t qt_meta_stringdata_WQtModuleConfig = {
    {
QT_MOC_LITERAL(0, 0, 15), // "WQtModuleConfig"
QT_MOC_LITERAL(1, 16, 7), // "updated"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 9), // "configure"
QT_MOC_LITERAL(4, 35, 6), // "accept"
QT_MOC_LITERAL(5, 42, 6), // "reject"
QT_MOC_LITERAL(6, 49, 13), // "addModulePath"
QT_MOC_LITERAL(7, 63, 16), // "removeModulePath"
QT_MOC_LITERAL(8, 80, 24), // "pathListSelectionChanged"
QT_MOC_LITERAL(9, 105, 24), // "resetAllModuleCheckboxes"
QT_MOC_LITERAL(10, 130, 23), // "refreshModuleCheckboxes"
QT_MOC_LITERAL(11, 154, 24), // "toggleComboboxVisibility"
QT_MOC_LITERAL(12, 179, 18), // "showThemAllUpdated"
QT_MOC_LITERAL(13, 198, 5) // "reset"

    },
    "WQtModuleConfig\0updated\0\0configure\0"
    "accept\0reject\0addModulePath\0"
    "removeModulePath\0pathListSelectionChanged\0"
    "resetAllModuleCheckboxes\0"
    "refreshModuleCheckboxes\0"
    "toggleComboboxVisibility\0showThemAllUpdated\0"
    "reset"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_WQtModuleConfig[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   74,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,   75,    2, 0x0a /* Public */,
       4,    0,   76,    2, 0x0a /* Public */,
       5,    0,   77,    2, 0x0a /* Public */,
       6,    0,   78,    2, 0x0a /* Public */,
       7,    0,   79,    2, 0x0a /* Public */,
       8,    0,   80,    2, 0x08 /* Private */,
       9,    0,   81,    2, 0x08 /* Private */,
      10,    0,   82,    2, 0x08 /* Private */,
      11,    1,   83,    2, 0x08 /* Private */,
      12,    0,   86,    2, 0x08 /* Private */,
      13,    0,   87,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void WQtModuleConfig::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<WQtModuleConfig *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->updated(); break;
        case 1: _t->configure(); break;
        case 2: _t->accept(); break;
        case 3: _t->reject(); break;
        case 4: _t->addModulePath(); break;
        case 5: _t->removeModulePath(); break;
        case 6: _t->pathListSelectionChanged(); break;
        case 7: _t->resetAllModuleCheckboxes(); break;
        case 8: _t->refreshModuleCheckboxes(); break;
        case 9: _t->toggleComboboxVisibility((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: _t->showThemAllUpdated(); break;
        case 11: _t->reset(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (WQtModuleConfig::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WQtModuleConfig::updated)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject WQtModuleConfig::staticMetaObject = { {
    QMetaObject::SuperData::link<QDialog::staticMetaObject>(),
    qt_meta_stringdata_WQtModuleConfig.data,
    qt_meta_data_WQtModuleConfig,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *WQtModuleConfig::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *WQtModuleConfig::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_WQtModuleConfig.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int WQtModuleConfig::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 12;
    }
    return _id;
}

// SIGNAL 0
void WQtModuleConfig::updated()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
