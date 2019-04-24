/**
* @file pencil.h
* @brief this header file contains the functionalities for
* buying and selling pencil and the Auto Pencil Machine (APM).
*/

#ifndef PENCIL_H
#define PENCIL_H
#include "production.h"
#include "wallet.h"
#include "intelligence.h"

/**
* @class Pencil
* @brief Class to implement pencil game
* @details We define the constructor, variables and
* necessary methods.
*/

class Pencil : public Production, public Intelligence
{
public:
    /**
    * Constructor.
    */
    Pencil();

    /**
    * Initializes class variables
    */
    void initializePencil();

    /**
    * Returns pencils in invertory.
    */
    int getInventory();

    /**
    * Produce pencils.
    */
    void producePencil();

    /**
    * Price of pencil.
    */
    double priceofPencil;

    /**
    * Sell rate of pencil.
    */
    double rateofPencil;

    /**
    * Number of pencil produced.
    */
    int numberofPencil;

    /**
    * Total number of pencil produced.
    */
    double totalnumberofPencil;

    /**
    * Pencils for upgrade.
    */
    int pencilsForUpgrade;

    /**
    * Increase price of pencil.
    */
    void increasePrice();

    /**
    * Decrease price of pencil.
    */
    void decreasePrice();

    /**
    * Sells pencil.
    */
    void sell();

    /**
    * New rate of pencil sells.
    */
    void newRate();

    /**
    * Number of APMs.
    */
    double numberofApm;

    /**
    * Price of APMs.
    */
    double priceofApm;

    /**
    * Rate of APMs.
    */
    double rateofApm;

    /**
    * APM fractional.
    */
    double apmFractional;

    /**
    * Price of APM.
    */
    int apmUpgradePrice;

    /**
    * APM upgrade availability.
    */
    bool apmUpgradeAvailable;

    /**
    * Buy APM.
    */
    void buyApm();

    /**
    * APM 2000.
    */
    void apm2000();

    /**
    * Upgrade of APM.
    */
    void upgradeApm();

    /**
    * Function to round number to 2 decimal places.
    */
    double round(double var);

    /**
    * Marketing price.
    */
    int marketing;

    /**
    * Marketing price upgrade.
    */
    double marketingUpgradePrice;

    /**
    * Marketing functionality (active/inactive)
    */
    bool marketingUnlocked;

    /**
    * Function to upgrade market.
    */
    void upgradeMarketing();
};

#endif // PENCIL_H
