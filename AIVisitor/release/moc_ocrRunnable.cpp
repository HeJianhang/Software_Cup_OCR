/****************************************************************************
** Meta object code from reading C++ file 'ocrRunnable.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../ocrRunnable.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ocrRunnable.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_OCRRunnable_t {
    QByteArrayData data[5];
    char stringdata0[35];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_OCRRunnable_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_OCRRunnable_t qt_meta_stringdata_OCRRunnable = {
    {
QT_MOC_LITERAL(0, 0, 11), // "OCRRunnable"
QT_MOC_LITERAL(1, 12, 6), // "Result"
QT_MOC_LITERAL(2, 19, 0), // ""
QT_MOC_LITERAL(3, 20, 6), // "MyPair"
QT_MOC_LITERAL(4, 27, 7) // "DoneOne"

    },
    "OCRRunnable\0Result\0\0MyPair\0DoneOne"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_OCRRunnable[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   24,    2, 0x06 /* Public */,
       4,    0,   27,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void,

       0        // eod
};

void OCRRunnable::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        OCRRunnable *_t = static_cast<OCRRunnable *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->Result((*reinterpret_cast< const MyPair(*)>(_a[1]))); break;
        case 1: _t->DoneOne(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (OCRRunnable::*_t)(const MyPair & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&OCRRunnable::Result)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (OCRRunnable::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&OCRRunnable::DoneOne)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject OCRRunnable::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_OCRRunnable.data,
      qt_meta_data_OCRRunnable,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *OCRRunnable::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *OCRRunnable::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_OCRRunnable.stringdata0))
        return static_cast<void*>(const_cast< OCRRunnable*>(this));
    if (!strcmp(_clname, "QRunnable"))
        return static_cast< QRunnable*>(const_cast< OCRRunnable*>(this));
    return QObject::qt_metacast(_clname);
}

int OCRRunnable::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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

// SIGNAL 0
void OCRRunnable::Result(const MyPair & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void OCRRunnable::DoneOne()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}
struct qt_meta_stringdata_StartRunnable_t {
    QByteArrayData data[1];
    char stringdata0[14];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_StartRunnable_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_StartRunnable_t qt_meta_stringdata_StartRunnable = {
    {
QT_MOC_LITERAL(0, 0, 13) // "StartRunnable"

    },
    "StartRunnable"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_StartRunnable[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

void StartRunnable::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObject StartRunnable::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_StartRunnable.data,
      qt_meta_data_StartRunnable,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *StartRunnable::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *StartRunnable::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_StartRunnable.stringdata0))
        return static_cast<void*>(const_cast< StartRunnable*>(this));
    if (!strcmp(_clname, "QRunnable"))
        return static_cast< QRunnable*>(const_cast< StartRunnable*>(this));
    return QObject::qt_metacast(_clname);
}

int StartRunnable::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
QT_END_MOC_NAMESPACE
