#include "../source/include/PilotSimulation.hpp"

#include <iostream>
#include <vector>
#include <random>

bool has_reached_waypoint(CoordinateAttitude & current_waypoint,
    SharedObject<CoordinateAttitude> & robot_coordinate_attitude,
    CoordinateAttitude waypoint_precision_margin){

    CoordinateAttitude & coordinate_attitude_data =
        SharedObject<CoordinateAttitude>
        ::Accessor(robot_coordinate_attitude).access();

    // check if the x coordinate is in range of the precision_margin
    if (coordinate_attitude_data.coordinate.get_x() <
        (current_waypoint.coordinate + r2d2::Translation{
        waypoint_precision_margin.coordinate.get_x(), 0 *
        r2d2::Length::METER, 0 * r2d2::Length::METER}).get_x() &&
        coordinate_attitude_data.coordinate.get_x() >
        (current_waypoint.coordinate -
        r2d2::Translation{waypoint_precision_margin.coordinate.get_x(),
        0 * r2d2::Length::METER, 0 * r2d2::Length::METER}).get_x()){

        // check if the y coordinate is in range of the precision_margin
        if (coordinate_attitude_data.coordinate.get_y() <
            (current_waypoint.coordinate + r2d2::Translation{0 *
            r2d2::Length::METER,
            waypoint_precision_margin.coordinate.get_y(),0 *
            r2d2::Length::METER}).get_y() &&
            coordinate_attitude_data.coordinate.get_y() >
            (current_waypoint.coordinate - r2d2::Translation{0 *
            r2d2::Length::METER,
            waypoint_precision_margin.coordinate.get_y(), 0 *
            r2d2::Length::METER}).get_y()){

            // check if the attitude yaw is in range of the percision_margin
            if (coordinate_attitude_data.attitude.angle_z.get_angle() <
                current_waypoint.attitude.angle_z.get_angle() +
                waypoint_precision_margin.attitude.angle_z.get_angle() &&
                coordinate_attitude_data.attitude.angle_z.get_angle() >
                current_waypoint.attitude.angle_z.get_angle() -
                waypoint_precision_margin.attitude.angle_z.get_angle()){
                    return true;
            }
        }
    }
    return false;
}

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
	r2d2::Angle rotation_speed(0.1 * r2d2::Angle::rad);

	CoordinateAttitude waypoint = {r2d2::Coordinate(), Attitude()};

    r2d2::PilotSimulation pilot_simulation(robot_status, speed, rotation_speed,
        waypoint);

    std::thread pilot_simulation_thread(&r2d2::PilotSimulation::run,
        &pilot_simulation);

    for(CoordinateAttitude new_waypoint : psuedo_path){
        pilot_simulation.go_to_position(new_waypoint);

        while(!has_reached_waypoint(new_waypoint,
            robot_status.get_current_coordinate_attitude(), {
            r2d2::Coordinate(3.0 * r2d2::Length::METER, 3.0 *
            r2d2::Length::METER, 0 * r2d2::Length::METER), Attitude(0 *
            r2d2::Angle::rad, 0 * r2d2::Angle::rad,
            0.087 * r2d2::Angle::rad)})){

        LockingSharedObject<CoordinateAttitude> & temp_robot_status =
            robot_status.get_current_coordinate_attitude();

        CoordinateAttitude & coordinate_attitude =
            SharedObject<CoordinateAttitude>::Accessor(temp_robot_status)
            .access();

        Attitude & my_attitude = coordinate_attitude.attitude;
        r2d2::Coordinate & my_coordinate = coordinate_attitude.coordinate;

        std:cout << "waypoint:    " << new_waypoint
            .coordinate << " "  << new_waypoint.attitude.angle_z << std::endl;

        std::cout << "RobotStatus: " << coordinate_attitude.coordinate << " "
            << coordinate_attitude.attitude.angle_z << std::endl;


        std::this_thread::sleep_for(std::chrono::microseconds(500000));
        }
    }
    pilot_simulation_thread.join();
    return 0;
}
