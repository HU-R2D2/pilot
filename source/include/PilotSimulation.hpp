//! \addtogroup 0006 Pilot Simulation
//! \brief PilotSimulation is a Pilot which will simulate a driving pilot.
//!
//! \file   Pilot.hpp
//! \author Timon van den Brink 1664554
//! \date   Created: <30-03-16>
//! \date   Last Modified: <02-06-16>
//! \brief  In this file the PilotSimulation implementation can be found.
//!
//! \copyright Copyright © 2016, HU University of Applied Sciences Utrecht. 
//! All rights reserved.
//! 
//! License: newBSD
//!
//! Redistribution and use in source and binary forms, 
//! with or without modification, are permitted provided that 
//! the following conditions are met:
//! - Redistributions of source code must retain the above copyright notice, 
//!   this list of conditions and the following disclaimer.
//! - Redistributions in binary form must reproduce the above copyright notice, 
//!   this list of conditions and the following disclaimer in the documentation 
//!   and/or other materials provided with the distribution.
//! - Neither the name of the HU University of Applied Sciences Utrecht 
//!   nor the names of its contributors may be used to endorse or promote 
//!   products derived from this software without specific prior written 
//!   permission.
//!
//! THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
//! "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, 
//! BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY 
//! AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. 
//! IN NO EVENT SHALL THE HU UNIVERSITY OF APPLIED SCIENCES UTRECHT
//! BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
//! CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, 
//! PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; 
//! OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, 
//! WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR 
//! OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, 
//! EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// ~< HEADER_VERSION 2016 04 12 >~
#ifndef _PILOTSIMULATION_HPP
#define _PILOTSIMULATION_HPP
#include <iostream>
#include <chrono>
#include <thread>
#include <cmath>
#include <Translation.hpp>
#include "Pilot.hpp"

namespace r2d2 {

    //! @author     Timon van den Brink 1664554
    //! @date       06-06-16
    //! @version    1.0
    //! @brief      The PilotSimulation class is a class that will simmulate a driving pilot
    //!             It contains a rotation speed attribute, speed and a waypoint attribute.
    //!
    //!
    class PilotSimulation: public Pilot {

        //!
        //!@brief      Initializes private member robot_status which is a reference. 
        //!@brief      Speed , rotation_speed and waypoints. 
        //!@param      robot_status object containing actual information about the robot.
        //!
        public: PilotSimulation(RobotStatus & robot_status, r2d2::Speed speed,
                                Rotation rotation_speed,CoordinateAttitude waypoint): 
        Pilot(robot_status),
        speed(speed),
        rotation_speed(rotation_speed),
        waypoint(waypoint) {}

        //!
        //!@brief Interface function which will take care of the movement.
        //!@brief it wards coordinates on the map to the given parameter coordinate_attitude. 
        //!@param coordinate_attitude the new position and orientation where the robot needs to go.
        //!
        void go_to_position(const CoordinateAttitude & coordinate_attitude) override {
            CoordinateAttitude & waypoint_data=
            LockingSharedObject<CoordinateAttitude>::Accessor(waypoint).access();
            waypoint_data = coordinate_attitude;
        }

        //!
        //!@brief     function that periodicly simulates the motor management    
        //!
        void run() {
            std::this_thread::sleep_for(std::chrono::seconds(1));
            int period_ms = 100;
            int idle_time_ms = 0;
            while (true) {
                if (!has_reached_waypoint()) {
                    idle_time_ms = 0;
                    //get access to waypoint
                    LockingSharedObject < CoordinateAttitude > ::Accessor acc(waypoint);
                    CoordinateAttitude & waypoint_data = acc.access();

                    //get RobotStatus object 
                    LockingSharedObject < CoordinateAttitude > & temp_robot_status = 
                        robot_status.get_current_coordinate_attitude();

                    CoordinateAttitude & coordinate_attitude =
                        SharedObject < CoordinateAttitude > ::Accessor(temp_robot_status).access();
                    Attitude & my_attitude = coordinate_attitude.attitude;
                    r2d2::Coordinate & my_coordinate = coordinate_attitude.coordinate;

                    r2d2::Angle & my_angle = my_attitude.angle_z;

                    //waypoint_angle between waypoint and current_position
                    r2d2::Translation my_translation(
                        waypoint_data.coordinate.get_x() - my_coordinate.get_x(),
                        waypoint_data.coordinate.get_y() - my_coordinate.get_y(), 
                        0 * r2d2::Length::METER);

                    r2d2::Angle waypoint_angle = 
                        std::atan2(my_translation.get_y() 
                        / r2d2::Length::METER, my_translation.get_x() 
                        / r2d2::Length::METER) * r2d2::Angle::rad;

                    if (my_angle.get_angle() <= waypoint_angle.get_angle() + 0.087 
                        && my_angle.get_angle() >= waypoint_angle.get_angle() - 0.087) {
                        my_coordinate += {
                            (std::cos(my_angle.get_angle()) * speed 
                                / (r2d2::Length::METER / r2d2::Duration::SECOND)) * r2d2::Length::METER,
                            (std::sin(my_angle.get_angle()) * speed / (r2d2::Length::METER 
                                / r2d2::Duration::SECOND)) * r2d2::Length::METER,
                            0 * r2d2::Length::METER
                        };
                    } else {
                        if (my_angle.get_angle() < waypoint_angle.get_angle()) {
                            my_angle += rotation_speed.rotation * r2d2::Angle::rad;
                        } else {
                            my_angle -= rotation_speed.rotation * r2d2::Angle::rad;
                        }
                    }
                    std::cout << "    my_angle:" << my_angle << std::endl;
                    std::cout << "    waypoint_angle:" << waypoint_angle << std::endl;
                    std::cout << "    Waypoint:" << waypoint_data.coordinate 
                        << " attitude:" << waypoint_data.attitude.angle_z << std::endl;
                    std::cout << "    CoordinateAttitude:" << my_coordinate << " attitude:" << my_angle << std::endl;

                } else {
                    idle_time_ms += period_ms;
                    if (idle_time_ms >= 10000) {
                        break;
                    }
                }
                std::this_thread::sleep_for(std::chrono::milliseconds(period_ms));
            }
        }

        //!
        //!@brief     checks if pilot has reached waypoint   
        //!@return    bool 
        bool has_reached_waypoint() {
            LockingSharedObject < CoordinateAttitude > ::Accessor acc(waypoint);
            CoordinateAttitude & waypoint_data = acc.access();

            LockingSharedObject < CoordinateAttitude > & temp_robot_status = 
                robot_status.get_current_coordinate_attitude();

            CoordinateAttitude & coordinate_attitude = 
                SharedObject < CoordinateAttitude > ::Accessor(temp_robot_status).access();
            Attitude & my_attitude = coordinate_attitude.attitude;
            r2d2::Coordinate & my_coordinate = coordinate_attitude.coordinate;

            if (my_coordinate.get_x() < (waypoint_data.coordinate + r2d2::Translation {
                    3 * r2d2::Length::METER, 0 * r2d2::Length::METER, 0 * r2d2::Length::METER
                }).get_x() && my_coordinate.get_x() > (waypoint_data.coordinate - r2d2::Translation {
                    3 * r2d2::Length::METER, 0 * r2d2::Length::METER, 0 * r2d2::Length::METER
                }).get_x()) {
                if (my_coordinate.get_y() < (waypoint_data.coordinate + r2d2::Translation {
                        0 * r2d2::Length::METER, 3 * r2d2::Length::METER, 0 * r2d2::Length::METER
                    }).get_y() && my_coordinate.get_y() > (waypoint_data.coordinate - r2d2::Translation {
                        0 * r2d2::Length::METER, 3 * r2d2::Length::METER, 0 * r2d2::Length::METER
                    }).get_y()) {
                    if (my_attitude.angle_z.get_angle() < waypoint_data.attitude.angle_z.get_angle() + 0.087 
                    && my_attitude.angle_z.get_angle() > waypoint_data.attitude.angle_z.get_angle() - 0.087) {
                        return true;
                    }
                }
            }
            return false;
        }
        private: 
        Rotation rotation_speed;
        r2d2::Speed speed;
        LockingSharedObject < CoordinateAttitude > waypoint;
    };
}
#endif