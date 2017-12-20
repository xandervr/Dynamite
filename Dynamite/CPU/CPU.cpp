//
//  CPU.cpp
//  Dynamite
//
//  Created by Xander Van Raemdonck on 21/12/2017.
//  Copyright © 2017 TnTap. All rights reserved.
//

#include "CPU.hpp"

#ifdef __APPLE__
    uint64_t get_cpu_temp(void)
    {
        uint64_t temp = 0;
        size_t size = sizeof(temp);
        
        if (sysctlbyname("machdep.xcpm.cpu_thermal_level", &temp, &size, NULL, 0) < 0)
        {
            perror("sysctl");
        }
        return temp;
    }
#endif

