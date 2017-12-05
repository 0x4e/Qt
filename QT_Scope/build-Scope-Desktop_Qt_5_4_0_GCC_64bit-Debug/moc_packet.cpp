/****************************************************************************
** Meta object code from reading C++ file 'packet.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Scope/packet.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'packet.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Packet_t {
    QByteArrayData data[9];
    char stringdata[100];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Packet_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Packet_t qt_meta_stringdata_Packet = {
    {
QT_MOC_LITERAL(0, 0, 6), // "Packet"
QT_MOC_LITERAL(1, 7, 10), // "dataToSend"
QT_MOC_LITERAL(2, 18, 0), // ""
QT_MOC_LITERAL(3, 19, 11), // "QByteArray&"
QT_MOC_LITERAL(4, 31, 4), // "data"
QT_MOC_LITERAL(5, 36, 14), // "update_console"
QT_MOC_LITERAL(6, 51, 11), // "text_string"
QT_MOC_LITERAL(7, 63, 15), // "samplesReceived"
QT_MOC_LITERAL(8, 79, 20) // "readPendingDatagrams"

    },
    "Packet\0dataToSend\0\0QByteArray&\0data\0"
    "update_console\0text_string\0samplesReceived\0"
    "readPendingDatagrams"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Packet[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x06 /* Public */,
       5,    1,   37,    2, 0x06 /* Public */,
       7,    0,   40,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       8,    0,   41,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void Packet::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Packet *_t = static_cast<Packet *>(_o);
        switch (_id) {
        case 0: _t->dataToSend((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 1: _t->update_console((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->samplesReceived(); break;
        case 3: _t->readPendingDatagrams(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (Packet::*_t)(QByteArray & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Packet::dataToSend)) {
                *result = 0;
            }
        }
        {
            typedef void (Packet::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Packet::update_console)) {
                *result = 1;
            }
        }
        {
            typedef void (Packet::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Packet::samplesReceived)) {
                *result = 2;
            }
        }
    }
}

const QMetaObject Packet::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Packet.data,
      qt_meta_data_Packet,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Packet::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Packet::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Packet.stringdata))
        return static_cast<void*>(const_cast< Packet*>(this));
    return QObject::qt_metacast(_clname);
}

int Packet::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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

// SIGNAL 0
void Packet::dataToSend(QByteArray & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Packet::update_console(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void Packet::samplesReceived()
{
    QMetaObject::activate(this, &staticMetaObject, 2, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
