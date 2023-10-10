#pragma once
namespace MGE {
	class AComponent {
	protected:
		unsigned int _ID;
		unsigned int createID();

	public:
		AComponent();
		virtual void Awake();
		virtual void Start();
		virtual void Update();
		virtual void LateUpdate();
		unsigned int getID();
	};
}
