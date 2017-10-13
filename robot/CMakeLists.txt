# Set a variable for commands below
set(PROJECT_NAME LidarRobot)

# Define your project and language
project(${PROJECT_NAME} C CXX)

set(${PROJECT_NAME}_BOARD pro)

file(GLOB SRC_FILES *.cpp "../robot.cpp")
file(GLOB HDR_FILES *.h)

# Define the source code
set(${PROJECT_NAME}_SRCS ${SRC_FILES})

# Define the header files
set(${PROJECT_NAME}_HDRS ${HDR_FILES})

# set(${PROJECT_NAME}_SKETCH ${CMAKE_SOURCE_DIR}/robot)

# Define the port for uploading code to the Arduino
set(${PROJECT_NAME}_PORT COM6)

# Command to generate code arduino firmware (.hex file)
generate_arduino_firmware(${PROJECT_NAME})
