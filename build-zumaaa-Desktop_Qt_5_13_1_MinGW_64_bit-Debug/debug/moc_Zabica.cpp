/****************************************************************************
** Meta object code from reading C++ file 'Zabica.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.13.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../zumaaa/Zabica.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Zabica.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.13.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Zabica_t {
    QByteArrayData data[8];
    char stringdata0[66];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Zabica_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Zabica_t qt_meta_stringdata_Zabica = {
    {
QT_MOC_LITERAL(0, 0, 6), // "Zabica"
QT_MOC_LITERAL(1, 7, 10), // "Mouse_Move"
QT_MOC_LITERAL(2, 18, 0), // ""
QT_MOC_LITERAL(3, 19, 9), // "Mouse_Pos"
QT_MOC_LITERAL(4, 29, 10), // "Mouse_Left"
QT_MOC_LITERAL(5, 40, 7), // "rotiraj"
QT_MOC_LITERAL(6, 48, 12), // "QMouseEvent*"
QT_MOC_LITERAL(7, 61, 4) // "klik"

    },
    "Zabica\0Mouse_Move\0\0Mouse_Pos\0Mouse_Left\0"
    "rotiraj\0QMouseEvent*\0klik"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Zabica[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   39,    2, 0x06 /* Public */,
       3,    0,   40,    2, 0x06 /* Public */,
       4,    0,   41,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    1,   42,    2, 0x0a /* Public */,
       7,    1,   45,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 6,    2,
    QMetaType::Void, 0x80000000 | 6,    2,

       0        // eod
};

void Zabica::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Zabica *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->Mouse_Move(); break;
        case 1: _t->Mouse_Pos(); break;
        case 2: _t->Mouse_Left(); break;
        case 3: _t->rotiraj((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 4: _t->klik((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Zabica::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Zabica::Mouse_Move)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (Zabica::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Zabica::Mouse_Pos)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (Zabica::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Zabica::Mouse_Left)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Zabica::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_Zabica.data,
    qt_meta_data_Zabica,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Zabica::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Zabica::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Zabica.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "QGraphicsRectItem"))
        return static_cast< QGraphicsRectItem*>(this);
    return QObject::qt_metacast(_clname);
}

int Zabica::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void Zabica::Mouse_Move()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void Zabica::Mouse_Pos()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void Zabica::Mouse_Left()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
