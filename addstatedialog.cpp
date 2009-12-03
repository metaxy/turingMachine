#include "addstatedialog.h"
#include "ui_addstatedialog.h"

addStateDialog::addStateDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addStateDialog)
{
    ui->setupUi(this);
    connect(ui->pushButton_ok,SIGNAL(clicked()),this,SLOT(ok()));
    connect(ui->pushButton_ok,SIGNAL(clicked()),this,SLOT(close()));
    connect(ui->pushButton_cancel,SIGNAL(clicked()),this,SLOT(close()));
}

addStateDialog::~addStateDialog()
{
    delete ui;
}
void addStateDialog::ok()
{
    struct state s;
    s.name = ui->lineEdit_stateName->text();
    s.type = ui->comboBox_type->currentIndex();
    emit stateAdded(s);
}

void addStateDialog::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}
