#include "buchunghinzu.h"
#include "ui_buchunghinzu.h"

BuchungHinzu::BuchungHinzu(unsigned int remitterID, DBInterface *dbInterface,  QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BuchungHinzu)
{
    ui->setupUi(this);
    this->remitterID = remitterID;
    this->setWindowModality(Qt::ApplicationModal);	//block input to all other windows of this application
    this->dbInterface = dbInterface;
}

BuchungHinzu::~BuchungHinzu()
{
    delete ui;
}

/**
 * @brief BuchungHinzu::SetRemitterID Sets the remitterID
 * @param remitterID The new remitterID
 */
void BuchungHinzu::SetRemitterID(unsigned int remitterID)
{
    this->remitterID = remitterID;
}

/**
 * @brief keyReleaseEvent Overriden key event handler
 * @param keyEvent The key event to handle
 */
void BuchungHinzu::keyPressEvent(QKeyEvent *keyEvent)
{
    switch(keyEvent->key())
    {
    case Qt::Key_Return:
    case Qt::Key_Enter:
        CloseAccept();
        break;

    case Qt::Key_Escape:
        CloseReject();
        break;

    default:
        QDialog::keyPressEvent(keyEvent);
    }
}

/**
 * @brief BuchungHinzu::on_buttonOK_clicked Slot function for when the OK button is clicked
 */
void BuchungHinzu::on_buttonOK_clicked()
{
    CloseAccept();
}

/**
 * @brief BuchungHinzu::on_buttonCancel_clicked Slot function for when the Cancel button is clicked
 */
void BuchungHinzu::on_buttonCancel_clicked()
{
    CloseReject();
}

/**
 * @brief BuchungHinzu::CloseAccept Executes an SQL query to add a "Buchung" and closes the dialog box afterwards
 */
void BuchungHinzu::CloseAccept()
{
    dbInterface->AddBuchung(remitterID, ui->dateEdit->date(), ui->doubleSpinBox->value());
    this->accept();
}
/**
 * @brief BuchungHinzu::CloseReject() Closes the dialog box without any further action
 */
void BuchungHinzu::CloseReject()
{
    this->reject();
}
