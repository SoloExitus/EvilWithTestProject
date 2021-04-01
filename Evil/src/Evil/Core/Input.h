#pragma once

#include <glm/glm.hpp>

#include "Evil/Core/KeyCodes.h"
#include "Evil/Core/MouseCodes.h"

namespace Evil
{
	class Input
	{
	public:
		static bool IsKeyPressed(KeyCode key);

		static bool IsMouseButtonPressed(MouseCode button);
		static glm::vec2 GetMousePosition();
		static float GetMouseX();
		static float GetMouseY();
	
	};
}
