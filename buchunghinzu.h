#ifndef BUCHUNGHINZU_H
#define BUCHUNGHINZU_H

#include <QDialog>
#include <QKeyEvent>
#include "dbinterface.h"

namespace Ui {
class BuchungHinzu;
}

class BuchungHinzu : public QDialog
{
    Q_OBJECT

public:
    explicit BuchungHinzu(unsigned int remitterID, DBInterface *dbInterface, QWidget *parent = nullptr);
    ~BuchungHinzu();

    void SetRemitterID(unsigned int remitterID);
    void CloseAccept(void);
    void CloseReject(void);

    void keyPressEvent(QKeyEvent *keyEvent);

private slots:

    void on_buttonOK_clicked();
    void on_buttonCancel_clicked();

private:
    Ui::BuchungHinzu *ui;
    unsigned int remitterID;
    DBInterface *dbInterface;

};

#endif // BUCHUNGHINZU_H
