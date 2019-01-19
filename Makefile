# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

# Default target executed when no arguments are given to make.
default_target: all

.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:


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
CMAKE_SOURCE_DIR = /home/preet/IIIT/2-2/Graphics/Assignments/1/jetpack-joyride

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/preet/IIIT/2-2/Graphics/Assignments/1/jetpack-joyride

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "No interactive CMake dialog available..."
	/usr/bin/cmake -E echo No\ interactive\ CMake\ dialog\ available.
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache

.PHONY : edit_cache/fast

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/usr/bin/cmake -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache

.PHONY : rebuild_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /home/preet/IIIT/2-2/Graphics/Assignments/1/jetpack-joyride/CMakeFiles /home/preet/IIIT/2-2/Graphics/Assignments/1/jetpack-joyride/CMakeFiles/progress.marks
	$(MAKE) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /home/preet/IIIT/2-2/Graphics/Assignments/1/jetpack-joyride/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean

.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named jetpack

# Build rule for target.
jetpack: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 jetpack
.PHONY : jetpack

# fast build rule for target.
jetpack/fast:
	$(MAKE) -f CMakeFiles/jetpack.dir/build.make CMakeFiles/jetpack.dir/build
.PHONY : jetpack/fast

src/ball.o: src/ball.cpp.o

.PHONY : src/ball.o

# target to build an object file
src/ball.cpp.o:
	$(MAKE) -f CMakeFiles/jetpack.dir/build.make CMakeFiles/jetpack.dir/src/ball.cpp.o
.PHONY : src/ball.cpp.o

src/ball.i: src/ball.cpp.i

.PHONY : src/ball.i

# target to preprocess a source file
src/ball.cpp.i:
	$(MAKE) -f CMakeFiles/jetpack.dir/build.make CMakeFiles/jetpack.dir/src/ball.cpp.i
.PHONY : src/ball.cpp.i

src/ball.s: src/ball.cpp.s

.PHONY : src/ball.s

# target to generate assembly for a file
src/ball.cpp.s:
	$(MAKE) -f CMakeFiles/jetpack.dir/build.make CMakeFiles/jetpack.dir/src/ball.cpp.s
.PHONY : src/ball.cpp.s

src/coin.o: src/coin.cpp.o

.PHONY : src/coin.o

# target to build an object file
src/coin.cpp.o:
	$(MAKE) -f CMakeFiles/jetpack.dir/build.make CMakeFiles/jetpack.dir/src/coin.cpp.o
.PHONY : src/coin.cpp.o

src/coin.i: src/coin.cpp.i

.PHONY : src/coin.i

# target to preprocess a source file
src/coin.cpp.i:
	$(MAKE) -f CMakeFiles/jetpack.dir/build.make CMakeFiles/jetpack.dir/src/coin.cpp.i
.PHONY : src/coin.cpp.i

src/coin.s: src/coin.cpp.s

.PHONY : src/coin.s

# target to generate assembly for a file
src/coin.cpp.s:
	$(MAKE) -f CMakeFiles/jetpack.dir/build.make CMakeFiles/jetpack.dir/src/coin.cpp.s
.PHONY : src/coin.cpp.s

src/color.o: src/color.cpp.o

.PHONY : src/color.o

# target to build an object file
src/color.cpp.o:
	$(MAKE) -f CMakeFiles/jetpack.dir/build.make CMakeFiles/jetpack.dir/src/color.cpp.o
.PHONY : src/color.cpp.o

src/color.i: src/color.cpp.i

.PHONY : src/color.i

# target to preprocess a source file
src/color.cpp.i:
	$(MAKE) -f CMakeFiles/jetpack.dir/build.make CMakeFiles/jetpack.dir/src/color.cpp.i
.PHONY : src/color.cpp.i

src/color.s: src/color.cpp.s

.PHONY : src/color.s

# target to generate assembly for a file
src/color.cpp.s:
	$(MAKE) -f CMakeFiles/jetpack.dir/build.make CMakeFiles/jetpack.dir/src/color.cpp.s
.PHONY : src/color.cpp.s

src/fireline.o: src/fireline.cpp.o

.PHONY : src/fireline.o

# target to build an object file
src/fireline.cpp.o:
	$(MAKE) -f CMakeFiles/jetpack.dir/build.make CMakeFiles/jetpack.dir/src/fireline.cpp.o
.PHONY : src/fireline.cpp.o

src/fireline.i: src/fireline.cpp.i

.PHONY : src/fireline.i

# target to preprocess a source file
src/fireline.cpp.i:
	$(MAKE) -f CMakeFiles/jetpack.dir/build.make CMakeFiles/jetpack.dir/src/fireline.cpp.i
.PHONY : src/fireline.cpp.i

src/fireline.s: src/fireline.cpp.s

.PHONY : src/fireline.s

# target to generate assembly for a file
src/fireline.cpp.s:
	$(MAKE) -f CMakeFiles/jetpack.dir/build.make CMakeFiles/jetpack.dir/src/fireline.cpp.s
.PHONY : src/fireline.cpp.s

src/input.o: src/input.cpp.o

.PHONY : src/input.o

# target to build an object file
src/input.cpp.o:
	$(MAKE) -f CMakeFiles/jetpack.dir/build.make CMakeFiles/jetpack.dir/src/input.cpp.o
.PHONY : src/input.cpp.o

src/input.i: src/input.cpp.i

.PHONY : src/input.i

# target to preprocess a source file
src/input.cpp.i:
	$(MAKE) -f CMakeFiles/jetpack.dir/build.make CMakeFiles/jetpack.dir/src/input.cpp.i
.PHONY : src/input.cpp.i

src/input.s: src/input.cpp.s

.PHONY : src/input.s

# target to generate assembly for a file
src/input.cpp.s:
	$(MAKE) -f CMakeFiles/jetpack.dir/build.make CMakeFiles/jetpack.dir/src/input.cpp.s
.PHONY : src/input.cpp.s

src/main.o: src/main.cpp.o

.PHONY : src/main.o

# target to build an object file
src/main.cpp.o:
	$(MAKE) -f CMakeFiles/jetpack.dir/build.make CMakeFiles/jetpack.dir/src/main.cpp.o
.PHONY : src/main.cpp.o

src/main.i: src/main.cpp.i

.PHONY : src/main.i

# target to preprocess a source file
src/main.cpp.i:
	$(MAKE) -f CMakeFiles/jetpack.dir/build.make CMakeFiles/jetpack.dir/src/main.cpp.i
.PHONY : src/main.cpp.i

src/main.s: src/main.cpp.s

.PHONY : src/main.s

# target to generate assembly for a file
src/main.cpp.s:
	$(MAKE) -f CMakeFiles/jetpack.dir/build.make CMakeFiles/jetpack.dir/src/main.cpp.s
.PHONY : src/main.cpp.s

src/nonedit.o: src/nonedit.cpp.o

.PHONY : src/nonedit.o

# target to build an object file
src/nonedit.cpp.o:
	$(MAKE) -f CMakeFiles/jetpack.dir/build.make CMakeFiles/jetpack.dir/src/nonedit.cpp.o
.PHONY : src/nonedit.cpp.o

src/nonedit.i: src/nonedit.cpp.i

.PHONY : src/nonedit.i

# target to preprocess a source file
src/nonedit.cpp.i:
	$(MAKE) -f CMakeFiles/jetpack.dir/build.make CMakeFiles/jetpack.dir/src/nonedit.cpp.i
.PHONY : src/nonedit.cpp.i

src/nonedit.s: src/nonedit.cpp.s

.PHONY : src/nonedit.s

# target to generate assembly for a file
src/nonedit.cpp.s:
	$(MAKE) -f CMakeFiles/jetpack.dir/build.make CMakeFiles/jetpack.dir/src/nonedit.cpp.s
.PHONY : src/nonedit.cpp.s

src/other_handlers.o: src/other_handlers.cpp.o

.PHONY : src/other_handlers.o

# target to build an object file
src/other_handlers.cpp.o:
	$(MAKE) -f CMakeFiles/jetpack.dir/build.make CMakeFiles/jetpack.dir/src/other_handlers.cpp.o
.PHONY : src/other_handlers.cpp.o

src/other_handlers.i: src/other_handlers.cpp.i

.PHONY : src/other_handlers.i

# target to preprocess a source file
src/other_handlers.cpp.i:
	$(MAKE) -f CMakeFiles/jetpack.dir/build.make CMakeFiles/jetpack.dir/src/other_handlers.cpp.i
.PHONY : src/other_handlers.cpp.i

src/other_handlers.s: src/other_handlers.cpp.s

.PHONY : src/other_handlers.s

# target to generate assembly for a file
src/other_handlers.cpp.s:
	$(MAKE) -f CMakeFiles/jetpack.dir/build.make CMakeFiles/jetpack.dir/src/other_handlers.cpp.s
.PHONY : src/other_handlers.cpp.s

src/platform.o: src/platform.cpp.o

.PHONY : src/platform.o

# target to build an object file
src/platform.cpp.o:
	$(MAKE) -f CMakeFiles/jetpack.dir/build.make CMakeFiles/jetpack.dir/src/platform.cpp.o
.PHONY : src/platform.cpp.o

src/platform.i: src/platform.cpp.i

.PHONY : src/platform.i

# target to preprocess a source file
src/platform.cpp.i:
	$(MAKE) -f CMakeFiles/jetpack.dir/build.make CMakeFiles/jetpack.dir/src/platform.cpp.i
.PHONY : src/platform.cpp.i

src/platform.s: src/platform.cpp.s

.PHONY : src/platform.s

# target to generate assembly for a file
src/platform.cpp.s:
	$(MAKE) -f CMakeFiles/jetpack.dir/build.make CMakeFiles/jetpack.dir/src/platform.cpp.s
.PHONY : src/platform.cpp.s

src/propulsion.o: src/propulsion.cpp.o

.PHONY : src/propulsion.o

# target to build an object file
src/propulsion.cpp.o:
	$(MAKE) -f CMakeFiles/jetpack.dir/build.make CMakeFiles/jetpack.dir/src/propulsion.cpp.o
.PHONY : src/propulsion.cpp.o

src/propulsion.i: src/propulsion.cpp.i

.PHONY : src/propulsion.i

# target to preprocess a source file
src/propulsion.cpp.i:
	$(MAKE) -f CMakeFiles/jetpack.dir/build.make CMakeFiles/jetpack.dir/src/propulsion.cpp.i
.PHONY : src/propulsion.cpp.i

src/propulsion.s: src/propulsion.cpp.s

.PHONY : src/propulsion.s

# target to generate assembly for a file
src/propulsion.cpp.s:
	$(MAKE) -f CMakeFiles/jetpack.dir/build.make CMakeFiles/jetpack.dir/src/propulsion.cpp.s
.PHONY : src/propulsion.cpp.s

src/timer.o: src/timer.cpp.o

.PHONY : src/timer.o

# target to build an object file
src/timer.cpp.o:
	$(MAKE) -f CMakeFiles/jetpack.dir/build.make CMakeFiles/jetpack.dir/src/timer.cpp.o
.PHONY : src/timer.cpp.o

src/timer.i: src/timer.cpp.i

.PHONY : src/timer.i

# target to preprocess a source file
src/timer.cpp.i:
	$(MAKE) -f CMakeFiles/jetpack.dir/build.make CMakeFiles/jetpack.dir/src/timer.cpp.i
.PHONY : src/timer.cpp.i

src/timer.s: src/timer.cpp.s

.PHONY : src/timer.s

# target to generate assembly for a file
src/timer.cpp.s:
	$(MAKE) -f CMakeFiles/jetpack.dir/build.make CMakeFiles/jetpack.dir/src/timer.cpp.s
.PHONY : src/timer.cpp.s

src/waterball.o: src/waterball.cpp.o

.PHONY : src/waterball.o

# target to build an object file
src/waterball.cpp.o:
	$(MAKE) -f CMakeFiles/jetpack.dir/build.make CMakeFiles/jetpack.dir/src/waterball.cpp.o
.PHONY : src/waterball.cpp.o

src/waterball.i: src/waterball.cpp.i

.PHONY : src/waterball.i

# target to preprocess a source file
src/waterball.cpp.i:
	$(MAKE) -f CMakeFiles/jetpack.dir/build.make CMakeFiles/jetpack.dir/src/waterball.cpp.i
.PHONY : src/waterball.cpp.i

src/waterball.s: src/waterball.cpp.s

.PHONY : src/waterball.s

# target to generate assembly for a file
src/waterball.cpp.s:
	$(MAKE) -f CMakeFiles/jetpack.dir/build.make CMakeFiles/jetpack.dir/src/waterball.cpp.s
.PHONY : src/waterball.cpp.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... edit_cache"
	@echo "... jetpack"
	@echo "... rebuild_cache"
	@echo "... src/ball.o"
	@echo "... src/ball.i"
	@echo "... src/ball.s"
	@echo "... src/coin.o"
	@echo "... src/coin.i"
	@echo "... src/coin.s"
	@echo "... src/color.o"
	@echo "... src/color.i"
	@echo "... src/color.s"
	@echo "... src/fireline.o"
	@echo "... src/fireline.i"
	@echo "... src/fireline.s"
	@echo "... src/input.o"
	@echo "... src/input.i"
	@echo "... src/input.s"
	@echo "... src/main.o"
	@echo "... src/main.i"
	@echo "... src/main.s"
	@echo "... src/nonedit.o"
	@echo "... src/nonedit.i"
	@echo "... src/nonedit.s"
	@echo "... src/other_handlers.o"
	@echo "... src/other_handlers.i"
	@echo "... src/other_handlers.s"
	@echo "... src/platform.o"
	@echo "... src/platform.i"
	@echo "... src/platform.s"
	@echo "... src/propulsion.o"
	@echo "... src/propulsion.i"
	@echo "... src/propulsion.s"
	@echo "... src/timer.o"
	@echo "... src/timer.i"
	@echo "... src/timer.s"
	@echo "... src/waterball.o"
	@echo "... src/waterball.i"
	@echo "... src/waterball.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system
