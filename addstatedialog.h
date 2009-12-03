#ifndef ADDSTATEDIALOG_H
#define ADDSTATEDIALOG_H

#include <QDialog>
#include "state.h"
namespace Ui {
    class addStateDialog;
}

class addStateDialog : public QDialog {
    Q_OBJECT
signals:
    void stateAdded(struct state);
private slots:
    void ok();
public:
    addStateDialog(QWidget *parent = 0);
    ~addStateDialog();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::addStateDialog *ui;
};

#endif // ADDSTATEDIALOG_H
