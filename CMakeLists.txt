cmake_minimum_required(VERSION 3.1.0)

project(Pencils)

#CMAKE_PREFIX_PATH="/Users/briansherif/Qt/5.13.0/clang_64/lib/cmake"

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed
set(CMAKE_AUTOMOC ON)
# Create code from a list of Qt designer ui files
set(CMAKE_AUTOUIC ON)

# Find the QtWidgets library
find_package(Qt5Widgets CONFIG REQUIRED)

# Populate a CMake variable with the sources
set(Pencils_SRCS
    src/produce_pencil.ui
    src/produce_pencil.cpp
    src/main.cpp
)

# Tell CMake to create the pencil production executable
add_executable(Pencils ${Pencils_SRCS})
# Use the Widgets module from Qt 5
target_link_libraries(Pencils Qt5::Widgets)



