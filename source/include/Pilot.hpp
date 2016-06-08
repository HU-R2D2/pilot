//! \addtogroup 0006 Pilot Simulation
//! \brief Pilot is an abstraction for any movable vehicle.
//!
//! \file   Pilot.hpp
//! \author Timon van den Brink 1664554
//!         Anas Shehata 1651951
//! \date   Created: <30-03-16>
//! \date   Last Modified: <06-08-16>
//! \brief  In this file the Pilot interface can be found.
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
#ifndef _PILOT_HPP
#define _PILOT_HPP

#include "RobotStatus.hpp"

namespace r2d2{

    //! @author     Timon van den Brink 1664554
    //! @autor      Anas Shehata 1651951
    //! @date       07-06-16
    //! @version    1.0
    //! @brief      Pilot is an abstraction for any movable vehicle.
    //!             it contains 1 robot_status attribute and is responsible
    //!             for movement.
    //!
    class Pilot{
        public:

            //!
            //!@brief      Initializes private member robot_status which is a
            //!            reference and contains the actual information about
            //!            the robot.
            //!@param      robot_status object containing actual information
            //!            about the robot.
            //!
            Pilot(RobotStatus & robot_status);

            //!
            //!@brief   Interface function which will take care of the movement.
            //!         it wards coordinates on the map to the given parameter
            //!         coordinate_attitude.
            //!
            //!@param   coordinate_attitude the new position and orientation
            //!         where the robot needs to go.
            //!
            virtual void go_to_position(
                const CoordinateAttitude & coordinate_attitude) = 0;


            void start();

            void stop();

            bool get_enabled();

        protected:
            RobotStatus & robot_status;
        private:
            bool enabled = false;
            LockingSharedObject<bool> shared_enabled;
    };
}
#endif
