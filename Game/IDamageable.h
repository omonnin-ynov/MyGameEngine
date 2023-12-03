#pragma once

namespace MGE
{
	class AEntity;
}

namespace ILM
{

	class IDamageable
	{
	protected:
		float _hp;
		float _damage;
	public:
		IDamageable(float hp, float damage) : _hp(hp), _damage(damage) {}
		virtual ~IDamageable() = default;

		virtual float getHp() const
		{
			return _hp;
		}

		void setHp(float hp)
		{
			_hp = hp;
		}

		/// \brief Makes the IDamageable entity/comp take damage
		/// \param parent entity that dealt damage
		/// \param damage the amount of damage received
		/// \return the amount of damage actually dealt
		virtual float takeDamage(MGE::AEntity* parent, float damage) = 0;

		virtual float getDamage() const
		{
			return _damage;
		}

		virtual void setDamage(float damage)
		{
			_damage = damage;
		}
	};
}
