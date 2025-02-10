cmake_minimum_required( VERSION 3.10 )

set( PROJECT_NAME DTED_Database )
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin" )

project( ${PROJECT_NAME} )
set( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99" )


find_package( PostgreSQL REQUIRED ) 
include_directories( /opt/homebrew/include )
link_directories( /opt/homebrew/lib )

add_executable( main Main.c )
target_link_libraries( main pq )

