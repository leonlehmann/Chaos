#pragma once

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace Chaos {
	namespace Core {

#define MAX_KEYS	1024
#define MAX_BUTTONS	32

		class Window
		{
		private:
			const char *_title;
			int _width, _height;
			GLFWwindow *_window;
			bool _closed;

			bool _keys[MAX_KEYS];
			bool _mouseButtons[MAX_BUTTONS];
			double _mx, _my;
		public:
			Window(const char *title, int width, int height);
			~Window();
			void Clear() const;
			void Update();
			bool Closed() const;

			inline int GetWidth() const { return _width; }
			inline int GetHeight() const { return _height; }

			bool IsKeyPressed(unsigned int keycode) const;
			bool IsMouseButtonPressed(unsigned int button) const;
			void GetMousePosition(double& x, double& y) const;
		private:
			bool Init();
			friend static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
			friend static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
			friend static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
		};
	}
}
