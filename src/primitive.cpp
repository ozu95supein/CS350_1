#include "primitive.hpp"

primitive::primitive(P_TYPE p)	//constructor that will make primitives based on the type that is passed
{
	enum P_TYPE { E_POINT = 0, E_LINE = 1, E_TRIANGLE = 2, E_PLANE = 3, E_AABB = 4, E_SPHEREDISC = 5 };

	switch (p)
	{
	case E_POINT:

		break;
	case E_LINE:

		break;
	case E_TRIANGLE:

		break;
	case E_PLANE:

		break;
	case E_AABB:

		break;
	case E_SPHEREDISC:

		break;
	}
}
primitive::~primitive()
{

}