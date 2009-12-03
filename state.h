#ifndef STATE_H
#define STATE_H
#include <QtCore/QString>
struct state {
    QString name;
    int type;// 0: Normal state 1: Start state 2: End state
};

#endif // STATE_H
