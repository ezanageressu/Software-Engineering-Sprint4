/**
* @file intelligence.h
* @brief Intelligence currency implentation
* and functionalities
*/

#ifndef INTELLIGENCE_H
#define INTELLIGENCE_H

/**
* @class Intelligence
* @brief Class to implement Intelligence currency
* @details We define the constructor and necessary methods.
*/

class Intelligence{
public:
    /**
    * Constructor.
    */
    Intelligence();

    /**
    * Initializes class variables
    */
    void initializeIntelligence();

    /**
    * Amount of Intelligence
    */
    int intelligenceBalance;

    /**
    * Intelligence status (active/inactive)
    */
    bool intelligenceIsActive;

    /**
    * Insert your comment here.
    */
    void increaseIntelligence();
};


#endif // INTELLIGENCE_H
