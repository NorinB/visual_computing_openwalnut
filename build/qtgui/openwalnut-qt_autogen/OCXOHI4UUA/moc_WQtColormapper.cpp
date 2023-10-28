/****************************************************************************
** Meta object code from reading C++ file 'WQtColormapper.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../src/qtgui/controlPanel/WQtColormapper.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'WQtColormapper.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_WQtColormapper_t {
    QByteArrayData data[17];
    char stringdata0[237];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_WQtColormapper_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_WQtColormapper_t qt_meta_stringdata_WQtColormapper = {
    {
QT_MOC_LITERAL(0, 0, 14), // "WQtColormapper"
QT_MOC_LITERAL(1, 15, 23), // "textureSelectionChanged"
QT_MOC_LITERAL(2, 39, 0), // ""
QT_MOC_LITERAL(3, 40, 26), // "osg::ref_ptr<WGETexture3D>"
QT_MOC_LITERAL(4, 67, 7), // "texture"
QT_MOC_LITERAL(5, 75, 9), // "rowsMoved"
QT_MOC_LITERAL(6, 85, 11), // "QModelIndex"
QT_MOC_LITERAL(7, 97, 12), // "sourceParent"
QT_MOC_LITERAL(8, 110, 11), // "sourceStart"
QT_MOC_LITERAL(9, 122, 9), // "sourceEnd"
QT_MOC_LITERAL(10, 132, 17), // "destinationParent"
QT_MOC_LITERAL(11, 150, 14), // "destinationRow"
QT_MOC_LITERAL(12, 165, 20), // "handleTextureClicked"
QT_MOC_LITERAL(13, 186, 12), // "moveItemDown"
QT_MOC_LITERAL(14, 199, 10), // "moveItemUp"
QT_MOC_LITERAL(15, 210, 14), // "moveItemBottom"
QT_MOC_LITERAL(16, 225, 11) // "moveItemTop"

    },
    "WQtColormapper\0textureSelectionChanged\0"
    "\0osg::ref_ptr<WGETexture3D>\0texture\0"
    "rowsMoved\0QModelIndex\0sourceParent\0"
    "sourceStart\0sourceEnd\0destinationParent\0"
    "destinationRow\0handleTextureClicked\0"
    "moveItemDown\0moveItemUp\0moveItemBottom\0"
    "moveItemTop"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_WQtColormapper[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   49,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    5,   52,    2, 0x08 /* Private */,
      12,    0,   63,    2, 0x08 /* Private */,
      13,    0,   64,    2, 0x08 /* Private */,
      14,    0,   65,    2, 0x08 /* Private */,
      15,    0,   66,    2, 0x08 /* Private */,
      16,    0,   67,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 6, QMetaType::Int, QMetaType::Int, 0x80000000 | 6, QMetaType::Int,    7,    8,    9,   10,   11,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void WQtColormapper::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<WQtColormapper *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->textureSelectionChanged((*reinterpret_cast< osg::ref_ptr<WGETexture3D>(*)>(_a[1]))); break;
        case 1: _t->rowsMoved((*reinterpret_cast< const QModelIndex(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< const QModelIndex(*)>(_a[4])),(*reinterpret_cast< int(*)>(_a[5]))); break;
        case 2: _t->handleTextureClicked(); break;
        case 3: _t->moveItemDown(); break;
        case 4: _t->moveItemUp(); break;
        case 5: _t->moveItemBottom(); break;
        case 6: _t->moveItemTop(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (WQtColormapper::*)(osg::ref_ptr<WGETexture3D> );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WQtColormapper::textureSelectionChanged)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject WQtColormapper::staticMetaObject = { {
    QMetaObject::SuperData::link<WQtDockWidget::staticMetaObject>(),
    qt_meta_stringdata_WQtColormapper.data,
    qt_meta_data_WQtColormapper,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *WQtColormapper::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *WQtColormapper::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_WQtColormapper.stringdata0))
        return static_cast<void*>(this);
    return WQtDockWidget::qt_metacast(_clname);
}

int WQtColormapper::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = WQtDockWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void WQtColormapper::textureSelectionChanged(osg::ref_ptr<WGETexture3D> _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
