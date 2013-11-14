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
      Degrees init_angle = 0.0 ) :

	  canvas{ can },
	  position(init_position),
	  Angle{init_angle},	

      turtle_image{ "TurtleAlpha.png" }, //TODO: Magic literal
	  bPenDown{ true }
	{}

	void draw(Graphics& graphics) const{
	  graphics.draw_Image(turtle_image);
	}

	void forward(Units distance){
	  point old_position = position;
	  position.x += distance * cosD(Angle);
      position.y += distance * sinD(Angle);
	
	  if (bPenDown)
	    canvas.draw_line(old_position, position);
	
	  turtle_image.set_position(position);
	}
	
	void right(Degrees angle){
	  Angle += angle;
	  Angle = fmod(Angle, 360.0);
	  turtle_image.set_rotation(Angle);
	}
	
	void left(Degrees angle){
	  right(-angle);
	}
	void PenDown(){ 	
	  bPenDown = true; 
	}
	void PenUp(){
	  bPenDown = false;
	}

private:	
	Canvas& canvas;
	point position;
	Degrees Angle;

	image turtle_image;
	bool bPenDown;
};

}

#endif
