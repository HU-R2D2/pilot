//! \addtogroup 0006 Pilot Simulation
//! \brief PilotSimulation is a Pilot which will simulate a driving pilot.
//!
//! \file   Pilot.hpp
//! \author Timon van den Brink 1664554
//! \author Anas Shehata 1651951
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
    //! @autor           Anas Shehata 1651951
    //! @date       06-06-16
    //! @version    1.0
    //! @brief      The PilotSimulation class is a class that will simmulate
    //!             a driving pilot It contains a rotation speed attribute,
    //!             speed and a waypoint attribute.
    //!
    class PilotSimulation: public Pilot {

        //!
        //!@brief      Initializes private member robot_status which is a
        //!            reference. Speed , rotation_speed and waypoints.
        //!
        //!@param      robot_status object containing actual
        //!            information about the robot.
        //!
        public:
        PilotSimulation(RobotStatus & robot_status, r2d2::Speed speed,
                                Rotation rotation_speed,
                                CoordinateAttitude waypoint);

        //!
        //!@brief      Interface function which will take care of the movement.
        //!            it wards coordinates on the map to the given parameter
        //!            coordinate_attitude.
        //!@param      coordinate_attitude the new position and orientation
        //!            where the robot needs to go.
        //!
        virtual void go_to_position(
        const CoordinateAttitude & coordinate_attitude) override;


        //!
        //!@brief     function that periodically simulates the motor management
        //!
        void run();

        //!
        //!@brief     checks if pilot has reached waypoint
        //!@return    bool
        bool has_reached_waypoint();

        private:
        Rotation rotation_speed;
        r2d2::Speed speed;
        LockingSharedObject < CoordinateAttitude > waypoint;
    };
}
#endif
