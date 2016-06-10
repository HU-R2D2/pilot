//! \addtogroup 0006 Pilot Simulation
//! \brief PilotSimulation is a Pilot which will simulate a driving pilot.
//!
//! \file   PilotSimulation.cpp
//! \author Timon van den Brink 1664554
//!  Anas Shehata 1651951
//! \date   Created: <30-03-16>
//! \date   Last Modified: <06-08-16>
//! \brief  In this file the PilotSimulation implementation can be found.
//!
//! \copyright Copyright � 2016, HU University of Applied Sciences Utrecht.
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

#include "../include/PilotSimulation.hpp"

namespace r2d2 {

    PilotSimulation::PilotSimulation(RobotStatus & robot_status,
        Speed speed, Rotation rotation_speed,
        CoordinateAttitude waypoint):
            Pilot(robot_status),
            speed(speed),
            rotation_speed(rotation_speed),
            waypoint(waypoint)
    {}

    void PilotSimulation::go_to_position(const CoordinateAttitude &
        coordinate_attitude){
        SharedObject<CoordinateAttitude>::Accessor(waypoint).access()
            = coordinate_attitude;
        start();
    }

    void PilotSimulation::run() {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        int period_ms = 100;
        Angle angle_precision_margin(0.087 * Angle::rad);
        while (true) {
            if (get_enabled()) {
                //get access to waypoint
                LockingSharedObject < CoordinateAttitude >::Accessor
                    acc(waypoint);
                CoordinateAttitude & waypoint_data = acc.access();

                //get RobotStatus object
                LockingSharedObject < CoordinateAttitude >
                    & temp_robot_status =
                    robot_status.get_current_coordinate_attitude();

                CoordinateAttitude & coordinate_attitude =
                    SharedObject < CoordinateAttitude >
                        ::Accessor(temp_robot_status).access();

                Coordinate & my_coordinate =
                   coordinate_attitude.coordinate;
                Angle & my_angle =
                   coordinate_attitude.attitude.angle_z;

                //waypoint_angle between waypoint and current_position
                Translation my_translation(
                    waypoint_data.coordinate.get_x() -
                       my_coordinate.get_x(),
                    waypoint_data.coordinate.get_y() -
                       my_coordinate.get_y(), 0 * Length::METER);

                Angle waypoint_angle =
                    std::atan2(my_translation.get_y()
                    / Length::METER, my_translation.get_x()
                    / Length::METER) * Angle::rad;

                if (my_angle.get_angle() <= waypoint_angle.get_angle()
                       + angle_precision_margin.get_angle()
                    && my_angle.get_angle() >= waypoint_angle.get_angle()
                       - angle_precision_margin.get_angle()) {
                    my_coordinate += {
                        (std::cos(my_angle.get_angle())
                            * speed
                            / (Length::METER
                            / Duration::SECOND))
                            * Length::METER,
                        (std::sin(my_angle.get_angle()) * speed
                            / (Length::METER
                            / Duration::SECOND))
                            * Length::METER,
                        0 * Length::METER
                    };
                } else {
                    if (my_angle.get_angle() < waypoint_angle.get_angle()) {
                        my_angle += rotation_speed.rotation
                        * Angle::rad;
                    } else {
                        my_angle -= rotation_speed.rotation
                        * Angle::rad;
                    }
                }
            }
            std::this_thread::sleep_for(
                std::chrono::milliseconds(period_ms));
        }
    }
}
