# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.15

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
CMAKE_COMMAND = /home/dave11ar/Soft/clion-2019.2.5/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/dave11ar/Soft/clion-2019.2.5/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/dave11ar/GitHub/Algo/Lab/Lab4/Interesting

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/dave11ar/GitHub/Algo/Lab/Lab4/Interesting/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/Interesting.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Interesting.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Interesting.dir/flags.make

CMakeFiles/Interesting.dir/main.cpp.o: CMakeFiles/Interesting.dir/flags.make
CMakeFiles/Interesting.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dave11ar/GitHub/Algo/Lab/Lab4/Interesting/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Interesting.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Interesting.dir/main.cpp.o -c /home/dave11ar/GitHub/Algo/Lab/Lab4/Interesting/main.cpp

CMakeFiles/Interesting.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Interesting.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/dave11ar/GitHub/Algo/Lab/Lab4/Interesting/main.cpp > CMakeFiles/Interesting.dir/main.cpp.i

CMakeFiles/Interesting.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Interesting.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/dave11ar/GitHub/Algo/Lab/Lab4/Interesting/main.cpp -o CMakeFiles/Interesting.dir/main.cpp.s

# Object files for target Interesting
Interesting_OBJECTS = \
"CMakeFiles/Interesting.dir/main.cpp.o"

# External object files for target Interesting
Interesting_EXTERNAL_OBJECTS =

Interesting: CMakeFiles/Interesting.dir/main.cpp.o
Interesting: CMakeFiles/Interesting.dir/build.make
Interesting: CMakeFiles/Interesting.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/dave11ar/GitHub/Algo/Lab/Lab4/Interesting/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Interesting"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Interesting.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Interesting.dir/build: Interesting

.PHONY : CMakeFiles/Interesting.dir/build

CMakeFiles/Interesting.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Interesting.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Interesting.dir/clean

CMakeFiles/Interesting.dir/depend:
	cd /home/dave11ar/GitHub/Algo/Lab/Lab4/Interesting/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/dave11ar/GitHub/Algo/Lab/Lab4/Interesting /home/dave11ar/GitHub/Algo/Lab/Lab4/Interesting /home/dave11ar/GitHub/Algo/Lab/Lab4/Interesting/cmake-build-debug /home/dave11ar/GitHub/Algo/Lab/Lab4/Interesting/cmake-build-debug /home/dave11ar/GitHub/Algo/Lab/Lab4/Interesting/cmake-build-debug/CMakeFiles/Interesting.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Interesting.dir/depend

