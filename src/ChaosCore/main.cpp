#include "Window.h"

int main()
{
	using namespace Chaos;
	using namespace Core;

	Window window("Chaos Engine", 960, 540);
	glClearColor(0.2f, 0.3f, 0.8f, 1.0f);


	while (!window.Closed())
	{
		window.Clear();

		if (window.IsKeyPressed(GLFW_KEY_A))
			std::cout << "A was pressed!" << std::endl;

		if (window.IsMouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT)) 
		{
			double x, y;
			window.GetMousePosition(x, y);
			std::cout << "Left mouse button was pressed at position " << x << ", " << y << std::endl;
		}

		glBegin(GL_QUADS);
		glVertex2f(-0.5f, -0.5f);
		glVertex2f(-0.5f, 0.5f);
		glVertex2f(0.5f, 0.5f);
		glVertex2f(0.5f, -0.5f);
		glEnd();

		window.Update();
	}

	return 0;
}



