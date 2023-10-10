// MyGameEngine.cpp : Defines the functions for the static library.
//

#include "pch.h"
#include "framework.h"


static unsigned int IDCounter = 0;

// TODO: This is an example of a library function
void fnMyGameEngine(){
}

static unsigned int makeID() {
	IDCounter++;
	return IDCounter - 1;
}
