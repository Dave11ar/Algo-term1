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
CMAKE_SOURCE_DIR = /home/dave11ar/GitHub/Algo/Lab/Lab4/Levenshtein

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/dave11ar/GitHub/Algo/Lab/Lab4/Levenshtein/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/Levenshtein.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Levenshtein.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Levenshtein.dir/flags.make

CMakeFiles/Levenshtein.dir/main.cpp.o: CMakeFiles/Levenshtein.dir/flags.make
CMakeFiles/Levenshtein.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dave11ar/GitHub/Algo/Lab/Lab4/Levenshtein/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Levenshtein.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Levenshtein.dir/main.cpp.o -c /home/dave11ar/GitHub/Algo/Lab/Lab4/Levenshtein/main.cpp

CMakeFiles/Levenshtein.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Levenshtein.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/dave11ar/GitHub/Algo/Lab/Lab4/Levenshtein/main.cpp > CMakeFiles/Levenshtein.dir/main.cpp.i

CMakeFiles/Levenshtein.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Levenshtein.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/dave11ar/GitHub/Algo/Lab/Lab4/Levenshtein/main.cpp -o CMakeFiles/Levenshtein.dir/main.cpp.s

# Object files for target Levenshtein
Levenshtein_OBJECTS = \
"CMakeFiles/Levenshtein.dir/main.cpp.o"

# External object files for target Levenshtein
Levenshtein_EXTERNAL_OBJECTS =

Levenshtein: CMakeFiles/Levenshtein.dir/main.cpp.o
Levenshtein: CMakeFiles/Levenshtein.dir/build.make
Levenshtein: CMakeFiles/Levenshtein.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/dave11ar/GitHub/Algo/Lab/Lab4/Levenshtein/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Levenshtein"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Levenshtein.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Levenshtein.dir/build: Levenshtein

.PHONY : CMakeFiles/Levenshtein.dir/build

CMakeFiles/Levenshtein.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Levenshtein.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Levenshtein.dir/clean

CMakeFiles/Levenshtein.dir/depend:
	cd /home/dave11ar/GitHub/Algo/Lab/Lab4/Levenshtein/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/dave11ar/GitHub/Algo/Lab/Lab4/Levenshtein /home/dave11ar/GitHub/Algo/Lab/Lab4/Levenshtein /home/dave11ar/GitHub/Algo/Lab/Lab4/Levenshtein/cmake-build-debug /home/dave11ar/GitHub/Algo/Lab/Lab4/Levenshtein/cmake-build-debug /home/dave11ar/GitHub/Algo/Lab/Lab4/Levenshtein/cmake-build-debug/CMakeFiles/Levenshtein.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Levenshtein.dir/depend

