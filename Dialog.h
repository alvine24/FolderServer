#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "FolderServer.h"

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();
    
private slots:

    void on_buttonBox_clicked();

private:
    Ui::Dialog *ui;
    FolderServer myFolder;
};

#endif // DIALOG_H
