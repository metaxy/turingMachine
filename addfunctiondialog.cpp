#include "addfunctiondialog.h"
#include "ui_addfunctiondialog.h"
#include <QtCore/QStringList>
addFunctionDialog::addFunctionDialog(QWidget *parent) :
    QDialog(parent),
    m_ui(new Ui::addFunctionDialog)
{
    m_ui->setupUi(this);
    connect(m_ui->pushButton_ok,SIGNAL(clicked()),this,SLOT(ok()));
    connect(m_ui->pushButton_ok,SIGNAL(clicked()),this,SLOT(close()));
    connect(m_ui->pushButton_cancel,SIGNAL(clicked()),this,SLOT(close()));
}

addFunctionDialog::~addFunctionDialog()
{
    delete m_ui;
}
void addFunctionDialog::setStates(QList<struct state> states)
{
    m_ui->comboBox_next->clear();
    m_ui->comboBox_state->clear();
    QStringList s;
    for(int i = 0;i<states.size();i++)
    {
        s << states.at(i).name;
    }
    m_ui->comboBox_state->insertItems(0,s);
    m_ui->comboBox_next->insertItems(0,s);
}
void addFunctionDialog::ok()
{
    struct function f;
    f.input = m_ui->lineEdit_input->text();
    f.output = m_ui->lineEdit_output->text();
    f.move = m_ui->comboBox_move->currentText();
    f.next = m_ui->comboBox_next->currentText();
    f.state = m_ui->comboBox_state->currentText();
    emit functionAdded(f);
}
void addFunctionDialog::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        m_ui->retranslateUi(this);
        break;
    default:
        break;
    }
}
