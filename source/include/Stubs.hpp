//! \addtogroup 0006 Pilot Simulation
//! \brief PilotSimulation is a Pilot which will simulate a driving pilot.
//!
//! \file   Stubs.hpp
//! \author Timon van den Brink 1664554
//!  Anas Shehata 1651951
//! \date   Created: <30-03-16>
//! \date   Last Modified: <06-08-16>
//! \brief  In this file stubs used in the Pilot until the official classes are
//! released
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
