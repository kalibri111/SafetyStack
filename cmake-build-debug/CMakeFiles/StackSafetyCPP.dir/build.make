# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.17

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Disable VCS-based implicit rules.
% : %,v


# Disable VCS-based implicit rules.
% : RCS/%


# Disable VCS-based implicit rules.
% : RCS/%,v


# Disable VCS-based implicit rules.
% : SCCS/s.%


# Disable VCS-based implicit rules.
% : s.%


.SUFFIXES: .hpux_make_needs_suffix_list


# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

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
CMAKE_COMMAND = /snap/clion/126/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /snap/clion/126/bin/cmake/linux/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/kalibri/MIPT/1_sem/Dedinsky/StackSafetyCPP

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/kalibri/MIPT/1_sem/Dedinsky/StackSafetyCPP/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/StackSafetyCPP.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/StackSafetyCPP.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/StackSafetyCPP.dir/flags.make

CMakeFiles/StackSafetyCPP.dir/main.cpp.o: CMakeFiles/StackSafetyCPP.dir/flags.make
CMakeFiles/StackSafetyCPP.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kalibri/MIPT/1_sem/Dedinsky/StackSafetyCPP/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/StackSafetyCPP.dir/main.cpp.o"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/StackSafetyCPP.dir/main.cpp.o -c /home/kalibri/MIPT/1_sem/Dedinsky/StackSafetyCPP/main.cpp

CMakeFiles/StackSafetyCPP.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/StackSafetyCPP.dir/main.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kalibri/MIPT/1_sem/Dedinsky/StackSafetyCPP/main.cpp > CMakeFiles/StackSafetyCPP.dir/main.cpp.i

CMakeFiles/StackSafetyCPP.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/StackSafetyCPP.dir/main.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kalibri/MIPT/1_sem/Dedinsky/StackSafetyCPP/main.cpp -o CMakeFiles/StackSafetyCPP.dir/main.cpp.s

# Object files for target StackSafetyCPP
StackSafetyCPP_OBJECTS = \
"CMakeFiles/StackSafetyCPP.dir/main.cpp.o"

# External object files for target StackSafetyCPP
StackSafetyCPP_EXTERNAL_OBJECTS =

StackSafetyCPP: CMakeFiles/StackSafetyCPP.dir/main.cpp.o
StackSafetyCPP: CMakeFiles/StackSafetyCPP.dir/build.make
StackSafetyCPP: CMakeFiles/StackSafetyCPP.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/kalibri/MIPT/1_sem/Dedinsky/StackSafetyCPP/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable StackSafetyCPP"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/StackSafetyCPP.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/StackSafetyCPP.dir/build: StackSafetyCPP

.PHONY : CMakeFiles/StackSafetyCPP.dir/build

CMakeFiles/StackSafetyCPP.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/StackSafetyCPP.dir/cmake_clean.cmake
.PHONY : CMakeFiles/StackSafetyCPP.dir/clean

CMakeFiles/StackSafetyCPP.dir/depend:
	cd /home/kalibri/MIPT/1_sem/Dedinsky/StackSafetyCPP/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/kalibri/MIPT/1_sem/Dedinsky/StackSafetyCPP /home/kalibri/MIPT/1_sem/Dedinsky/StackSafetyCPP /home/kalibri/MIPT/1_sem/Dedinsky/StackSafetyCPP/cmake-build-debug /home/kalibri/MIPT/1_sem/Dedinsky/StackSafetyCPP/cmake-build-debug /home/kalibri/MIPT/1_sem/Dedinsky/StackSafetyCPP/cmake-build-debug/CMakeFiles/StackSafetyCPP.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/StackSafetyCPP.dir/depend

