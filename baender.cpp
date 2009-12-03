#include "baender.h"
#include <QtGui/QListWidget>
baender::baender(const QList<QString> &bAlph,const QString &l)
{
    leer = l;
    current = leer;
    hinten << leer << leer << leer;
    vorne << leer << leer << leer;
}
void baender::move(const QString &richtung)
{
    if(richtung == "R") {
        moveRight();
    } else if(richtung == "L") {
        moveLeft();
    }
}
void baender::moveLeft()
{
    vorne.insert(0,current);
    if(hinten.isEmpty()) {
        hinten.append(leer);
    }
    current = hinten.last();
    hinten.removeLast();
}
void baender::moveRight()
{
    hinten.append(current);
    if(vorne.isEmpty()) {
        vorne.append(leer);
    }
    current = vorne.first();
    vorne.removeFirst();

}
    //void baender::moveNot();
int baender::write(const QString &s)
{
   /* if(bAlph.lastIndexOf(s) == -1) {
        return 1;//nicht im bandalphabet
    } else {*/
        current = s;
      //  return 0;//alles ok
   /* }*/
}
QString baender::read()
{
    return current;
}
int baender::setStart(const int &i)
{
}
QList<QString> baender::toStringList()
{
    QList<QString> out;
    out << hinten << "_"+current+"_" << vorne;
    return out;
}
void baender::showBand(QListWidget *list)
{
    list->clear();
    QList<QString> out;
    out << hinten << current << vorne;
    list->insertItems(0,out);
    list->setCurrentRow(hinten.size());
    for(int i = 0;i < list->count();i++)
    {

          list->item(i)->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsEnabled);
    }
}
void baender::readBand(QListWidget *list)
{
    hinten.clear();
    vorne.clear();
    for(int i = 0;i < list->count();i++)
    {
        if( i < list->currentRow())
        {
            hinten << list->item(i)->text();
        }
        else if( i == list->currentRow())
        {
            current = list->item(i)->text();
        }
        else
        {
            vorne << list->item(i)->text();
        }
    }

}
void baender::addNewLeft()
{
    hinten.insert(0,leer);
}
void baender::addNewRight()
{
    vorne.append(leer);
}
