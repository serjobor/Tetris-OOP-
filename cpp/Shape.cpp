#include "Shape.h"

I::I()
{
	active_square = { 1,3,5,7 };
}

Z::Z()
{
	active_square = { 2,4,5,7 };
}

S::S()
{
	active_square = { 3,5,4,6 };
}

T::T()
{
	active_square = { 3,5,4,7 };
}

L::L()
{
	active_square = { 2,3,5,7 };
}

J::J()
{
	active_square = { 3,5,7,6 };
}

O::O()
{
	active_square = { 2,3,4,5 };
}

Coords* Shapes::changeZarray(Coords* z) 
{
	for (std::size_t i{}; i < active_square.size(); ++i) {
		z[i].setX(active_square[i] % 2);
		z[i].setY(active_square[i] / 2);
	}
	return z;
}
