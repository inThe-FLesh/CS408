# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.26

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

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /snap/clion/250/bin/cmake/linux/x64/bin/cmake

# The command to remove a file.
RM = /snap/clion/250/bin/cmake/linux/x64/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/ross/Documents/Year4/CS408/CS408

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ross/Documents/Year4/CS408/CS408/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/CS408.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/CS408.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/CS408.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/CS408.dir/flags.make

CMakeFiles/CS408.dir/src/sha-256/SHA256.cpp.o: CMakeFiles/CS408.dir/flags.make
CMakeFiles/CS408.dir/src/sha-256/SHA256.cpp.o: /home/ross/Documents/Year4/CS408/CS408/src/sha-256/SHA256.cpp
CMakeFiles/CS408.dir/src/sha-256/SHA256.cpp.o: CMakeFiles/CS408.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ross/Documents/Year4/CS408/CS408/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/CS408.dir/src/sha-256/SHA256.cpp.o"
	/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/CS408.dir/src/sha-256/SHA256.cpp.o -MF CMakeFiles/CS408.dir/src/sha-256/SHA256.cpp.o.d -o CMakeFiles/CS408.dir/src/sha-256/SHA256.cpp.o -c /home/ross/Documents/Year4/CS408/CS408/src/sha-256/SHA256.cpp

CMakeFiles/CS408.dir/src/sha-256/SHA256.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/CS408.dir/src/sha-256/SHA256.cpp.i"
	/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ross/Documents/Year4/CS408/CS408/src/sha-256/SHA256.cpp > CMakeFiles/CS408.dir/src/sha-256/SHA256.cpp.i

CMakeFiles/CS408.dir/src/sha-256/SHA256.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/CS408.dir/src/sha-256/SHA256.cpp.s"
	/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ross/Documents/Year4/CS408/CS408/src/sha-256/SHA256.cpp -o CMakeFiles/CS408.dir/src/sha-256/SHA256.cpp.s

CMakeFiles/CS408.dir/src/sha-256/preprocessing.cpp.o: CMakeFiles/CS408.dir/flags.make
CMakeFiles/CS408.dir/src/sha-256/preprocessing.cpp.o: /home/ross/Documents/Year4/CS408/CS408/src/sha-256/preprocessing.cpp
CMakeFiles/CS408.dir/src/sha-256/preprocessing.cpp.o: CMakeFiles/CS408.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ross/Documents/Year4/CS408/CS408/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/CS408.dir/src/sha-256/preprocessing.cpp.o"
	/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/CS408.dir/src/sha-256/preprocessing.cpp.o -MF CMakeFiles/CS408.dir/src/sha-256/preprocessing.cpp.o.d -o CMakeFiles/CS408.dir/src/sha-256/preprocessing.cpp.o -c /home/ross/Documents/Year4/CS408/CS408/src/sha-256/preprocessing.cpp

CMakeFiles/CS408.dir/src/sha-256/preprocessing.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/CS408.dir/src/sha-256/preprocessing.cpp.i"
	/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ross/Documents/Year4/CS408/CS408/src/sha-256/preprocessing.cpp > CMakeFiles/CS408.dir/src/sha-256/preprocessing.cpp.i

CMakeFiles/CS408.dir/src/sha-256/preprocessing.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/CS408.dir/src/sha-256/preprocessing.cpp.s"
	/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ross/Documents/Year4/CS408/CS408/src/sha-256/preprocessing.cpp -o CMakeFiles/CS408.dir/src/sha-256/preprocessing.cpp.s

CMakeFiles/CS408.dir/src/sha-256/computation.cpp.o: CMakeFiles/CS408.dir/flags.make
CMakeFiles/CS408.dir/src/sha-256/computation.cpp.o: /home/ross/Documents/Year4/CS408/CS408/src/sha-256/computation.cpp
CMakeFiles/CS408.dir/src/sha-256/computation.cpp.o: CMakeFiles/CS408.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ross/Documents/Year4/CS408/CS408/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/CS408.dir/src/sha-256/computation.cpp.o"
	/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/CS408.dir/src/sha-256/computation.cpp.o -MF CMakeFiles/CS408.dir/src/sha-256/computation.cpp.o.d -o CMakeFiles/CS408.dir/src/sha-256/computation.cpp.o -c /home/ross/Documents/Year4/CS408/CS408/src/sha-256/computation.cpp

CMakeFiles/CS408.dir/src/sha-256/computation.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/CS408.dir/src/sha-256/computation.cpp.i"
	/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ross/Documents/Year4/CS408/CS408/src/sha-256/computation.cpp > CMakeFiles/CS408.dir/src/sha-256/computation.cpp.i

CMakeFiles/CS408.dir/src/sha-256/computation.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/CS408.dir/src/sha-256/computation.cpp.s"
	/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ross/Documents/Year4/CS408/CS408/src/sha-256/computation.cpp -o CMakeFiles/CS408.dir/src/sha-256/computation.cpp.s

# Object files for target CS408
CS408_OBJECTS = \
"CMakeFiles/CS408.dir/src/sha-256/SHA256.cpp.o" \
"CMakeFiles/CS408.dir/src/sha-256/preprocessing.cpp.o" \
"CMakeFiles/CS408.dir/src/sha-256/computation.cpp.o"

# External object files for target CS408
CS408_EXTERNAL_OBJECTS =

CS408: CMakeFiles/CS408.dir/src/sha-256/SHA256.cpp.o
CS408: CMakeFiles/CS408.dir/src/sha-256/preprocessing.cpp.o
CS408: CMakeFiles/CS408.dir/src/sha-256/computation.cpp.o
CS408: CMakeFiles/CS408.dir/build.make
CS408: CMakeFiles/CS408.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ross/Documents/Year4/CS408/CS408/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable CS408"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/CS408.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/CS408.dir/build: CS408
.PHONY : CMakeFiles/CS408.dir/build

CMakeFiles/CS408.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/CS408.dir/cmake_clean.cmake
.PHONY : CMakeFiles/CS408.dir/clean

CMakeFiles/CS408.dir/depend:
	cd /home/ross/Documents/Year4/CS408/CS408/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ross/Documents/Year4/CS408/CS408 /home/ross/Documents/Year4/CS408/CS408 /home/ross/Documents/Year4/CS408/CS408/cmake-build-debug /home/ross/Documents/Year4/CS408/CS408/cmake-build-debug /home/ross/Documents/Year4/CS408/CS408/cmake-build-debug/CMakeFiles/CS408.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/CS408.dir/depend
