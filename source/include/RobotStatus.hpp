//! \addtogroup 0006 Pilot Simulation
//!
//! The class RobotStatus is a model which contains data objects, those data objects give information about the status of the Robot.
//! The value of RobotStatus is that the data in this container can be shared over a network for example, this object makes also logging of the status of Robot easy. 
//!
//! \file   RobotStatus.hpp
//! \author Timon van den Brink 1664554
//! \date   Created: <15-04-16>
//! \date   Last Modified: <02-06-16>
//! \brief  In this file the object RobotStatus can be found.
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

#ifndef _ROBOTSTATUS_HPP
#define _ROBOTSTATUS_HPP

#include <Speed.hpp>
#include <LockingSharedObject.hpp>

#include "stubs.hpp"

namespace r2d2{

	class RobotStatus{
		public:
			//!@brief Initializes private members with the given parameters.
			//!@param coordinate_attitude object which contains the robots current location and orientation.
			//!@param speed this object will represent the robots current speed.
			RobotStatus(CoordinateAttitude & coordinate_attitude, r2d2::Speed & speed):
			current_coordinate_attitude(coordinate_attitude),
			current_speed(speed)
			{}	
			
			//!@brief Getter for current_coordinate_attitude,
			//!@brief returns a reference to LockingSharedObject current_coordinate_attitude.
			LockingSharedObject<CoordinateAttitude> & get_current_coordinate_attitude() {
				return current_coordinate_attitude;
			}		
			
			//!@brief Getter for current_speed,
			//!@brief returns a reference to LockingSharedObject current_speed.
			LockingSharedObject<r2d2::Speed> & get_current_speed() {
				return current_speed;
			}
		
		private:
			LockingSharedObject<CoordinateAttitude> current_coordinate_attitude;
			LockingSharedObject<r2d2::Speed> current_speed;
	};
}
#endif