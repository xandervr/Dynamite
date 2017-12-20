//
//  CPU.hpp
//  Dynamite
//
//  Created by Xander Van Raemdonck on 21/12/2017.
//  Copyright © 2017 TnTap. All rights reserved.
//

#ifndef CPU_hpp
#define CPU_hpp

#include <stdio.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/sysctl.h>

#ifdef __APPLE__
    uint64_t get_cpu_temp(void);
#endif

#endif /* CPU_hpp */
