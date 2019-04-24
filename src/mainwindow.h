/**
* @file mainwindow.h
* @brief Main window functionality
*/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>

#include "pencil.h"
#include "production.h"
#include "wallet.h"
#include "intelligence.h"
#include "debug.h"
#include "server.h"


/**
 * @namespace Ui
 * @brief Getting MainWondow class from Ui namespace
 */

namespace Ui {
    class MainWindow;
}

/**
* @class MainWindow
* @brief Class to implement the MainWindow
* @details class MainWindow extending from QMainWindow
* uses Q_OBJECT macro defined in QMainWindow header
*/

class MainWindow : public QMainWindow, public Debug, public Server
{
    Q_OBJECT

public:
    /**
    * Constructor.
    */
    explicit MainWindow(QWidget *parent = nullptr);

    /**
    * Destructor.
    */
    ~MainWindow();

private slots:

    void gameStart();

    /**
    * Action taken when make pencil is clicked.
    */
    void on_makePencil_clicked();

    /**
    * Function that updates ui labels every second.
    */
    void runner();

    /**
    * Function to sell pencils continuously every second.
    */
    void seller();

    /**
    * Function to produce pencils continuously every second .
    */
    void apm2Seller();

    /**
    * Activates and runs Intelligence
    */
    void intelligenceRunner();

    /**
    * Function to calculate prices of graphite
    * and wood every 5 second.
    */
    void calculatePrices();

    /**
    * Function to check which buttons need to be disabled.
    */
    void checkbuttons();

    /**
    * APM Check.
    */
    bool apmCheck();

    /**
    * Disables late game ui components.
    */
    void disableComponents();

    /**
    * Action taken when buy wood is clicked.
    */
    void on_buyWood_clicked();

    /**
    * Action taken when buy graphite is clicked.
    */
    void on_buyGraphite_clicked();

    /**
    * Action taken when buy APM is clicked.
    */
    void on_buyApm_clicked();

    /**
    * Action taken when increase price is clicked.
    */
    void on_increasePencil_clicked();

    /**
    * Action taken when decrease price is clicked.
    */
    void on_decreasePencil_clicked();

    /**
    * Action taken when upgrade APM is clicked.
    */
    void on_upgradeApm_clicked();

    /**
    * Action taken when unlock Marketing is clicked.
    */
    void on_unlockMarketing_clicked();

    /**
    * Action taken when upgrade Marketing is clicked.
    */
    void on_upgradeMarketing_clicked();

    /**
    * Activates Intelligence functionality if criteria are met.
    */
    bool activateIntelligence();

    /**
    * Activates Marketing functionality if criteria are met.
    */
    void unlockMarketing();

    /**
    * Save game functionality.
    */
    void save();

    /**
    * Load game functionality.
    */
    void load();

    /**
    * Displays the debug button.
    */
    void displayDebugButton();

    /**
    * Calls speedUp() from Debug class.
    */
    void debug();

    /**
    * Action taken when game is started from main page.
    */
    void on_startGame_clicked();

    /**
    * Action taken when game is loaded from main page.
    */
    void on_loadGame_clicked();

    /**
    * Action taken when game is quit.
    */
    void on_quit_clicked();

    /**
    * Acquires high scores from server and displays on main page.
    */
    void getHighScore();

private:
    /**
    * Ui.
    */
    Ui::MainWindow *ui;
    QTimer *timer5s;
    QTimer *timer;
};

#endif // MAINWINDOW_H
