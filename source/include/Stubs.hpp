#ifndef _STUBS_HPP
#define _STUBS_HPP

#include <Angle.hpp>
#include <Coordinate.hpp>

class Rotation{
    public:		
        Rotation(double rotation):
        rotation(rotation)
        {}
		
		Rotation(const Rotation & rhs):
		rotation(rhs.rotation)
		{}

    double rotation;
};

class Attitude{
    public: 
        Attitude():
        angle_x(r2d2::Angle(0 * r2d2::Angle::rad)),
        angle_y(r2d2::Angle(0 * r2d2::Angle::rad)),
        angle_z(r2d2::Angle(0 * r2d2::Angle::rad))
        {}
		
		Attitude(const Attitude & rhs):
		angle_x(rhs.angle_x),
		angle_y(rhs.angle_y),
		angle_z(rhs.angle_z)
		{}
		
        Attitude(r2d2::Angle angle_x, r2d2::Angle angle_y, r2d2::Angle angle_z):
        angle_x(angle_x),
        angle_y(angle_y),
        angle_z(angle_z)
        {}
		
        r2d2::Angle angle_x, angle_y, angle_z;
};

struct CoordinateAttitude{
	public:		
		r2d2::Coordinate coordinate;
		Attitude attitude;
};

#endif