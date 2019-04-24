#include <iostream>
#include "wallet.h"

Wallet::Wallet(){
	initializeWallet();
}

void Wallet::initializeWallet(){
	this->balance = 145.00;
}
void Wallet::setBalance(double newBalance){
	this->balance = newBalance;
}

double Wallet::getBalance(){
	return this->balance;
}
