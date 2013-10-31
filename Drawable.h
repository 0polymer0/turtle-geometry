#ifndef TURTLE_DRAWABLE
#define TURTLE_DRAWABLE

//#include <mutex>
#include <memory>
#include <utility>
#include <string>
#include <stdexcept>
#include <iostream>
#include <mutex>
#include <SFML/Graphics.hpp>

#include "Units.h"

namespace Turt{


struct point{ 
	Coordinate x;
	Coordinate y;
};

struct line{
	point first;
	point second;
};

class image{
public:
	image(std::string file_name) :
		image_resource_{},
		_tex{},
		_frame{} {
			_tex.loadFromFile(file_name);
			_tex.setSmooth(true);
			_frame.setTexture(_tex);
	}
	image(const image& rhs) :
		image_resource_{},
		_tex{ rhs._tex },
		_frame{ rhs._frame }
	{}
	const image& operator=(const image& rhs){
		std::lock_guard<std::mutex> lk{ image_resource_ };
		_tex = rhs._tex;
		_frame = rhs._frame;
	}

	void set_position(point new_position){
		std::lock_guard<std::mutex> lk{ image_resource_ };
		float x = static_cast<float>( new_position.x ); //TODO: fix broken cast
		float y = static_cast<float>( new_position.y );
		_frame.setPosition(sf::Vector2f(x, y));
	}
	void set_rotation(Degrees new_rotation){
		std::lock_guard<std::mutex> lk{ image_resource_ };
		float degree = static_cast<float>(new_rotation);
		_frame.setRotation(degree);
	}
	float get_height(){
		 sf::FloatRect rectangle = _frame.getGlobalBounds();
		 return rectangle.height;
	}
	explicit operator sf::Sprite(){
		std::lock_guard<std::mutex> lk{ image_resource_ };
		_frame.setTexture(_tex);
		return _frame;
	}
private:
	std::mutex image_resource_;
	sf::Texture _tex;
	sf::Sprite _frame;
};

class Graphics{
public:
	Graphics(int width, int height) : //TODO: Default renderTexture sufficient
		graphics_resources{},
		images{},
		lines{},
		render_texture{}{
			if (!render_texture.create(width, height)){
				throw std::runtime_error{ "render texture failed to create in Graphics." };
			}	
	}
	
	void draw_Image(image drawn_image){
		//std::unique_lock<std::mutex> lock( graphics_resources );
		images.push_back(drawn_image);//Not enough info, also need location
	}

	void draw_Line(line drawn_line){
		lines.push_back(to_vertex(drawn_line.first));
		lines.push_back( to_vertex( drawn_line.second ) );
	}

	void draw_Lines( const std::vector<line>& drawn_lines){
		//std::unique_lock<std::mutex> lck{ graphics_resources };
		//auto Begin = drawn_lines.begin();
		//auto End = drawn_lines.end();
		//for (; Begin != End; ++Begin)
		//	draw_Line(*Begin);
		for ( line l : drawn_lines)
		 	draw_Line(l);
	}

	//TODO::There is no record of ordering, buffering is hard...
	sf::Sprite render_Graphics(){
		//std::unique_lock<std::mutex> lck{ graphics_resources };

		render_texture.clear(sf::Color::White);
		
		//draw buffer
		render_texture.draw(lines.data(), lines.size(), sf::Lines);
		for (image img : images){
			render_texture.draw(sf::Sprite( img ));
		} 
		
		render_texture.display();

		const sf::Texture& texture = render_texture.getTexture();
		lines.clear(); //refresh buffer
		images.clear();
		return sf::Sprite{ texture };
	}
private:
	sf::Vertex to_vertex(point p){
		float x = static_cast<float>(p.x);
		float y = static_cast<float>(p.y);
		return sf::Vertex{
			     sf::Vector2f{ x, y },
			     sf::Color::Black
		       };
	}
	std::mutex graphics_resources;
	std::vector<image> images;
	std::vector<sf::Vertex> lines;
	sf::RenderTexture render_texture;
};

class Drawable_ref{
public:
	template<typename T>
	Drawable_ref(T& x) : 
		//polymorphic_resource{},
		self_{ std::make_shared<model<T>>(&x) }{}
	//template<typename T>
	//Drawable_ref(const T& x) = delete;
	friend void draw(const Drawable_ref& dr, Graphics& g){
	//	std::unique_lock<std::mutex> {dr.polymorphic_resource};
		dr.self_->draw_(g);
	}

private:
	struct concept{
		virtual ~concept() = default;
		virtual void draw_(Graphics&)const = 0;
	};
	template<typename T>
	struct model : concept{
		model(T* x) : 	
			//polymorphic_resource{},
			data_{ x } {}

		void draw_(Graphics& g) const{	
          //  std::unique_lock<std::mutex> lck(polymorphic_resource);
			
			draw(*data_, g);
		}

		//mutable std::mutex polymorphic_resource;
		T* data_;
	};

	//mutable std::mutex polymorphic_resource;
	std::shared_ptr<const concept> self_;
};

}

#endif