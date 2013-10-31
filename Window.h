#ifndef TURTLE_WINDOW
#define TURTLE_WINDOW
#include <vector>
#include <mutex>
#include <thread>

//third party
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "Drawable.h"
#include "guarded_thread.h"

namespace Turt{

	class window{
	public:
		window(int length, int height) :
			window_resources{},
			Length{ length },
			Height{ height },
			draw_stack{},
			window_ptr{ nullptr }, //delayed till construction in thread.
			window_loop_thread{ &window::window_loop, this }
		{}

		void add_drawable(const Drawable_ref& ref){
			std::unique_lock<std::mutex> lck(window_resources);
			draw_stack.push_back(ref);
		}

	private:
		void window_loop();

		void handle_window_events(sf::RenderWindow&);
		void draw_drawables(sf::RenderWindow&, Graphics&);
		void animate_window(sf::RenderWindow&, Graphics&);

		std::mutex window_resources;
		int Length;
		int Height;
		std::vector<Drawable_ref> draw_stack;

		//delay construction to bind member function to new thread
		std::unique_ptr<sf::RenderWindow> window_ptr;
		guarded_thread window_loop_thread;
	};
}




#endif

