#include "pch.h"
#include "Observer.h"
#include "ObserverSourceMaking.h"
#include "Singleton.h"
#include "FactoryMethod.h"
#include "AbstractFactory.h"
#include "Decorator.h"
#include "Command.h"
#include "Strategy.h"
#include "Adapter.h"
#include "State.h"
#include "ChainOfResonsibility.h"
#include <iostream>

int main() {
	nsChainOfResponsibility::programTest();

	std::cout << "------ END MAIN ------ \n";
	return 0;
}

