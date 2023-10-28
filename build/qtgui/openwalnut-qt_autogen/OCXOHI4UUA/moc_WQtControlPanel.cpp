/****************************************************************************
** Meta object code from reading C++ file 'WQtControlPanel.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../src/qtgui/controlPanel/WQtControlPanel.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'WQtControlPanel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_WQtControlPanel_t {
    QByteArrayData data[28];
    char stringdata0[357];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_WQtControlPanel_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_WQtControlPanel_t qt_meta_stringdata_WQtControlPanel = {
    {
QT_MOC_LITERAL(0, 0, 15), // "WQtControlPanel"
QT_MOC_LITERAL(1, 16, 14), // "selectTreeItem"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 16), // "reselectTreeItem"
QT_MOC_LITERAL(4, 49, 17), // "selectRoiTreeItem"
QT_MOC_LITERAL(5, 67, 16), // "QTreeWidgetItem*"
QT_MOC_LITERAL(6, 84, 4), // "item"
QT_MOC_LITERAL(7, 89, 16), // "selectDataModule"
QT_MOC_LITERAL(8, 106, 26), // "osg::ref_ptr<WGETexture3D>"
QT_MOC_LITERAL(9, 133, 7), // "texture"
QT_MOC_LITERAL(10, 141, 14), // "findModuleItem"
QT_MOC_LITERAL(11, 156, 13), // "WModule::SPtr"
QT_MOC_LITERAL(12, 170, 6), // "module"
QT_MOC_LITERAL(13, 177, 12), // "buildPropTab"
QT_MOC_LITERAL(14, 190, 28), // "std::shared_ptr<WProperties>"
QT_MOC_LITERAL(15, 219, 5), // "props"
QT_MOC_LITERAL(16, 225, 9), // "infoProps"
QT_MOC_LITERAL(17, 235, 11), // "std::string"
QT_MOC_LITERAL(18, 247, 4), // "name"
QT_MOC_LITERAL(19, 252, 8), // "QWidget*"
QT_MOC_LITERAL(20, 261, 6), // "inject"
QT_MOC_LITERAL(21, 268, 14), // "changeTreeItem"
QT_MOC_LITERAL(22, 283, 6), // "column"
QT_MOC_LITERAL(23, 290, 17), // "deleteROITreeItem"
QT_MOC_LITERAL(24, 308, 12), // "deleteModule"
QT_MOC_LITERAL(25, 321, 17), // "handleRoiDragDrop"
QT_MOC_LITERAL(26, 339, 11), // "QDropEvent*"
QT_MOC_LITERAL(27, 351, 5) // "event"

    },
    "WQtControlPanel\0selectTreeItem\0\0"
    "reselectTreeItem\0selectRoiTreeItem\0"
    "QTreeWidgetItem*\0item\0selectDataModule\0"
    "osg::ref_ptr<WGETexture3D>\0texture\0"
    "findModuleItem\0WModule::SPtr\0module\0"
    "buildPropTab\0std::shared_ptr<WProperties>\0"
    "props\0infoProps\0std::string\0name\0"
    "QWidget*\0inject\0changeTreeItem\0column\0"
    "deleteROITreeItem\0deleteModule\0"
    "handleRoiDragDrop\0QDropEvent*\0event"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_WQtControlPanel[] = {

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
       1,    0,   69,    2, 0x08 /* Private */,
       3,    0,   70,    2, 0x08 /* Private */,
       4,    1,   71,    2, 0x08 /* Private */,
       7,    1,   74,    2, 0x08 /* Private */,
      10,    1,   77,    2, 0x08 /* Private */,
      13,    4,   80,    2, 0x08 /* Private */,
      13,    3,   89,    2, 0x28 /* Private | MethodCloned */,
      21,    2,   96,    2, 0x08 /* Private */,
      23,    0,  101,    2, 0x08 /* Private */,
      24,    0,  102,    2, 0x08 /* Private */,
      25,    1,  103,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 5,    6,
    QMetaType::Void, 0x80000000 | 8,    9,
    0x80000000 | 5, 0x80000000 | 11,   12,
    QMetaType::Void, 0x80000000 | 14, 0x80000000 | 14, 0x80000000 | 17, 0x80000000 | 19,   15,   16,   18,   20,
    QMetaType::Void, 0x80000000 | 14, 0x80000000 | 14, 0x80000000 | 17,   15,   16,   18,
    QMetaType::Void, 0x80000000 | 5, QMetaType::Int,    6,   22,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 26,   27,

       0        // eod
};

void WQtControlPanel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<WQtControlPanel *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->selectTreeItem(); break;
        case 1: _t->reselectTreeItem(); break;
        case 2: _t->selectRoiTreeItem((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1]))); break;
        case 3: _t->selectDataModule((*reinterpret_cast< osg::ref_ptr<WGETexture3D>(*)>(_a[1]))); break;
        case 4: { QTreeWidgetItem* _r = _t->findModuleItem((*reinterpret_cast< WModule::SPtr(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QTreeWidgetItem**>(_a[0]) = std::move(_r); }  break;
        case 5: _t->buildPropTab((*reinterpret_cast< std::shared_ptr<WProperties>(*)>(_a[1])),(*reinterpret_cast< std::shared_ptr<WProperties>(*)>(_a[2])),(*reinterpret_cast< const std::string(*)>(_a[3])),(*reinterpret_cast< QWidget*(*)>(_a[4]))); break;
        case 6: _t->buildPropTab((*reinterpret_cast< std::shared_ptr<WProperties>(*)>(_a[1])),(*reinterpret_cast< std::shared_ptr<WProperties>(*)>(_a[2])),(*reinterpret_cast< const std::string(*)>(_a[3]))); break;
        case 7: _t->changeTreeItem((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 8: _t->deleteROITreeItem(); break;
        case 9: _t->deleteModule(); break;
        case 10: _t->handleRoiDragDrop((*reinterpret_cast< QDropEvent*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 5:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 3:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QWidget* >(); break;
            }
            break;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject WQtControlPanel::staticMetaObject = { {
    QMetaObject::SuperData::link<WQtDockWidget::staticMetaObject>(),
    qt_meta_stringdata_WQtControlPanel.data,
    qt_meta_data_WQtControlPanel,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *WQtControlPanel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *WQtControlPanel::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_WQtControlPanel.stringdata0))
        return static_cast<void*>(this);
    return WQtDockWidget::qt_metacast(_clname);
}

int WQtControlPanel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = WQtDockWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
