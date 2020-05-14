#include "antoniusdbguitab.h"
#include "ui_antoniusdbguitab.h"
#include <QKeyEvent>
#include <QIcon>

/********** include files for all the page widgets **********/
#include "abonnenten.h"
#include "abonnentensuche.h"


AntoniusDBGUITab::AntoniusDBGUITab(DBInterface *dbInterface, QWidget *parent) :
    QTabWidget(parent),
    ui(new Ui::AntoniusDBGUITab)
{
    ui->setupUi(this);
    this->setWindowTitle(APPLICATION_WINDOW_TITLE);
    windowIcon = QIcon("./resource/Antonius Icon big.jpg");
    this->setWindowIcon(windowIcon);
    this->addTab(new Abonnenten(dbInterface, this), QString("Abonnenten (F3)"));
    this->addTab(new AbonnentenSuche(dbInterface, this), QString("Abonnenten Suche (F4)"));
}

AntoniusDBGUITab::~AntoniusDBGUITab()
{
    delete ui;
}

/**
 * @brief Slot function for when the "X" in the right corner of the window is clicked
 */
void AntoniusDBGUITab::on_exitButton_clicked()
{
    this->ExitProgram();
}

/**
 * @brief Key Event Handler (overridden from base class)
 * @param event The key event, which is to be handled
 */
void AntoniusDBGUITab::keyPressEvent(QKeyEvent *event)
{
    int keyCode = event->key();
    switch(keyCode)
    {
    case Qt::Key_Escape:
        //this->ExitProgram();
        break;

    case Qt::Key_F1:
        break;

    case Qt::Key_F3:
        setCurrentIndex(ABONNENTEN_TAB);
        break;

    case Qt::Key_F4:
        setCurrentIndex(ABONNENTEN_SUCHE_TAB);
        break;

    case Qt::Key_F5:
        break;

    case Qt::Key_F6:
        break;

    case Qt::Key_F7:
        break;

    case Qt::Key_F8:
        break;

    case Qt::Key_F9:
        break;

    case Qt::Key_F10:
        break;

    case Qt::Key_F12:
        break;

    //all other events are processed by the base class's event handler
//    default:
//        QTabWidget::keyReleaseEvent(event); break;
    }
}

/**
 * @brief Exits the program and does some eventual cleanup
 */
void AntoniusDBGUITab::ExitProgram(void)
{
    QCoreApplication::quit();
}
