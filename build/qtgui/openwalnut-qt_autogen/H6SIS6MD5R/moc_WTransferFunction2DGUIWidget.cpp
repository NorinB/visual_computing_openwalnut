/****************************************************************************
** Meta object code from reading C++ file 'WTransferFunction2DGUIWidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../src/qtgui/controlPanel/transferFunction2D/WTransferFunction2DGUIWidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'WTransferFunction2DGUIWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_WTransferFunction2DGUIWidget_t {
    QByteArrayData data[15];
    char stringdata0[225];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_WTransferFunction2DGUIWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_WTransferFunction2DGUIWidget_t qt_meta_stringdata_WTransferFunction2DGUIWidget = {
    {
QT_MOC_LITERAL(0, 0, 28), // "WTransferFunction2DGUIWidget"
QT_MOC_LITERAL(1, 29, 21), // "cleanTransferFunction"
QT_MOC_LITERAL(2, 51, 0), // ""
QT_MOC_LITERAL(3, 52, 12), // "addBoxWidget"
QT_MOC_LITERAL(4, 65, 17), // "addTriangleWidget"
QT_MOC_LITERAL(5, 83, 19), // "addQuadrangleWidget"
QT_MOC_LITERAL(6, 103, 17), // "addEllipsisWidget"
QT_MOC_LITERAL(7, 121, 11), // "dataChanged"
QT_MOC_LITERAL(8, 133, 14), // "playAnimations"
QT_MOC_LITERAL(9, 148, 14), // "stopAnimations"
QT_MOC_LITERAL(10, 163, 15), // "pauseAnimations"
QT_MOC_LITERAL(11, 179, 17), // "updateRateChanged"
QT_MOC_LITERAL(12, 197, 7), // "newRate"
QT_MOC_LITERAL(13, 205, 15), // "showContextMenu"
QT_MOC_LITERAL(14, 221, 3) // "pos"

    },
    "WTransferFunction2DGUIWidget\0"
    "cleanTransferFunction\0\0addBoxWidget\0"
    "addTriangleWidget\0addQuadrangleWidget\0"
    "addEllipsisWidget\0dataChanged\0"
    "playAnimations\0stopAnimations\0"
    "pauseAnimations\0updateRateChanged\0"
    "newRate\0showContextMenu\0pos"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_WTransferFunction2DGUIWidget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   69,    2, 0x0a /* Public */,
       3,    0,   70,    2, 0x0a /* Public */,
       4,    0,   71,    2, 0x0a /* Public */,
       5,    0,   72,    2, 0x0a /* Public */,
       6,    0,   73,    2, 0x0a /* Public */,
       7,    0,   74,    2, 0x0a /* Public */,
       8,    0,   75,    2, 0x0a /* Public */,
       9,    0,   76,    2, 0x0a /* Public */,
      10,    0,   77,    2, 0x0a /* Public */,
      11,    1,   78,    2, 0x0a /* Public */,
      13,    1,   81,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   12,
    QMetaType::Void, QMetaType::QPoint,   14,

       0        // eod
};

void WTransferFunction2DGUIWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<WTransferFunction2DGUIWidget *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->cleanTransferFunction(); break;
        case 1: _t->addBoxWidget(); break;
        case 2: _t->addTriangleWidget(); break;
        case 3: _t->addQuadrangleWidget(); break;
        case 4: _t->addEllipsisWidget(); break;
        case 5: _t->dataChanged(); break;
        case 6: _t->playAnimations(); break;
        case 7: _t->stopAnimations(); break;
        case 8: _t->pauseAnimations(); break;
        case 9: _t->updateRateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: _t->showContextMenu((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject WTransferFunction2DGUIWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<QGraphicsView::staticMetaObject>(),
    qt_meta_stringdata_WTransferFunction2DGUIWidget.data,
    qt_meta_data_WTransferFunction2DGUIWidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *WTransferFunction2DGUIWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *WTransferFunction2DGUIWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_WTransferFunction2DGUIWidget.stringdata0))
        return static_cast<void*>(this);
    return QGraphicsView::qt_metacast(_clname);
}

int WTransferFunction2DGUIWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGraphicsView::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 11;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
