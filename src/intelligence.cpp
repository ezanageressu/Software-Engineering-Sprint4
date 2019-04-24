#include <iostream>
#include "intelligence.h"

Intelligence::Intelligence(){
	initializeIntelligence();
}

void Intelligence::initializeIntelligence(){
    this->intelligenceIsActive = false;
    this->intelligenceBalance = 250;
}

void Intelligence::increaseIntelligence(){
/** Prevent Intelligence from exceeding 200 */
    if(this->intelligenceBalance<200){
        this->intelligenceBalance++;
    }
}

