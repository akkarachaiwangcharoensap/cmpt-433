# Build the app, using the HAL

include_directories(include)
file(GLOB MY_SOURCES "src/*.c")
add_executable(reaction_timer ${MY_SOURCES})

# Make use of the HAL library
target_link_libraries(reaction_timer LINK_PRIVATE hal)

# Copy executable to final location (change `reaction_timer` to project name as needed)
add_custom_command(TARGET reaction_timer POST_BUILD 
  COMMAND "${CMAKE_COMMAND}" -E copy 
     "$<TARGET_FILE:reaction_timer>"
     "~/cmpt-433/public/assignment-1/reaction_timer" 
  COMMENT "Copying ARM executable to public NFS directory")
