#include <memory>


#include "window.h"

using namespace std;
using namespace sf;

void Turt::window::
handle_window_events(sf::RenderWindow& window){
	//unique_lock<mutex> lck(window_resources);
	Event event;
	while (window.pollEvent(event)){
		//pollEvent automatically moves window
		if (event.type == sf::Event::Closed)
			window.close();
	}
}

void Turt::window::
draw_drawables(sf::RenderWindow& window, Graphics& graphics){ 
	//if (!isDrawing) return;
	unique_lock<mutex> lck(window_resources);
	if (!draw_stack.empty()){
		for (const auto& drawItem : draw_stack){
			//draw(drawItem, graphics);
			drawItem.draw(graphics);
		}
	  sf::Sprite to_draw = graphics.render_Graphics();
	  window.draw(to_draw);
	}
}

void Turt::window::
animate_window(RenderWindow& window, Graphics& graphics){

	window.clear(sf::Color::Black);

	draw_drawables(window, graphics);
	
	window.display();

}

const int antialiasing_level = 8;
const string window_name = "Tort";
void Turt::window::
window_loop(){
	sf::Context context;
	Graphics graphics{Length, Height};
	ContextSettings settings;
	settings.antialiasingLevel = antialiasing_level;

	//initialize window
	//window needs to be constructed in the thread.
	//Delaying its construction makes it a pointer.
	window_ptr = 
	make_unique<RenderWindow>(
	  VideoMode(Length, Height),
	  window_name,
	  Style::Default,
	  settings
	);

	//Begin "Game Loop"
	while (window_ptr->isOpen()){
		handle_window_events(*window_ptr);
		animate_window(*window_ptr, graphics);
	}
	//unique_lock<mutex> lck(window_resources);
}



