#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "baender.h"
#include "addfunctiondialog.h"
#include "addstatedialog.h"
#include <QtDebug>
#include <QTimer>
#include <QMessageBox>
#include <QFileDialog>
#include <QDir>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->actionAdd_Function,SIGNAL(triggered()),this,SLOT(addFunction()));
    connect(ui->actionAdd_State,SIGNAL(triggered()),this,SLOT(addState()));
    connect(ui->actionStart,SIGNAL(triggered()),this,SLOT(start()));
    connect(ui->actionBeenden,SIGNAL(triggered()),this,SLOT(close()));
    connect(ui->pushButton_addNewLeft,SIGNAL(clicked()),this,SLOT(addNewLeft()));
    connect(ui->pushButton_addNewRight,SIGNAL(clicked()),this,SLOT(addNewRight()));
    connect(ui->actionSpeichern,SIGNAL(triggered()),this,SLOT(saveMachine()));
    connect(ui->actionLaden,SIGNAL(triggered()),this,SLOT(loadMachine()));
    QStringList alph;
    alph << "1" << "2";
    b = new baender(alph,"#");
    b->showBand(ui->listWidget_band);
    m_pause = 500;
}
void MainWindow::showBand(QList<QString> band)
{
    ui->listWidget_band->clear();
    ui->listWidget_band->insertItems(0,band);
}
void MainWindow::addFunction()
{
    addFunctionDialog *dialog = new addFunctionDialog(this);
    connect(dialog,SIGNAL(functionAdded(struct function)),this,SLOT(addFunction(struct function)));
    dialog->setStates(states);
    dialog->show();
    dialog->exec();
}
void MainWindow::addState()
{
    addStateDialog *dialog = new addStateDialog(this);
    connect(dialog,SIGNAL(stateAdded(struct state)),this,SLOT(addState(struct state)));
 //   dialog->setStates(states);
    dialog->show();
    dialog->exec();
}

void MainWindow::addFunction(struct function f)
{
    functions << f;
    const int current = ui->tableWidget_functions->rowCount();
    ui->tableWidget_functions->insertRow(current);

    QTableWidgetItem *stateItem = new QTableWidgetItem(f.state);
    ui->tableWidget_functions->setItem(current,0,stateItem);

    QTableWidgetItem *inputItem = new QTableWidgetItem(f.input);
    ui->tableWidget_functions->setItem(current,1,inputItem);

    QTableWidgetItem *outputItem = new QTableWidgetItem(f.output);
    ui->tableWidget_functions->setItem(current,2,outputItem);

    QTableWidgetItem *moveItem = new QTableWidgetItem(f.move);
    ui->tableWidget_functions->setItem(current,3,moveItem);

    QTableWidgetItem *nextItem = new QTableWidgetItem(f.next);
    ui->tableWidget_functions->setItem(current,4,nextItem);
}
void MainWindow::addState(struct state s)
{
    states << s;
    showStates();
}
void MainWindow::showStates()
{
    QStringList s;
    for(int i = 0;i<states.size();i++)
    {
        s << states.at(i).name;
    }
    ui->listWidget_states->clear();
    ui->listWidget_states->insertItems(0,s);
}
void MainWindow::start()
{
    //find the start state
    readFunctions();
    bool foundStartState = false;
    for(int i = 0;i<states.size();i++)
    {
        if(states.at(i).type == 1)
        {
            currentState = states.at(i);
            foundStartState = true;
            break;
        }
    }
    if(foundStartState == false)
    {
        QMessageBox::critical(this, tr("Error"),tr("No start state found."));
        //error box
        return;
    }

    bool foundEndState = false;
    for(int i = 0;i<states.size();i++)
    {
        if(states.at(i).type == 2)
        {
            foundEndState = true;
            break;
        }
    }
    if(foundEndState == false)
    {
        QMessageBox::critical(this, tr("Error"),tr("No end state found."));
        return;
    }

    b->readBand(ui->listWidget_band);

    QTimer::singleShot(m_pause,this,SLOT(tick()));
    //tick
}
void MainWindow::tick()
{
    if(currentState.type == 2)
    {
        qDebug() << "end";
        return;
    }
    QString input = b->read();
    bool found=false;
    struct function ff;
    for(int i = 0;i<functions.size();i++)
    {
        struct function f = functions.at(i);
        if(f.state == currentState.name && input == f.input)
        {
            ff = f;
            found = true;
            break;
        }
    }
    if(found == false)
    {
        qDebug() << "dont found anything for the current state";
    }
    else
    {
        b->write(ff.output);
        b->move(ff.move);
        found = false;
        for(int i = 0;i<states.size();i++)
        {
            if(states.at(i).name == ff.next)
            {
                qDebug() << "found next state";
                currentState = states.at(i);
                found = true;
                break;
            }

        }
        b->showBand(ui->listWidget_band);
        if(found)
        {
            QTimer::singleShot(m_pause,this,SLOT(tick()));
        }
    }
}
void MainWindow::readFunctions()
{
    functions.clear();
    for(int i = 0;i < ui->tableWidget_functions->rowCount();i++)
    {
        struct function f;
        f.state = ui->tableWidget_functions->item(i,0)->text();
        f.input = ui->tableWidget_functions->item(i,1)->text();
        f.output = ui->tableWidget_functions->item(i,2)->text();
        f.move = ui->tableWidget_functions->item(i,3)->text();
        f.next = ui->tableWidget_functions->item(i,4)->text();
        functions << f;
    }
}
void MainWindow::addNewLeft()
{
      b->readBand(ui->listWidget_band);
      b->addNewLeft();
      b->showBand(ui->listWidget_band);
}

void MainWindow::addNewRight()
{
      b->readBand(ui->listWidget_band);
      b->addNewRight();
      b->showBand(ui->listWidget_band);
}

void MainWindow::saveMachine()
{
    QString fileName = QFileDialog::getSaveFileName(this,tr("Save Machine"),QDir::homePath(), tr("Machine (*.turing)"));
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        return;
    }
    QDataStream out(&file);
    QStringList state,input,output,move,next,stateName;
    QList<int> stateType;
    for(int i = 0;i<functions.size();++i)
    {
        state << functions.at(i).state;
        output << functions.at(i).output;
        input << functions.at(i).input;
        move << functions.at(i).move;
        next << functions.at(i).next;
    }
    for(int i = 0;i<states.size();++i)
    {
        stateName << states.at(i).name;
        stateType << states.at(i).type;

    }
    b->readBand(ui->listWidget_band);
    out << input << move << next << output << state << stateName << stateType << b->bAlph << b->current << b->hinten << b->leer << b->vorne ;
    file.close();
}
void MainWindow::loadMachine()
{
    QString fileName =  fileName = QFileDialog::getOpenFileName(this,tr("Open Machine"),QDir::homePath(), tr("Machine (*.turing)"));
    QFile file(fileName );
    if (!file.open(QIODevice::ReadOnly)) {
        return;
    }
    QDataStream in(&file);
    QStringList state,input,output,move,next,stateName;
    QList<int> stateType;
    in >> input >> move >> next >> output >> state >> stateName >> stateType >> b->bAlph >> b->current >> b->hinten >> b->leer >> b->vorne ;
    functions.clear();
    states.clear();
    for (int i=ui->tableWidget_functions->rowCount()-1; i >= 0; ++i)
        ui->tableWidget_functions->removeRow(i);

    for(int i = 0;i<input.size();i++)
    {
       struct function f;
       f.input = input.at(i);
       f.move = move.at(i);
       f.next = next.at(i);
       f.output = output.at(i);
       f.state = state.at(i);
       addFunction(f);
    }
    for(int i = 0;i<stateName.size();i++)
    {
       struct state s;
       s.name = stateName.at(i);
       s.type = stateType.at(i);
       states << s;
    }
    showStates();
    b->showBand(ui->listWidget_band);
}

MainWindow::~MainWindow()
{
    delete ui;
}
