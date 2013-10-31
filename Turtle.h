#ifndef TURTLE_TURTLE
#define TURTLE_TURTLE

#include <memory>
#include <mutex>
#include <chrono>

//Drawable details
#include "Drawable.h"
#include "Canvas.h"
#include "Units.h"

namespace Turt {

class Turtle{
public:
	Turtle(
		Canvas& can, 
		point init_position,
		//Speed init_speed = -1.0,
		Degrees init_angle = 0.0 ) :

		canvas{ can },
		position(init_position),
		//speed{init_speed},
		Angle{init_angle},	
		
		turtle_resource{},

		turtle_image{ "TurtleAlpha.png" }, //TODO: Magic literal
		bPenDown{ true }
	{}

	void forward(Units distance){
		point old_position = position;
		//if (speed <= 0){ //negative values are unbounded speeds.
			std::lock_guard<std::mutex> lck{ turtle_resource };
			position.x += distance * cosD(Angle);
			position.y += distance * sinD(Angle);
		//}
		/*else{ //use speed
		  typedef std::chrono::high_resolution_clock Time;
		  typedef std::chrono::duration<Units> Units_seconds;

		  Units dt = 0;
		  Units dx = 0;
		  Units elapsed_distance = 0;
		  do{	
			auto Initial = Time::now();
		
			std::lock_guard<std::mutex> lck{ turtle_resource };
			Units dx = dt*speed;		
			position.x += dx*cosD(Angle);
			position.y += dx*sinD(Angle);

			auto Final = Time::now();

	        dt = Units_seconds{ Final - Initial }.count();

	        elapsed_distance += dx;
	      }while (elapsed_distance < distance);
	  }*/

		if (bPenDown){
			//std::lock_guard<std::mutex> lck{ turtle_resource };
			canvas.draw_line(old_position, position);
		}

	}
	
	void right(Degrees angle){
		std::lock_guard<std::mutex> lck{ turtle_resource };
		Angle += angle;
		Angle = fmod(Angle, 360.0);
	}
	
	void left(Degrees angle){
		right(-angle);
	}
	void PenDown(){ 
		std::lock_guard<std::mutex> lck{ turtle_resource };
		bPenDown = true; 
	}
	void PenUp(){
		std::lock_guard<std::mutex> lck{ turtle_resource };
		bPenDown = false;
	}

	friend void draw(Turtle& t, Graphics& graphics){
		std::lock_guard<std::mutex> lck{ t.turtle_resource };

		t.turtle_image.set_position(t.position);
		t.turtle_image.set_rotation(t.Angle);
		graphics.draw_Image(t.turtle_image);
	}

private:	
	
	Canvas& canvas;
	point position;
	//Speed speed;
	Degrees Angle;

	std::mutex turtle_resource;

	image turtle_image;
	bool bPenDown;
};


}

#endif