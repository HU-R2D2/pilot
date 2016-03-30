/**
* @file PilotSimulatie.hpp
* @Author Timon van den Brink.
* @date 30 March, 2016
* @brief This file contains the interface Pilot
*/
#ifdef _PILOT_HPP
#define _PILOT_HPP

#include "Pilot.hpp"
/**
* @class PilotSimulatie
* @brief The class Pilot is an interface for all movable vehicles.
*/
class PilotSimulatie : public Pilot{
	public:
		PilotSimulatie(SharedObject<Coordinate> & current_position, SharedObject<Bearing> & current_bearing):
		current_position{current_position},
		current_bearing{current_bearing}
		{
		
		}
		void go_to_position(SharedObject<Coordinate> & destination, SharedObject<Bearing> & orientation) override {
			//current_position = destination;
			//current_bearing = orientation;
		}
	private:
		SharedObject<Coordinate> & current_position;
		SharedObject<Bearing> & current_bearing;
};

#endif