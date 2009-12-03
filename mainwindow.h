#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include <QList>
#include <QString>
#include "function.h"
#include "state.h"
#include "baender.h"
namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public slots:
    void addFunction();
    void addFunction(struct function f);
    void addState();
    void addState(struct state s);
    void start();
    void tick();
    void addNewLeft();
    void addNewRight();
    void saveMachine();
    void loadMachine();


public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void showStates();

private:
    Ui::MainWindow *ui;
    void showBand(QList<QString> band);
    QList<struct state> states;
    QList<struct function> functions;
    struct state currentState;
    baender *b;
    int m_pause;
    void readFunctions();
};

#endif // MAINWINDOW_H
