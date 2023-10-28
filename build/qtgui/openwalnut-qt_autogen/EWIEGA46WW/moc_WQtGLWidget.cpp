/****************************************************************************
** Meta object code from reading C++ file 'WQtGLWidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../src/qtgui/WQtGLWidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'WQtGLWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_WQtGLWidget_t {
    QByteArrayData data[11];
    char stringdata0[185];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_WQtGLWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_WQtGLWidget_t qt_meta_stringdata_WQtGLWidget = {
    {
QT_MOC_LITERAL(0, 0, 11), // "WQtGLWidget"
QT_MOC_LITERAL(1, 12, 18), // "renderedFirstFrame"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 5), // "reset"
QT_MOC_LITERAL(4, 38, 17), // "setPresetViewLeft"
QT_MOC_LITERAL(5, 56, 18), // "setPresetViewRight"
QT_MOC_LITERAL(6, 75, 21), // "setPresetViewSuperior"
QT_MOC_LITERAL(7, 97, 21), // "setPresetViewInferior"
QT_MOC_LITERAL(8, 119, 21), // "setPresetViewAnterior"
QT_MOC_LITERAL(9, 141, 22), // "setPresetViewPosterior"
QT_MOC_LITERAL(10, 164, 20) // "setFitScreenPosition"

    },
    "WQtGLWidget\0renderedFirstFrame\0\0reset\0"
    "setPresetViewLeft\0setPresetViewRight\0"
    "setPresetViewSuperior\0setPresetViewInferior\0"
    "setPresetViewAnterior\0setPresetViewPosterior\0"
    "setFitScreenPosition"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_WQtGLWidget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   59,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,   60,    2, 0x0a /* Public */,
       4,    0,   61,    2, 0x0a /* Public */,
       5,    0,   62,    2, 0x0a /* Public */,
       6,    0,   63,    2, 0x0a /* Public */,
       7,    0,   64,    2, 0x0a /* Public */,
       8,    0,   65,    2, 0x0a /* Public */,
       9,    0,   66,    2, 0x0a /* Public */,
      10,    0,   67,    2, 0x0a /* Public */,

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

       0        // eod
};

void WQtGLWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<WQtGLWidget *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->renderedFirstFrame(); break;
        case 1: _t->reset(); break;
        case 2: _t->setPresetViewLeft(); break;
        case 3: _t->setPresetViewRight(); break;
        case 4: _t->setPresetViewSuperior(); break;
        case 5: _t->setPresetViewInferior(); break;
        case 6: _t->setPresetViewAnterior(); break;
        case 7: _t->setPresetViewPosterior(); break;
        case 8: _t->setFitScreenPosition(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (WQtGLWidget::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WQtGLWidget::renderedFirstFrame)) {
                *result = 0;
                return;
            }
        }
    }
    (void)_a;
}

QT_INIT_METAOBJECT const QMetaObject WQtGLWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<WQtGLWidgetParent::staticMetaObject>(),
    qt_meta_stringdata_WQtGLWidget.data,
    qt_meta_data_WQtGLWidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *WQtGLWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *WQtGLWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_WQtGLWidget.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "QOpenGLFunctions"))
        return static_cast< QOpenGLFunctions*>(this);
    return WQtGLWidgetParent::qt_metacast(_clname);
}

int WQtGLWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = WQtGLWidgetParent::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void WQtGLWidget::renderedFirstFrame()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
