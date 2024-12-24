/****************************************************************************
** Meta object code from reading C++ file 'ToDoList.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.5.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../ToDoList.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ToDoList.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.5.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSToDoListENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSToDoListENDCLASS = QtMocHelpers::stringData(
    "ToDoList",
    "addTask",
    "",
    "removeTask",
    "saveTasks",
    "loadTasks",
    "editTask",
    "QListWidgetItem*",
    "item",
    "changeTaskColor",
    "changeFontSize",
    "showContextMenu",
    "pos",
    "searchTasks",
    "text",
    "addTaskWithLink",
    "openLink"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSToDoListENDCLASS_t {
    uint offsetsAndSizes[34];
    char stringdata0[9];
    char stringdata1[8];
    char stringdata2[1];
    char stringdata3[11];
    char stringdata4[10];
    char stringdata5[10];
    char stringdata6[9];
    char stringdata7[17];
    char stringdata8[5];
    char stringdata9[16];
    char stringdata10[15];
    char stringdata11[16];
    char stringdata12[4];
    char stringdata13[12];
    char stringdata14[5];
    char stringdata15[16];
    char stringdata16[9];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSToDoListENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSToDoListENDCLASS_t qt_meta_stringdata_CLASSToDoListENDCLASS = {
    {
        QT_MOC_LITERAL(0, 8),  // "ToDoList"
        QT_MOC_LITERAL(9, 7),  // "addTask"
        QT_MOC_LITERAL(17, 0),  // ""
        QT_MOC_LITERAL(18, 10),  // "removeTask"
        QT_MOC_LITERAL(29, 9),  // "saveTasks"
        QT_MOC_LITERAL(39, 9),  // "loadTasks"
        QT_MOC_LITERAL(49, 8),  // "editTask"
        QT_MOC_LITERAL(58, 16),  // "QListWidgetItem*"
        QT_MOC_LITERAL(75, 4),  // "item"
        QT_MOC_LITERAL(80, 15),  // "changeTaskColor"
        QT_MOC_LITERAL(96, 14),  // "changeFontSize"
        QT_MOC_LITERAL(111, 15),  // "showContextMenu"
        QT_MOC_LITERAL(127, 3),  // "pos"
        QT_MOC_LITERAL(131, 11),  // "searchTasks"
        QT_MOC_LITERAL(143, 4),  // "text"
        QT_MOC_LITERAL(148, 15),  // "addTaskWithLink"
        QT_MOC_LITERAL(164, 8)   // "openLink"
    },
    "ToDoList",
    "addTask",
    "",
    "removeTask",
    "saveTasks",
    "loadTasks",
    "editTask",
    "QListWidgetItem*",
    "item",
    "changeTaskColor",
    "changeFontSize",
    "showContextMenu",
    "pos",
    "searchTasks",
    "text",
    "addTaskWithLink",
    "openLink"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSToDoListENDCLASS[] = {

 // content:
      11,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   80,    2, 0x08,    1 /* Private */,
       3,    0,   81,    2, 0x08,    2 /* Private */,
       4,    0,   82,    2, 0x08,    3 /* Private */,
       5,    0,   83,    2, 0x08,    4 /* Private */,
       6,    1,   84,    2, 0x08,    5 /* Private */,
       9,    0,   87,    2, 0x08,    7 /* Private */,
      10,    0,   88,    2, 0x08,    8 /* Private */,
      11,    1,   89,    2, 0x08,    9 /* Private */,
      13,    1,   92,    2, 0x08,   11 /* Private */,
      15,    0,   95,    2, 0x08,   13 /* Private */,
      16,    1,   96,    2, 0x08,   14 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QPoint,   12,
    QMetaType::Void, QMetaType::QString,   14,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 7,    8,

       0        // eod
};

Q_CONSTINIT const QMetaObject ToDoList::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_CLASSToDoListENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSToDoListENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSToDoListENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<ToDoList, std::true_type>,
        // method 'addTask'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'removeTask'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'saveTasks'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'loadTasks'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'editTask'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QListWidgetItem *, std::false_type>,
        // method 'changeTaskColor'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'changeFontSize'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'showContextMenu'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QPoint &, std::false_type>,
        // method 'searchTasks'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'addTaskWithLink'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'openLink'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QListWidgetItem *, std::false_type>
    >,
    nullptr
} };

void ToDoList::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ToDoList *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->addTask(); break;
        case 1: _t->removeTask(); break;
        case 2: _t->saveTasks(); break;
        case 3: _t->loadTasks(); break;
        case 4: _t->editTask((*reinterpret_cast< std::add_pointer_t<QListWidgetItem*>>(_a[1]))); break;
        case 5: _t->changeTaskColor(); break;
        case 6: _t->changeFontSize(); break;
        case 7: _t->showContextMenu((*reinterpret_cast< std::add_pointer_t<QPoint>>(_a[1]))); break;
        case 8: _t->searchTasks((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 9: _t->addTaskWithLink(); break;
        case 10: _t->openLink((*reinterpret_cast< std::add_pointer_t<QListWidgetItem*>>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject *ToDoList::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ToDoList::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSToDoListENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int ToDoList::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 11;
    }
    return _id;
}
QT_WARNING_POP
