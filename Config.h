#ifndef CONFIG_H
#define CONFIG_H

#include "src/Utilities/Utilities.h"
// Simple bits of functional macros that provide various convenience functions
// Also contains platform-specific hardware call wrapper functions

#include "ProjectConfig.hpp"
// Provides various structures to control most aspects of program performance
// Also contains hardware controllers and debugging system controls

#include "src/Hardware_Configuration/HardwareConfig.h"  // Must be included AFTER ProjectConfig.hpp
// Contains pinout mapping definitions for assorted hardware platforms

#endif //CONFIG_H