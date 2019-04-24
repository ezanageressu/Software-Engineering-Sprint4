/**
* @file production.h
* @brief This header file contains functionalities to
* buy and sell wood and graphite.
*/

#ifndef PRODUCTION_H
#define PRODUCTION_H
#include "wallet.h"

/**
* @class Production
* @brief Class to implement production of the pencils
* @details We define the constructor, variables and
* necessary methods.
*/

class Production : public Wallet{

public:
    /**
    * Constructor.
    */
    Production();

    /**
    * Initializes class variables
    */
    void initializeProduction();

    /**
    * Price of Wood.
    */
    double priceofWood;

    /**
    * Price of Graphite.
    */
    double priceofGraphite;

    /**
    * Amount of wood.
    */
    double numberofWood;

    /**
    * Amount of graphite.
    */
    double numberofGraphite;

    /**
    * Buy wood function.
    */
    void buyWood();

    /**
    * Buy graphite function.
    */
    void buyGraphite();

    /**
    * Disable buy wood function.
    */
    bool disable_buyWood();

    /**
    * Disable buy graphite function.
    */
    bool disable_buyGraphite();

    /**
    * Calculates price of wood and
    * graphite function.
    */
    void calculatePrices();

    /**
    * Consumes wood function.
    */
    void decreaseWood();

    /**
    * Consume graphite function.
    */
    void decreaseGraphite();

    /**
    * return number of wood.
    */
    double getWood();

    /**
    * return number of graphite.
    */
    double getGraphite();
};

#endif // PRODUCTION_H
