# CMakeList.txt for HAL
#   Build a library (`hal`) which exposes the header files as "hal/*.h"
#   Use header as: #include "hal/button.h"

include_directories(include)
include_directories(hal/include)
file(GLOB MY_SOURCES "src/*.c")

add_library(hal STATIC ${MY_SOURCES})
target_include_directories(hal PUBLIC include)

find_library(GPIOD_LIBRARY gpiod)       # UNSURE IF NEEDED
# target_link_libraries(btn_statemachine LINK_PRIVATE gpiod) # May need to change to HAL lib.

target_link_libraries(hal PRIVATE gpiod)