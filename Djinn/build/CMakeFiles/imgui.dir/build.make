# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.25

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
CMAKE_COMMAND = /Applications/CMake.app/Contents/bin/cmake

# The command to remove a file.
RM = /Applications/CMake.app/Contents/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/tsaperlein/Desktop/DJINN/Djinn

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/tsaperlein/Desktop/DJINN/Djinn/build

# Include any dependencies generated for this target.
include CMakeFiles/imgui.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/imgui.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/imgui.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/imgui.dir/flags.make

CMakeFiles/imgui.dir/external/imgui/imgui.cpp.o: CMakeFiles/imgui.dir/flags.make
CMakeFiles/imgui.dir/external/imgui/imgui.cpp.o: /Users/tsaperlein/Desktop/DJINN/Djinn/external/imgui/imgui.cpp
CMakeFiles/imgui.dir/external/imgui/imgui.cpp.o: CMakeFiles/imgui.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/tsaperlein/Desktop/DJINN/Djinn/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/imgui.dir/external/imgui/imgui.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/imgui.dir/external/imgui/imgui.cpp.o -MF CMakeFiles/imgui.dir/external/imgui/imgui.cpp.o.d -o CMakeFiles/imgui.dir/external/imgui/imgui.cpp.o -c /Users/tsaperlein/Desktop/DJINN/Djinn/external/imgui/imgui.cpp

CMakeFiles/imgui.dir/external/imgui/imgui.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/imgui.dir/external/imgui/imgui.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/tsaperlein/Desktop/DJINN/Djinn/external/imgui/imgui.cpp > CMakeFiles/imgui.dir/external/imgui/imgui.cpp.i

CMakeFiles/imgui.dir/external/imgui/imgui.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/imgui.dir/external/imgui/imgui.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/tsaperlein/Desktop/DJINN/Djinn/external/imgui/imgui.cpp -o CMakeFiles/imgui.dir/external/imgui/imgui.cpp.s

CMakeFiles/imgui.dir/external/imgui/imgui_draw.cpp.o: CMakeFiles/imgui.dir/flags.make
CMakeFiles/imgui.dir/external/imgui/imgui_draw.cpp.o: /Users/tsaperlein/Desktop/DJINN/Djinn/external/imgui/imgui_draw.cpp
CMakeFiles/imgui.dir/external/imgui/imgui_draw.cpp.o: CMakeFiles/imgui.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/tsaperlein/Desktop/DJINN/Djinn/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/imgui.dir/external/imgui/imgui_draw.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/imgui.dir/external/imgui/imgui_draw.cpp.o -MF CMakeFiles/imgui.dir/external/imgui/imgui_draw.cpp.o.d -o CMakeFiles/imgui.dir/external/imgui/imgui_draw.cpp.o -c /Users/tsaperlein/Desktop/DJINN/Djinn/external/imgui/imgui_draw.cpp

CMakeFiles/imgui.dir/external/imgui/imgui_draw.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/imgui.dir/external/imgui/imgui_draw.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/tsaperlein/Desktop/DJINN/Djinn/external/imgui/imgui_draw.cpp > CMakeFiles/imgui.dir/external/imgui/imgui_draw.cpp.i

CMakeFiles/imgui.dir/external/imgui/imgui_draw.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/imgui.dir/external/imgui/imgui_draw.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/tsaperlein/Desktop/DJINN/Djinn/external/imgui/imgui_draw.cpp -o CMakeFiles/imgui.dir/external/imgui/imgui_draw.cpp.s

CMakeFiles/imgui.dir/external/imgui/imgui_demo.cpp.o: CMakeFiles/imgui.dir/flags.make
CMakeFiles/imgui.dir/external/imgui/imgui_demo.cpp.o: /Users/tsaperlein/Desktop/DJINN/Djinn/external/imgui/imgui_demo.cpp
CMakeFiles/imgui.dir/external/imgui/imgui_demo.cpp.o: CMakeFiles/imgui.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/tsaperlein/Desktop/DJINN/Djinn/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/imgui.dir/external/imgui/imgui_demo.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/imgui.dir/external/imgui/imgui_demo.cpp.o -MF CMakeFiles/imgui.dir/external/imgui/imgui_demo.cpp.o.d -o CMakeFiles/imgui.dir/external/imgui/imgui_demo.cpp.o -c /Users/tsaperlein/Desktop/DJINN/Djinn/external/imgui/imgui_demo.cpp

CMakeFiles/imgui.dir/external/imgui/imgui_demo.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/imgui.dir/external/imgui/imgui_demo.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/tsaperlein/Desktop/DJINN/Djinn/external/imgui/imgui_demo.cpp > CMakeFiles/imgui.dir/external/imgui/imgui_demo.cpp.i

CMakeFiles/imgui.dir/external/imgui/imgui_demo.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/imgui.dir/external/imgui/imgui_demo.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/tsaperlein/Desktop/DJINN/Djinn/external/imgui/imgui_demo.cpp -o CMakeFiles/imgui.dir/external/imgui/imgui_demo.cpp.s

CMakeFiles/imgui.dir/external/imgui/imgui_tables.cpp.o: CMakeFiles/imgui.dir/flags.make
CMakeFiles/imgui.dir/external/imgui/imgui_tables.cpp.o: /Users/tsaperlein/Desktop/DJINN/Djinn/external/imgui/imgui_tables.cpp
CMakeFiles/imgui.dir/external/imgui/imgui_tables.cpp.o: CMakeFiles/imgui.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/tsaperlein/Desktop/DJINN/Djinn/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/imgui.dir/external/imgui/imgui_tables.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/imgui.dir/external/imgui/imgui_tables.cpp.o -MF CMakeFiles/imgui.dir/external/imgui/imgui_tables.cpp.o.d -o CMakeFiles/imgui.dir/external/imgui/imgui_tables.cpp.o -c /Users/tsaperlein/Desktop/DJINN/Djinn/external/imgui/imgui_tables.cpp

CMakeFiles/imgui.dir/external/imgui/imgui_tables.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/imgui.dir/external/imgui/imgui_tables.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/tsaperlein/Desktop/DJINN/Djinn/external/imgui/imgui_tables.cpp > CMakeFiles/imgui.dir/external/imgui/imgui_tables.cpp.i

CMakeFiles/imgui.dir/external/imgui/imgui_tables.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/imgui.dir/external/imgui/imgui_tables.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/tsaperlein/Desktop/DJINN/Djinn/external/imgui/imgui_tables.cpp -o CMakeFiles/imgui.dir/external/imgui/imgui_tables.cpp.s

CMakeFiles/imgui.dir/external/imgui/imgui_widgets.cpp.o: CMakeFiles/imgui.dir/flags.make
CMakeFiles/imgui.dir/external/imgui/imgui_widgets.cpp.o: /Users/tsaperlein/Desktop/DJINN/Djinn/external/imgui/imgui_widgets.cpp
CMakeFiles/imgui.dir/external/imgui/imgui_widgets.cpp.o: CMakeFiles/imgui.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/tsaperlein/Desktop/DJINN/Djinn/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/imgui.dir/external/imgui/imgui_widgets.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/imgui.dir/external/imgui/imgui_widgets.cpp.o -MF CMakeFiles/imgui.dir/external/imgui/imgui_widgets.cpp.o.d -o CMakeFiles/imgui.dir/external/imgui/imgui_widgets.cpp.o -c /Users/tsaperlein/Desktop/DJINN/Djinn/external/imgui/imgui_widgets.cpp

CMakeFiles/imgui.dir/external/imgui/imgui_widgets.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/imgui.dir/external/imgui/imgui_widgets.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/tsaperlein/Desktop/DJINN/Djinn/external/imgui/imgui_widgets.cpp > CMakeFiles/imgui.dir/external/imgui/imgui_widgets.cpp.i

CMakeFiles/imgui.dir/external/imgui/imgui_widgets.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/imgui.dir/external/imgui/imgui_widgets.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/tsaperlein/Desktop/DJINN/Djinn/external/imgui/imgui_widgets.cpp -o CMakeFiles/imgui.dir/external/imgui/imgui_widgets.cpp.s

CMakeFiles/imgui.dir/external/imgui/backends/imgui_impl_glfw.cpp.o: CMakeFiles/imgui.dir/flags.make
CMakeFiles/imgui.dir/external/imgui/backends/imgui_impl_glfw.cpp.o: /Users/tsaperlein/Desktop/DJINN/Djinn/external/imgui/backends/imgui_impl_glfw.cpp
CMakeFiles/imgui.dir/external/imgui/backends/imgui_impl_glfw.cpp.o: CMakeFiles/imgui.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/tsaperlein/Desktop/DJINN/Djinn/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/imgui.dir/external/imgui/backends/imgui_impl_glfw.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/imgui.dir/external/imgui/backends/imgui_impl_glfw.cpp.o -MF CMakeFiles/imgui.dir/external/imgui/backends/imgui_impl_glfw.cpp.o.d -o CMakeFiles/imgui.dir/external/imgui/backends/imgui_impl_glfw.cpp.o -c /Users/tsaperlein/Desktop/DJINN/Djinn/external/imgui/backends/imgui_impl_glfw.cpp

CMakeFiles/imgui.dir/external/imgui/backends/imgui_impl_glfw.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/imgui.dir/external/imgui/backends/imgui_impl_glfw.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/tsaperlein/Desktop/DJINN/Djinn/external/imgui/backends/imgui_impl_glfw.cpp > CMakeFiles/imgui.dir/external/imgui/backends/imgui_impl_glfw.cpp.i

CMakeFiles/imgui.dir/external/imgui/backends/imgui_impl_glfw.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/imgui.dir/external/imgui/backends/imgui_impl_glfw.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/tsaperlein/Desktop/DJINN/Djinn/external/imgui/backends/imgui_impl_glfw.cpp -o CMakeFiles/imgui.dir/external/imgui/backends/imgui_impl_glfw.cpp.s

CMakeFiles/imgui.dir/external/imgui/backends/imgui_impl_opengl3.cpp.o: CMakeFiles/imgui.dir/flags.make
CMakeFiles/imgui.dir/external/imgui/backends/imgui_impl_opengl3.cpp.o: /Users/tsaperlein/Desktop/DJINN/Djinn/external/imgui/backends/imgui_impl_opengl3.cpp
CMakeFiles/imgui.dir/external/imgui/backends/imgui_impl_opengl3.cpp.o: CMakeFiles/imgui.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/tsaperlein/Desktop/DJINN/Djinn/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/imgui.dir/external/imgui/backends/imgui_impl_opengl3.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/imgui.dir/external/imgui/backends/imgui_impl_opengl3.cpp.o -MF CMakeFiles/imgui.dir/external/imgui/backends/imgui_impl_opengl3.cpp.o.d -o CMakeFiles/imgui.dir/external/imgui/backends/imgui_impl_opengl3.cpp.o -c /Users/tsaperlein/Desktop/DJINN/Djinn/external/imgui/backends/imgui_impl_opengl3.cpp

CMakeFiles/imgui.dir/external/imgui/backends/imgui_impl_opengl3.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/imgui.dir/external/imgui/backends/imgui_impl_opengl3.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/tsaperlein/Desktop/DJINN/Djinn/external/imgui/backends/imgui_impl_opengl3.cpp > CMakeFiles/imgui.dir/external/imgui/backends/imgui_impl_opengl3.cpp.i

CMakeFiles/imgui.dir/external/imgui/backends/imgui_impl_opengl3.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/imgui.dir/external/imgui/backends/imgui_impl_opengl3.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/tsaperlein/Desktop/DJINN/Djinn/external/imgui/backends/imgui_impl_opengl3.cpp -o CMakeFiles/imgui.dir/external/imgui/backends/imgui_impl_opengl3.cpp.s

# Object files for target imgui
imgui_OBJECTS = \
"CMakeFiles/imgui.dir/external/imgui/imgui.cpp.o" \
"CMakeFiles/imgui.dir/external/imgui/imgui_draw.cpp.o" \
"CMakeFiles/imgui.dir/external/imgui/imgui_demo.cpp.o" \
"CMakeFiles/imgui.dir/external/imgui/imgui_tables.cpp.o" \
"CMakeFiles/imgui.dir/external/imgui/imgui_widgets.cpp.o" \
"CMakeFiles/imgui.dir/external/imgui/backends/imgui_impl_glfw.cpp.o" \
"CMakeFiles/imgui.dir/external/imgui/backends/imgui_impl_opengl3.cpp.o"

# External object files for target imgui
imgui_EXTERNAL_OBJECTS =

libimgui.a: CMakeFiles/imgui.dir/external/imgui/imgui.cpp.o
libimgui.a: CMakeFiles/imgui.dir/external/imgui/imgui_draw.cpp.o
libimgui.a: CMakeFiles/imgui.dir/external/imgui/imgui_demo.cpp.o
libimgui.a: CMakeFiles/imgui.dir/external/imgui/imgui_tables.cpp.o
libimgui.a: CMakeFiles/imgui.dir/external/imgui/imgui_widgets.cpp.o
libimgui.a: CMakeFiles/imgui.dir/external/imgui/backends/imgui_impl_glfw.cpp.o
libimgui.a: CMakeFiles/imgui.dir/external/imgui/backends/imgui_impl_opengl3.cpp.o
libimgui.a: CMakeFiles/imgui.dir/build.make
libimgui.a: CMakeFiles/imgui.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/tsaperlein/Desktop/DJINN/Djinn/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Linking CXX static library libimgui.a"
	$(CMAKE_COMMAND) -P CMakeFiles/imgui.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/imgui.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/imgui.dir/build: libimgui.a
.PHONY : CMakeFiles/imgui.dir/build

CMakeFiles/imgui.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/imgui.dir/cmake_clean.cmake
.PHONY : CMakeFiles/imgui.dir/clean

CMakeFiles/imgui.dir/depend:
	cd /Users/tsaperlein/Desktop/DJINN/Djinn/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/tsaperlein/Desktop/DJINN/Djinn /Users/tsaperlein/Desktop/DJINN/Djinn /Users/tsaperlein/Desktop/DJINN/Djinn/build /Users/tsaperlein/Desktop/DJINN/Djinn/build /Users/tsaperlein/Desktop/DJINN/Djinn/build/CMakeFiles/imgui.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/imgui.dir/depend

