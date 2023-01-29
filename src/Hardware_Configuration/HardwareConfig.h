#ifndef HARDWARECONFIG_H
#define HARDWARECONFIG_H

//TODO::All definitions should be const and typed so that they are checked at compile time and not just blind macro textual replacements,
// types should match expected types so compile errors aren't thrown

//TODO:: Are explicit/exact types appropriate for the situation,
// e.g. is GPS_RX_PIN really a uint32 or does the library expect something else, If it is expecting a uint32. then why?
// Why is it coded using a uint32 instead of being length independent for different systems as most systems don't use 32-bit pin addresses,
// When possible (its written in our code and not someone else's library), these errors should be corrected across the whole system

//TODO::Compilers are smart and having uint8, uint32 typedefs often don't make sense and potentially even limit platform-specific compiler optimizations,
// When we don't care what the type is specifically and we just care that it works properly and
// in situations where there is no explicit type specificity a decision should be made, we should consider these cases:
// 1) e.g. For integers: Is the maximum length and possible pos/neg value known? Should I explicitly make this signed o unsigned? Should I limit the maximum size?
//         For Chars: Should I use a char array here, or would a C++ string class make more sense (and the performance decrease be unimportant compared to improved clarity and ease of use)
// 2) This system varies and isn't set in stone, In this case, the type should just be made int or a pointer configurable type or a variable-type std::container or perhaps even std::auto in special cases


#include "HAB_Teensy.hpp"
#include "HAB_ESP32.hpp"
#include "HAB_STM32.hpp"
#include "HAB_Nano.hpp"


#endif //HARDWARECONFIG_H