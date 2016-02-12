/****************************************************************************
** Meta object code from reading C++ file 'uiboundary.h'
**
** Created: Thu Dec 19 18:57:44 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "uiboundary.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'uiboundary.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_UiBoundary[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x0a,
      30,   11,   11,   11, 0x0a,
      45,   11,   11,   11, 0x08,
      71,   11,   11,   11, 0x08,
      98,   11,   11,   11, 0x08,
     129,   11,   11,   11, 0x08,
     153,   11,   11,   11, 0x08,
     196,  187,   11,   11, 0x08,
     231,  187,   11,   11, 0x08,
     266,  187,   11,   11, 0x08,
     300,  187,   11,   11, 0x08,
     334,  187,   11,   11, 0x08,
     370,   11,   11,   11, 0x08,
     397,   11,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_UiBoundary[] = {
    "UiBoundary\0\0update_settings()\0"
    "get_settings()\0on_Button_Vugge_clicked()\0"
    "on_Save_settings_clicked()\0"
    "on_Button_Automatisk_clicked()\0"
    "on_Button_Uro_clicked()\0"
    "on_Button_Indstillinger_clicked()\0"
    "position\0on_Tempmax_Slider_sliderMoved(int)\0"
    "on_Tempmin_Slider_sliderMoved(int)\0"
    "on_Lydmax_Slider_sliderMoved(int)\0"
    "on_Urotid_Slider_sliderMoved(int)\0"
    "on_Vuggetid_Slider_sliderMoved(int)\0"
    "on_Button_cancel_clicked()\0"
    "on_Button_default_clicked()\0"
};

void UiBoundary::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        UiBoundary *_t = static_cast<UiBoundary *>(_o);
        switch (_id) {
        case 0: _t->update_settings(); break;
        case 1: _t->get_settings(); break;
        case 2: _t->on_Button_Vugge_clicked(); break;
        case 3: _t->on_Save_settings_clicked(); break;
        case 4: _t->on_Button_Automatisk_clicked(); break;
        case 5: _t->on_Button_Uro_clicked(); break;
        case 6: _t->on_Button_Indstillinger_clicked(); break;
        case 7: _t->on_Tempmax_Slider_sliderMoved((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->on_Tempmin_Slider_sliderMoved((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->on_Lydmax_Slider_sliderMoved((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: _t->on_Urotid_Slider_sliderMoved((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: _t->on_Vuggetid_Slider_sliderMoved((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 12: _t->on_Button_cancel_clicked(); break;
        case 13: _t->on_Button_default_clicked(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData UiBoundary::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject UiBoundary::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_UiBoundary,
      qt_meta_data_UiBoundary, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &UiBoundary::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *UiBoundary::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *UiBoundary::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_UiBoundary))
        return static_cast<void*>(const_cast< UiBoundary*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int UiBoundary::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
