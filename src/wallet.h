/**
* @file wallet.h
* @brief This header file contains required definitions
* for Wallet. It only stores Balance which is the money
* the user has in the bank.
*/

#ifndef WALLET_H
#define WALLET_H

/**
* @class Wallet
* @brief Class to implement the wallet of the player
* @details We define the constructor, variables
* and necessary methods.
*/

class Wallet{
public:
    /**
    * Constructor.
    */
    Wallet();

    /**
    * Initializes class variables
    */
    void initializeWallet();

    /**
    * Balance in wallet.
    */
    double balance;

    /**
    * Sets the balance.
    */
    void setBalance(double newBalance);

    /**
    * Returns the balance.
    */
    double getBalance();
};

#endif // WALLET_H
