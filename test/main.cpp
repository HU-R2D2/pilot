#include "../source/include/PilotSimulation.hpp"

#include <iostream>
#include <vector>
#include <random>

int main(int argc,char *argv[]){

	std::vector<CoordinateAttitude> psuedo_path;

	for(int i = 0; i < 10; ++i){
		double attitude = rand() % 2;
		double x(rand() % 100), y(rand() % 100);
	    std::cout << "x: " << x << " y: " << y << " attitude: " << attitude
            << std::endl;
		psuedo_path.push_back(CoordinateAttitude{r2d2::Coordinate(x *
            r2d2::Length::METER, y * r2d2::Length::METER, 0 *
            r2d2::Length::METER), Attitude(0 * r2d2::Angle::rad, 0 *
                r2d2::Angle::rad, attitude * r2d2::Angle::rad)});
	}

	CoordinateAttitude status = {r2d2::Coordinate(0 * r2d2::Length::METER,
        0 * r2d2::Length::METER, 0 * r2d2::Length::METER), Attitude()};

	r2d2::Speed s = 0 * r2d2::Length::METER/r2d2::Duration::SECOND;

	r2d2::RobotStatus robot_status(status, s);

	r2d2::Speed speed = 1.0 * r2d2::Length::METER/r2d2::Duration::SECOND;
	Rotation rotation_speed(0.1);

	CoordinateAttitude waypoint = {r2d2::Coordinate(), Attitude()};

    r2d2::PilotSimulation pilot_simulation(robot_status, speed, rotation_speed,
        waypoint);

    std::thread pilot_simulation_thread(&r2d2::PilotSimulation::run,
        &pilot_simulation);

	std::this_thread::sleep_for(std::chrono::seconds(5));

   	for(CoordinateAttitude new_waypoint : psuedo_path){
		while(!pilot_simulation.has_reached_waypoint()){
			std::this_thread::sleep_for(std::chrono::seconds(2));
		}
		pilot_simulation.go_to_position(new_waypoint);
	}
	pilot_simulation_thread.join();
    return 0;
}
