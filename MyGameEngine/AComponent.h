#pragma once
#include <string>

namespace MGE {
	class AComponent {
	protected:
		unsigned int _ID;
		unsigned int createID();
		std::string name;

	public:
		AComponent(std::string name);
		virtual void Awake();
		virtual void Start();
		virtual void Update();
		virtual void LateUpdate();
		unsigned int getID();
	};
}
