#include "AEntity.h"

MGE::AEntity::AEntity(std::string name)
{
	_name = name;
	_ID = 0;
}

void MGE::AEntity::Awake()
{
}

void MGE::AEntity::Start()
{
}

void MGE::AEntity::Update()
{
}

void MGE::AEntity::LateUpdate()
{
}

const std::list<MGE::AComponent> MGE::AEntity::getComponents()
{
	return this->_components;
}

void MGE::AEntity::attachComponent(AComponent component) 
{
	_components.push_back(component);
}

unsigned int MGE::AEntity::getID()
{
	return 0;
}

void MGE::AEntity::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
}

std::string MGE::AEntity::E()
{
	return "E";
}
