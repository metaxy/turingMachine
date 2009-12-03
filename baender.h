#ifndef BAENDER_H
#define BAENDER_H
#include <QtCore/QList>
#include <QtCore/QString>
#include <QtGui/QListWidget>
class baender
{
public:
    baender(const QList<QString> &bAlph,const QString &l);
    void moveLeft();
    void moveRight();
    //void moveNot();
    int write(const QString &s);
    QString read();
    int setStart(const int &i);
    QList<QString> toStringList();
    void move(const QString &b);
    void showBand(QListWidget *list);
    void readBand(QListWidget *list);
    void addNewLeft();
    void addNewRight();
    QList<QString> bAlph;
    QList<QString> vorne;
    QList<QString> hinten;
    QString current;
    QString leer;
private:


};

#endif // BAENDER_H
