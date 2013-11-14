#ifndef TURTLE_CANVAS
#define TURTLE_CANVAS

#include <mutex>
#include <vector>
#include <memory>

#include "Drawable.h"
#include "Units.h"

namespace Turt{

class Canvas{
public:

	void draw_line(
	  point first,
	  point second){		
	  line new_line = { first, second };

	  std::lock_guard<std::mutex> lck{canvas_resource};
	  lines.push_back(new_line);
	}

	void draw(
	  Graphics& graphics) const{

	  std::lock_guard<std::mutex> lck{ canvas_resource };
	  graphics.draw_Lines( lines );
	}

private:
	mutable std::mutex canvas_resource;
	std::vector<line> lines;
};


}
#endif
