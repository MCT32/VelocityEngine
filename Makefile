# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.25

# Default target executed when no arguments are given to make.
default_target: all
.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/mct32/Repos/COOM

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/mct32/Repos/COOM

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake cache editor..."
	/usr/bin/ccmake -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache
.PHONY : edit_cache/fast

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/usr/bin/cmake --regenerate-during-build -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache
.PHONY : rebuild_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /home/mct32/Repos/COOM/CMakeFiles /home/mct32/Repos/COOM//CMakeFiles/progress.marks
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /home/mct32/Repos/COOM/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean
.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named COOM

# Build rule for target.
COOM: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 COOM
.PHONY : COOM

# fast build rule for target.
COOM/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/COOM.dir/build.make CMakeFiles/COOM.dir/build
.PHONY : COOM/fast

color.o: color.cpp.o
.PHONY : color.o

# target to build an object file
color.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/COOM.dir/build.make CMakeFiles/COOM.dir/color.cpp.o
.PHONY : color.cpp.o

color.i: color.cpp.i
.PHONY : color.i

# target to preprocess a source file
color.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/COOM.dir/build.make CMakeFiles/COOM.dir/color.cpp.i
.PHONY : color.cpp.i

color.s: color.cpp.s
.PHONY : color.s

# target to generate assembly for a file
color.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/COOM.dir/build.make CMakeFiles/COOM.dir/color.cpp.s
.PHONY : color.cpp.s

draw.o: draw.cpp.o
.PHONY : draw.o

# target to build an object file
draw.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/COOM.dir/build.make CMakeFiles/COOM.dir/draw.cpp.o
.PHONY : draw.cpp.o

draw.i: draw.cpp.i
.PHONY : draw.i

# target to preprocess a source file
draw.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/COOM.dir/build.make CMakeFiles/COOM.dir/draw.cpp.i
.PHONY : draw.cpp.i

draw.s: draw.cpp.s
.PHONY : draw.s

# target to generate assembly for a file
draw.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/COOM.dir/build.make CMakeFiles/COOM.dir/draw.cpp.s
.PHONY : draw.cpp.s

load.o: load.cpp.o
.PHONY : load.o

# target to build an object file
load.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/COOM.dir/build.make CMakeFiles/COOM.dir/load.cpp.o
.PHONY : load.cpp.o

load.i: load.cpp.i
.PHONY : load.i

# target to preprocess a source file
load.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/COOM.dir/build.make CMakeFiles/COOM.dir/load.cpp.i
.PHONY : load.cpp.i

load.s: load.cpp.s
.PHONY : load.s

# target to generate assembly for a file
load.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/COOM.dir/build.make CMakeFiles/COOM.dir/load.cpp.s
.PHONY : load.cpp.s

logging.o: logging.cpp.o
.PHONY : logging.o

# target to build an object file
logging.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/COOM.dir/build.make CMakeFiles/COOM.dir/logging.cpp.o
.PHONY : logging.cpp.o

logging.i: logging.cpp.i
.PHONY : logging.i

# target to preprocess a source file
logging.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/COOM.dir/build.make CMakeFiles/COOM.dir/logging.cpp.i
.PHONY : logging.cpp.i

logging.s: logging.cpp.s
.PHONY : logging.s

# target to generate assembly for a file
logging.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/COOM.dir/build.make CMakeFiles/COOM.dir/logging.cpp.s
.PHONY : logging.cpp.s

main.o: main.cpp.o
.PHONY : main.o

# target to build an object file
main.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/COOM.dir/build.make CMakeFiles/COOM.dir/main.cpp.o
.PHONY : main.cpp.o

main.i: main.cpp.i
.PHONY : main.i

# target to preprocess a source file
main.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/COOM.dir/build.make CMakeFiles/COOM.dir/main.cpp.i
.PHONY : main.cpp.i

main.s: main.cpp.s
.PHONY : main.s

# target to generate assembly for a file
main.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/COOM.dir/build.make CMakeFiles/COOM.dir/main.cpp.s
.PHONY : main.cpp.s

player.o: player.cpp.o
.PHONY : player.o

# target to build an object file
player.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/COOM.dir/build.make CMakeFiles/COOM.dir/player.cpp.o
.PHONY : player.cpp.o

player.i: player.cpp.i
.PHONY : player.i

# target to preprocess a source file
player.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/COOM.dir/build.make CMakeFiles/COOM.dir/player.cpp.i
.PHONY : player.cpp.i

player.s: player.cpp.s
.PHONY : player.s

# target to generate assembly for a file
player.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/COOM.dir/build.make CMakeFiles/COOM.dir/player.cpp.s
.PHONY : player.cpp.s

render.o: render.cpp.o
.PHONY : render.o

# target to build an object file
render.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/COOM.dir/build.make CMakeFiles/COOM.dir/render.cpp.o
.PHONY : render.cpp.o

render.i: render.cpp.i
.PHONY : render.i

# target to preprocess a source file
render.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/COOM.dir/build.make CMakeFiles/COOM.dir/render.cpp.i
.PHONY : render.cpp.i

render.s: render.cpp.s
.PHONY : render.s

# target to generate assembly for a file
render.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/COOM.dir/build.make CMakeFiles/COOM.dir/render.cpp.s
.PHONY : render.cpp.s

util.o: util.cpp.o
.PHONY : util.o

# target to build an object file
util.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/COOM.dir/build.make CMakeFiles/COOM.dir/util.cpp.o
.PHONY : util.cpp.o

util.i: util.cpp.i
.PHONY : util.i

# target to preprocess a source file
util.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/COOM.dir/build.make CMakeFiles/COOM.dir/util.cpp.i
.PHONY : util.cpp.i

util.s: util.cpp.s
.PHONY : util.s

# target to generate assembly for a file
util.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/COOM.dir/build.make CMakeFiles/COOM.dir/util.cpp.s
.PHONY : util.cpp.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... edit_cache"
	@echo "... rebuild_cache"
	@echo "... COOM"
	@echo "... color.o"
	@echo "... color.i"
	@echo "... color.s"
	@echo "... draw.o"
	@echo "... draw.i"
	@echo "... draw.s"
	@echo "... load.o"
	@echo "... load.i"
	@echo "... load.s"
	@echo "... logging.o"
	@echo "... logging.i"
	@echo "... logging.s"
	@echo "... main.o"
	@echo "... main.i"
	@echo "... main.s"
	@echo "... player.o"
	@echo "... player.i"
	@echo "... player.s"
	@echo "... render.o"
	@echo "... render.i"
	@echo "... render.s"
	@echo "... util.o"
	@echo "... util.i"
	@echo "... util.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

