/****************************************************************************
** Meta object code from reading C++ file 'ADC_stream.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Scope/ADC_stream.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ADC_stream.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_ADC_stream_t {
    QByteArrayData data[9];
    char stringdata[104];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ADC_stream_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ADC_stream_t qt_meta_stringdata_ADC_stream = {
    {
QT_MOC_LITERAL(0, 0, 10), // "ADC_stream"
QT_MOC_LITERAL(1, 11, 10), // "dataToSend"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 11), // "QByteArray&"
QT_MOC_LITERAL(4, 35, 4), // "data"
QT_MOC_LITERAL(5, 40, 14), // "update_console"
QT_MOC_LITERAL(6, 55, 11), // "text_string"
QT_MOC_LITERAL(7, 67, 15), // "samplesReceived"
QT_MOC_LITERAL(8, 83, 20) // "readPendingDatagrams"

    },
    "ADC_stream\0dataToSend\0\0QByteArray&\0"
    "data\0update_console\0text_string\0"
    "samplesReceived\0readPendingDatagrams"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ADC_stream[] = {

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

void ADC_stream::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ADC_stream *_t = static_cast<ADC_stream *>(_o);
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
            typedef void (ADC_stream::*_t)(QByteArray & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ADC_stream::dataToSend)) {
                *result = 0;
            }
        }
        {
            typedef void (ADC_stream::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ADC_stream::update_console)) {
                *result = 1;
            }
        }
        {
            typedef void (ADC_stream::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ADC_stream::samplesReceived)) {
                *result = 2;
            }
        }
    }
}

const QMetaObject ADC_stream::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_ADC_stream.data,
      qt_meta_data_ADC_stream,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *ADC_stream::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ADC_stream::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_ADC_stream.stringdata))
        return static_cast<void*>(const_cast< ADC_stream*>(this));
    return QObject::qt_metacast(_clname);
}

int ADC_stream::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void ADC_stream::dataToSend(QByteArray & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ADC_stream::update_console(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ADC_stream::samplesReceived()
{
    QMetaObject::activate(this, &staticMetaObject, 2, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
