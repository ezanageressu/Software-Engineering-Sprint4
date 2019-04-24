/**
* @file debug.h
* @brief This header file contains functionalities to
* debug the game.
*/

#ifndef DEBUG_H
#define DEBUG_H

/**
* @class Debug
* @brief Class to implement Debug functionality
* @details We define the constructor, destructor
* and necessary methods.
*/

class Debug: public Pencil {

public:
    /**
    * Constructor.
    */
    Debug();

    /**
     * Function to speed up the specified values.
    */
    void speedUp();

};

#endif // DEBUG_H
