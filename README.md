#My Game Engine

This engine is written in C++20 and supports a simplified version of the ECS. Entities can have components, but components cannot have components yet.

Features :

- Simplified ECS
- Engine management through Application class
- 2D SFML Integration
- Starting up an SFML Window
- Views with CameraComponent
- Automatic call of drawable components in update loop, scale with parent entity scale
- SpriteRendererComponent with a texture and sprite
- Input checking in Update in PlayerInput
- Box2D integration :
  - Instantiate a b2World
  - Synchronize physics world and graphical world in the update loop
  - RigidBodyComponent, ColliderComponent wrap b2Body and b2Fixture
  - Contact wrapper with ICollidable and CollisionListener
  - Collision filtering
- YAML integration
- Resource path manager
- Can add player characters, projectiles and enemies purely through config file
- Lua script integration with globally accessible lua_state to save on reloading scripts

Features I'd like to add:

- Components can have children components
- ECS paradigm with memory accesses optimized for locality
- Sprite center matches up with b2Body center (I attempted to do it, but the game refused to render when I did so)
- Better input integration
- GUI Components
- Sound
- Tilemap manager
- Fix the YAML warnings

#Vampire Survivors

The game is a simpler version of Vampire Survivors. I made that choice because Vampire survivors is a game that spawns and destroys many entities at all times.
This means that my engine needs to handle instantiation, deletion, and the update loop correctly. Failing that would mean a slow game, crashes or memory leaks.
I tested the game for 15 minutes and memory usage stays stable, which I'm rather proud of.

Currently the game creates the player character with some projectiles that spawn regularly from the player. The player can move with arrow keys.
Enemies also spawn all around the player from outside the viewport. Projectiles can damage and kill enemies, while enemies can damage and kill the player.
When the player dies, it's game over, although there's no proper end screen yet.

Features I'd like to add :

- HP bar
- Player takes damage from enemy contact
- Entity movement is handled through box2D rather than sfml
- Loss state (There's no win state to speak of in Vampire Survivors)
- Enemy wave manager
- Projectiles that bounce off of enemies and the screen boundary through calling the appropriate lua update function : luabridge::getGlobal(_luaState, "update" + projectileType);
- Randomly spawned items that change player stats or add projectiles

