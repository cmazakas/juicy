# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/christian/juicy/UnrolledList/VectorList

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/christian/juicy/UnrolledList/VectorList/build

# Include any dependencies generated for this target.
include CMakeFiles/VectorList.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/VectorList.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/VectorList.dir/flags.make

CMakeFiles/VectorList.dir/main.cpp.o: CMakeFiles/VectorList.dir/flags.make
CMakeFiles/VectorList.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/christian/juicy/UnrolledList/VectorList/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/VectorList.dir/main.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/VectorList.dir/main.cpp.o -c /home/christian/juicy/UnrolledList/VectorList/main.cpp

CMakeFiles/VectorList.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/VectorList.dir/main.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/christian/juicy/UnrolledList/VectorList/main.cpp > CMakeFiles/VectorList.dir/main.cpp.i

CMakeFiles/VectorList.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/VectorList.dir/main.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/christian/juicy/UnrolledList/VectorList/main.cpp -o CMakeFiles/VectorList.dir/main.cpp.s

CMakeFiles/VectorList.dir/main.cpp.o.requires:

.PHONY : CMakeFiles/VectorList.dir/main.cpp.o.requires

CMakeFiles/VectorList.dir/main.cpp.o.provides: CMakeFiles/VectorList.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/VectorList.dir/build.make CMakeFiles/VectorList.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/VectorList.dir/main.cpp.o.provides

CMakeFiles/VectorList.dir/main.cpp.o.provides.build: CMakeFiles/VectorList.dir/main.cpp.o


# Object files for target VectorList
VectorList_OBJECTS = \
"CMakeFiles/VectorList.dir/main.cpp.o"

# External object files for target VectorList
VectorList_EXTERNAL_OBJECTS =

VectorList: CMakeFiles/VectorList.dir/main.cpp.o
VectorList: CMakeFiles/VectorList.dir/build.make
VectorList: CMakeFiles/VectorList.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/christian/juicy/UnrolledList/VectorList/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable VectorList"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/VectorList.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/VectorList.dir/build: VectorList

.PHONY : CMakeFiles/VectorList.dir/build

CMakeFiles/VectorList.dir/requires: CMakeFiles/VectorList.dir/main.cpp.o.requires

.PHONY : CMakeFiles/VectorList.dir/requires

CMakeFiles/VectorList.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/VectorList.dir/cmake_clean.cmake
.PHONY : CMakeFiles/VectorList.dir/clean

CMakeFiles/VectorList.dir/depend:
	cd /home/christian/juicy/UnrolledList/VectorList/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/christian/juicy/UnrolledList/VectorList /home/christian/juicy/UnrolledList/VectorList /home/christian/juicy/UnrolledList/VectorList/build /home/christian/juicy/UnrolledList/VectorList/build /home/christian/juicy/UnrolledList/VectorList/build/CMakeFiles/VectorList.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/VectorList.dir/depend
