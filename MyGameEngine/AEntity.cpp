#include "AEntity.h"

MGE::AEntity::AEntity(std::string name)
{
	_name = name;
	_ID = 0;
}

unsigned int MGE::AEntity::getID()
{
	return 0;
}

std::string MGE::AEntity::E()
{
	return "E";
}
