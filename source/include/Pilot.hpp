/**
* @file Pilot.hpp
* @Author Timon van den Brink.
* @date 30 March, 2016
* @brief This file contains the interface Pilot
*/
#ifdef _PILOT_HPP
#define _PILOT_HPP

/**
* @class Pilot
* @brief The class Pilot is an interface for all movable vehicles.
*/
class Pilot{
	public:
		virtual void go_to_position(SharedObject<Coordinate> & destination, SharedObject<Bearing> & orientation) = 0;
};

#endif