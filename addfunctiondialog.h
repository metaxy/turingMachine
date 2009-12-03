#ifndef ADDFUNCTIONDIALOG_H
#define ADDFUNCTIONDIALOG_H

#include <QtGui/QDialog>
#include "function.h"
#include "state.h"
namespace Ui {
    class addFunctionDialog;
}

class addFunctionDialog : public QDialog {
    Q_OBJECT
    public slots:
    void ok();
public:
    addFunctionDialog(QWidget *parent = 0);
    ~addFunctionDialog();
    void setStates(QList<struct state> states);
protected:
    void changeEvent(QEvent *e);

private:
    Ui::addFunctionDialog *m_ui;
signals:
    void functionAdded(struct function f);
};

#endif // ADDFUNCTIONDIALOG_H
