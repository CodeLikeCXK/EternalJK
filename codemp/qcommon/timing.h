/*
===========================================================================
Copyright (C) 2000 - 2013, Raven Software, Inc.
Copyright (C) 2001 - 2013, Activision, Inc.
Copyright (C) 2013 - 2015, OpenJK contributors

This file is part of the OpenJK source code.

OpenJK is free software; you can redistribute it and/or modify it
under the terms of the GNU General Public License version 2 as
published by the Free Software Foundation.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, see <http://www.gnu.org/licenses/>.
===========================================================================
*/
/*
===========================================================================
Copyright (C) 2000 - 2013, Raven Software, Inc.
Copyright (C) 2001 - 2013, Activision, Inc.
Copyright (C) 2013 - 2015, OpenJK contributors

This file is part of the OpenJK source code.

OpenJK is free software; you can redistribute it and/or modify it
under the terms of the GNU General Public License version 2 as
published by the Free Software Foundation.
===========================================================================
*/

#pragma once

#include <windows.h>
#include <stdint.h> // Include for uint64_t

#ifdef _WIN32
    #include <intrin.h>
    // Fallback definition for ARM64_CNTVCT if the SDK is old
    #if defined(_M_ARM64) && !defined(ARM64_CNTVCT)
        #define ARM64_CNTVCT ARM64_SYSREG(3,3,14,0,2)
    #endif
#endif

class timing_c
{
private:
    uint64_t    start;
    uint64_t    end;

public:
    timing_c(void)
    {
    }

    void Start()
    {
#ifdef _WIN32
        #if defined(_M_ARM64)
            // Fix: Assign to 'start', do not return
            start = _ReadStatusReg(ARM64_CNTVCT);
        #elif defined(_M_AMD64) || defined(_M_IX86)
            start = __rdtsc();
        #endif
#else
        start = 0;
#endif
    }

    int End()
    {
        int64_t time;

#ifdef _WIN32
        #if defined(_M_ARM64)
            // Fix: Assign to 'end' so we can calculate the difference below
            end = _ReadStatusReg(ARM64_CNTVCT);
        #elif defined(_M_AMD64) || defined(_M_IX86)
            end = __rdtsc();
        #endif
#else
        end = 0;
#endif

        // Now calculate the duration using the values we just set
        time = end - start;
        if (time < 0)
        {
            time = 0;
        }
        return((int)time);
    }
};