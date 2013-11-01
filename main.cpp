
#include <iostream>
#include <memory>
#include <string>
#include <chrono>
#include <thread>


#include "Turtle.h"
#include "Drawable.h"
#include "window.h"
using namespace Turt;

namespace{

using namespace std;
using namespace std::chrono;

void wait(milliseconds milli_sec){
	this_thread::sleep_for(milli_sec);
}

template<typename Function>
void Repeat(Units n, Function f){
	int i = static_cast<int>(round(n));
	while(--i)
		f();
}

void ArcL (Turtle& t, Units R, Degrees Deg){
	Repeat(Deg, [&]{
		t.forward(R);
		t.left(1);
	});
}

void ArcR (Turtle& t, Units R, Degrees Deg){
	Repeat(Deg, [&]{
		//wait(milliseconds{ 10 });
		t.forward(R);
		t.right(1);
	});
}

void Thing(Turtle& t){
	t.forward(100);
	t.right(90);
	t.forward(100);
	t.right(90);
	t.forward(50);
	t.right(90);
	t.forward(50);
	t.right(90);
	t.forward(100);
	t.right(90);
	t.forward(25);
	t.right(90);
	t.forward(25);
	t.right(90);
	t.forward(50);
}

void Circle(Turtle& t){
	Repeat(360,[&]{
	//while (true){
		t.forward(3);
		t.right(1);
		//wait(milliseconds{ 2 });
	//}
	});
}

void Circles(Turtle& t){
	Repeat(9, [&]{
		wait(milliseconds{ 2 });
		ArcR(t, 2, 360);
		t.right(40);
	});
}

void Petal(Turtle& t, Units size){
	ArcR(t, size, 60);
	t.right(120);
	ArcR(t, size, 60);
	t.right(120);
}

void Flower(Turtle& t, Units size){
	Repeat(6,[&]{
		Petal(t, size);
		t.right(60);
	});
}

void Poly(Turtle& t, Units side, Degrees angle){
	int intAngle = static_cast<int>(angle);
	int i = 0;
	do{
		t.forward(side);
		t.right(angle);
		i++;
	}while(i*intAngle % 360 != 0);
}

void NewPoly(Turtle& t, Units side, Degrees angle){
	int m = static_cast<int>(angle);
	Units cycle = static_cast<Units>(zeroDivisor(3*m, 360));
	Repeat(cycle, [&]{
		t.forward(side);
		t.right(angle);
		t.forward(side);
		t.right(2*angle);
	});
}

void recursePoly(Turtle& t, Units side, Degrees angle, int current = 0){
	t.forward(side);
	t.right(angle);

	current += static_cast<int>(angle);
	if (!(current % 360)) return;

	recursePoly(t, side, angle, current);
}

void Polyspi (Turtle& t, Units side, Degrees angle, Units inc, int limit){
	if(!limit) return;
	--limit;
	t.forward(side);
	t.right(angle);
	Polyspi(t, side + inc, angle, inc, limit);
}

void InSpi(Turtle& t, Units side, Degrees angle, Units inc, int iterations){
	int i = iterations;
	while(--i){
		t.forward(side);
		t.right(angle);
		angle += inc;
	}
}

void tree(Turtle& t, Units r){
    if (r < 5){
        t.forward(r);
        t.forward(-r);
	}
	else{
        t.forward(r / 3.0);
        t.left(30);
        tree(t, r * 2.0 / 3.0);
        t.right(30);
        t.forward(-r / 3.0);
 
        t.forward(r / 2.0);
        t.right(25);
        tree(t, r / 2.0);
        t.left(25);
        t.forward(- r / 2.0);
         
        t.forward(r * 5 / 6.0);
        t.right(25);
        tree(t, r / 2.0);
        t.left(25);
        t.forward(-r * 5 / 6.0);
	}
}

}

int main(){
	const int screen_width = 800;
	const int screen_height = 600;
	Canvas can{};
	point first_point = { screen_width / 2, screen_height };
	Turtle t{ can, first_point, 270};
	window win(screen_width, screen_height); //clear what the dependece is
	
	win.add_drawable(can);
	win.add_drawable(t);

	tree(t, 400);

}
