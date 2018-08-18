#include "Window.h"

namespace Chaos {
	namespace Core {

		void window_resize(GLFWwindow *window, const int width, const int height)
		{
			glViewport(0, 0, width, height);
		}

		void key_callback(GLFWwindow* window, const int key, int scancode, const int action, int mods)
		{
			const auto win = static_cast<Window*>(glfwGetWindowUserPointer(window));
			win->_keys[key] = action != GLFW_RELEASE;
		}

		void mouse_button_callback(GLFWwindow* window, const int button, const int action, int mods)
		{
			const auto win = static_cast<Window*>(glfwGetWindowUserPointer(window));
			win->_mouseButtons[button] = action != GLFW_RELEASE;
		}

		void cursor_position_callback(GLFWwindow* window, const double xpos, const double ypos)
		{
			const auto win = static_cast<Window*>(glfwGetWindowUserPointer(window));
			win->_mx = xpos;
			win->_my = ypos;
		}

		Window::Window(const char *title, const int width, const int height)
		{
			_title = title;
			_width = width;
			_height = height;
			if (!Init())
				glfwTerminate();

			for (auto& key : _keys)
			{
				key = false;
			}

			for (auto& mouse_button : _mouseButtons)
			{
				mouse_button = false;
			}
		}

		Window::~Window()
		{
			glfwTerminate();
		}

		bool Window::Init()
		{
			if (!glfwInit())
			{
				std::cout << "Failed to initialize GLFW!" << std::endl;
				return false;
			}
			_window = glfwCreateWindow(_width, _height, _title, nullptr, nullptr);
			if (!_window)
			{
				std::cout << "Failed to create GLFW window!" << std::endl;
				return false;
			}
			glfwMakeContextCurrent(_window);
			glfwSetWindowUserPointer(_window, this);
			glfwSetWindowSizeCallback(_window, window_resize);
			glfwSetKeyCallback(_window, key_callback);
			glfwSetMouseButtonCallback(_window, mouse_button_callback);
			glfwSetCursorPosCallback(_window, cursor_position_callback);

			if (glewInit() != GLEW_OK)
			{
				std::cout << "Failed to initialize GLEW!" << std::endl;
				return false;
			}

			std::cout << "OpenGL " << glGetString(GL_VERSION) << std::endl;
			return true;
		}

		bool Window::IsKeyPressed(const unsigned int keycode) const
		{
			if (keycode >= MAX_KEYS)
				return false;

			return _keys[keycode];
		}

		bool Window::IsMouseButtonPressed(unsigned int button) const
		{
			if (button >= MAX_BUTTONS)
				return false;

			return _mouseButtons[button];
		}

		void Window::GetMousePosition(double& x, double& y) const
		{
			x = _mx;
			y = _my;
		}

		void Window::Clear() const
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}

		void Window::Update()
		{
			glfwPollEvents();
			glfwSwapBuffers(_window);
		}

		bool Window::Closed() const
		{
			return glfwWindowShouldClose(_window) == 1;
		}
	}
}
