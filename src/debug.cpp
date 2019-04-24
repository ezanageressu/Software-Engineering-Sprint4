#include "pencil.h"
#include "production.h"
#include "wallet.h"
#include "debug.h"

Debug::Debug(){}

void Debug::speedUp(){
    Wallet::balance = this->balance + 1000;
    Pencil::numberofPencil = this->numberofPencil + 1000;
    Pencil::totalnumberofPencil = this->totalnumberofPencil + 1000;
    Production::numberofWood = this->numberofWood + 10;
    Production::numberofGraphite = this->numberofGraphite + 10;
}
