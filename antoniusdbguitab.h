#ifndef ANTONIUSDBGUITAB_H
#define ANTONIUSDBGUITAB_H

#include <QTabWidget>
#include "dbinterface.h"

namespace Ui {
class AntoniusDBGUITab;
}

class AntoniusDBGUITab : public QTabWidget
{
    Q_OBJECT

public:
    explicit AntoniusDBGUITab(DBInterface *dbInterface, QWidget *parent = nullptr);
    ~AntoniusDBGUITab();

    void ExitProgram(void);

/********************EVENT_HANDLERS********************/
    void keyPressEvent(QKeyEvent *event);


private slots:
    void on_exitButton_clicked();

private:
    Ui::AntoniusDBGUITab *ui;
};

#endif // ANTONIUSDBGUITAB_H
