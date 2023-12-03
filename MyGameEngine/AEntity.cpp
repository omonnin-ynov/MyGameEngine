#include "AEntity.h"
#include "Application.h"

MGE::AEntity::AEntity()
{
    _ID = Application::getInstance()->GenerateID();
    _name = "";
}

MGE::AEntity::AEntity(std::string name)
{
    _name = name;
    _ID = Application::getInstance()->GenerateID();
}

MGE::AEntity::AEntity(std::string name, float x, float y)
{
    _name = name;
    _ID = Application::getInstance()->GenerateID();
    this->setPosition(x, y);
}

void MGE::AEntity::Update(float deltaTime)
{
    for (AComponent* comp : _components) {
        comp->Update(deltaTime);
    }
}

void MGE::AEntity::LateUpdate(float deltaTime)
{
    for (AComponent* comp : _components) {
        comp->LateUpdate(deltaTime);
    }
}

std::vector<MGE::AComponent*>* MGE::AEntity::getComponents()
{
    return &_components;
}

void MGE::AEntity::attachComponent(AComponent* component) 
{
    _components.push_back(component);
}

void MGE::AEntity::detachComponent(AComponent* component)
{
    auto it = std::find(_components.begin(), _components.end(), component);
    if (it != _components.end())
    {
        _components.erase(it);
    } else
    {
        std::cerr << "warning: AEntity::DetachComponent : component not found\n";
    }
}

uint64_t MGE::AEntity::getID()
{
    return _ID;
}

std::string MGE::AEntity::getName() const
{
    return _name;
}

void MGE::AEntity::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform.combine(this->getTransform());

    for (AComponent* component : _components) {
        auto drawableComponent = dynamic_cast<sf::Drawable*>(component);

        if (drawableComponent) {
            target.draw(*drawableComponent, states);
        }
    }
}
/// <summary>
/// E
/// </summary>
/// <returns>E</returns>
std::string MGE::AEntity::E()
{
    return "E";
}
