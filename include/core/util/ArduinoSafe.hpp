/**
 * Arduino.h redefines min and max, which causes problems when using certain parts of the C++ standard library.
 * By undefining true and false from Arduino, code completion features in IDE's seem to work better.
 */

#pragma once

#include <Arduino.h>
#undef min
#undef max
#undef true
#undef false