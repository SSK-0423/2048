#pragma once
#include "Framework/IComponent.h"

namespace Game2048
{
	class Tile : public Framework::IComponent
	{
	public:
		Tile(Framework::Object* owner);
		~Tile() = default;

		void Update(float deltaTime) override;
		void Draw() override;
		void SetNumber(unsigned int number);
		void SetScale(float width, float height);
		void SetGridPosition(unsigned int x, unsigned int y, float gridLeft, float gridTop);
		unsigned int GetNumber();

	private:
		unsigned int m_number = 0;
		float m_width = 0;
		float m_height = 0;
	};
}