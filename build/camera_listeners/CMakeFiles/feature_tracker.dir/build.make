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
CMAKE_SOURCE_DIR = /home/tg/my_slam/src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/tg/my_slam/build

# Include any dependencies generated for this target.
include camera_listeners/CMakeFiles/feature_tracker.dir/depend.make

# Include the progress variables for this target.
include camera_listeners/CMakeFiles/feature_tracker.dir/progress.make

# Include the compile flags for this target's objects.
include camera_listeners/CMakeFiles/feature_tracker.dir/flags.make

camera_listeners/CMakeFiles/feature_tracker.dir/src/feature_tracker.cpp.o: camera_listeners/CMakeFiles/feature_tracker.dir/flags.make
camera_listeners/CMakeFiles/feature_tracker.dir/src/feature_tracker.cpp.o: /home/tg/my_slam/src/camera_listeners/src/feature_tracker.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tg/my_slam/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object camera_listeners/CMakeFiles/feature_tracker.dir/src/feature_tracker.cpp.o"
	cd /home/tg/my_slam/build/camera_listeners && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/feature_tracker.dir/src/feature_tracker.cpp.o -c /home/tg/my_slam/src/camera_listeners/src/feature_tracker.cpp

camera_listeners/CMakeFiles/feature_tracker.dir/src/feature_tracker.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/feature_tracker.dir/src/feature_tracker.cpp.i"
	cd /home/tg/my_slam/build/camera_listeners && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/tg/my_slam/src/camera_listeners/src/feature_tracker.cpp > CMakeFiles/feature_tracker.dir/src/feature_tracker.cpp.i

camera_listeners/CMakeFiles/feature_tracker.dir/src/feature_tracker.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/feature_tracker.dir/src/feature_tracker.cpp.s"
	cd /home/tg/my_slam/build/camera_listeners && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/tg/my_slam/src/camera_listeners/src/feature_tracker.cpp -o CMakeFiles/feature_tracker.dir/src/feature_tracker.cpp.s

camera_listeners/CMakeFiles/feature_tracker.dir/src/feature_tracker.cpp.o.requires:

.PHONY : camera_listeners/CMakeFiles/feature_tracker.dir/src/feature_tracker.cpp.o.requires

camera_listeners/CMakeFiles/feature_tracker.dir/src/feature_tracker.cpp.o.provides: camera_listeners/CMakeFiles/feature_tracker.dir/src/feature_tracker.cpp.o.requires
	$(MAKE) -f camera_listeners/CMakeFiles/feature_tracker.dir/build.make camera_listeners/CMakeFiles/feature_tracker.dir/src/feature_tracker.cpp.o.provides.build
.PHONY : camera_listeners/CMakeFiles/feature_tracker.dir/src/feature_tracker.cpp.o.provides

camera_listeners/CMakeFiles/feature_tracker.dir/src/feature_tracker.cpp.o.provides.build: camera_listeners/CMakeFiles/feature_tracker.dir/src/feature_tracker.cpp.o


# Object files for target feature_tracker
feature_tracker_OBJECTS = \
"CMakeFiles/feature_tracker.dir/src/feature_tracker.cpp.o"

# External object files for target feature_tracker
feature_tracker_EXTERNAL_OBJECTS =

/home/tg/my_slam/devel/lib/camera_listeners/feature_tracker: camera_listeners/CMakeFiles/feature_tracker.dir/src/feature_tracker.cpp.o
/home/tg/my_slam/devel/lib/camera_listeners/feature_tracker: camera_listeners/CMakeFiles/feature_tracker.dir/build.make
/home/tg/my_slam/devel/lib/camera_listeners/feature_tracker: /opt/ros/kinetic/lib/libcv_bridge.so
/home/tg/my_slam/devel/lib/camera_listeners/feature_tracker: /opt/ros/kinetic/lib/x86_64-linux-gnu/libopencv_core3.so.3.3.1
/home/tg/my_slam/devel/lib/camera_listeners/feature_tracker: /opt/ros/kinetic/lib/x86_64-linux-gnu/libopencv_imgproc3.so.3.3.1
/home/tg/my_slam/devel/lib/camera_listeners/feature_tracker: /opt/ros/kinetic/lib/x86_64-linux-gnu/libopencv_imgcodecs3.so.3.3.1
/home/tg/my_slam/devel/lib/camera_listeners/feature_tracker: /opt/ros/kinetic/lib/libimage_transport.so
/home/tg/my_slam/devel/lib/camera_listeners/feature_tracker: /usr/lib/x86_64-linux-gnu/libtinyxml2.so
/home/tg/my_slam/devel/lib/camera_listeners/feature_tracker: /opt/ros/kinetic/lib/libclass_loader.so
/home/tg/my_slam/devel/lib/camera_listeners/feature_tracker: /usr/lib/libPocoFoundation.so
/home/tg/my_slam/devel/lib/camera_listeners/feature_tracker: /usr/lib/x86_64-linux-gnu/libdl.so
/home/tg/my_slam/devel/lib/camera_listeners/feature_tracker: /opt/ros/kinetic/lib/libroslib.so
/home/tg/my_slam/devel/lib/camera_listeners/feature_tracker: /opt/ros/kinetic/lib/librospack.so
/home/tg/my_slam/devel/lib/camera_listeners/feature_tracker: /usr/lib/x86_64-linux-gnu/libpython2.7.so
/home/tg/my_slam/devel/lib/camera_listeners/feature_tracker: /usr/lib/x86_64-linux-gnu/libboost_program_options.so
/home/tg/my_slam/devel/lib/camera_listeners/feature_tracker: /usr/lib/x86_64-linux-gnu/libtinyxml.so
/home/tg/my_slam/devel/lib/camera_listeners/feature_tracker: /opt/ros/kinetic/lib/libtf.so
/home/tg/my_slam/devel/lib/camera_listeners/feature_tracker: /opt/ros/kinetic/lib/libtf2_ros.so
/home/tg/my_slam/devel/lib/camera_listeners/feature_tracker: /opt/ros/kinetic/lib/libactionlib.so
/home/tg/my_slam/devel/lib/camera_listeners/feature_tracker: /opt/ros/kinetic/lib/libmessage_filters.so
/home/tg/my_slam/devel/lib/camera_listeners/feature_tracker: /opt/ros/kinetic/lib/libroscpp.so
/home/tg/my_slam/devel/lib/camera_listeners/feature_tracker: /usr/lib/x86_64-linux-gnu/libboost_filesystem.so
/home/tg/my_slam/devel/lib/camera_listeners/feature_tracker: /usr/lib/x86_64-linux-gnu/libboost_signals.so
/home/tg/my_slam/devel/lib/camera_listeners/feature_tracker: /opt/ros/kinetic/lib/libxmlrpcpp.so
/home/tg/my_slam/devel/lib/camera_listeners/feature_tracker: /opt/ros/kinetic/lib/libtf2.so
/home/tg/my_slam/devel/lib/camera_listeners/feature_tracker: /opt/ros/kinetic/lib/libroscpp_serialization.so
/home/tg/my_slam/devel/lib/camera_listeners/feature_tracker: /opt/ros/kinetic/lib/librosconsole.so
/home/tg/my_slam/devel/lib/camera_listeners/feature_tracker: /opt/ros/kinetic/lib/librosconsole_log4cxx.so
/home/tg/my_slam/devel/lib/camera_listeners/feature_tracker: /opt/ros/kinetic/lib/librosconsole_backend_interface.so
/home/tg/my_slam/devel/lib/camera_listeners/feature_tracker: /usr/lib/x86_64-linux-gnu/liblog4cxx.so
/home/tg/my_slam/devel/lib/camera_listeners/feature_tracker: /usr/lib/x86_64-linux-gnu/libboost_regex.so
/home/tg/my_slam/devel/lib/camera_listeners/feature_tracker: /opt/ros/kinetic/lib/librostime.so
/home/tg/my_slam/devel/lib/camera_listeners/feature_tracker: /opt/ros/kinetic/lib/libcpp_common.so
/home/tg/my_slam/devel/lib/camera_listeners/feature_tracker: /usr/lib/x86_64-linux-gnu/libboost_system.so
/home/tg/my_slam/devel/lib/camera_listeners/feature_tracker: /usr/lib/x86_64-linux-gnu/libboost_thread.so
/home/tg/my_slam/devel/lib/camera_listeners/feature_tracker: /usr/lib/x86_64-linux-gnu/libboost_chrono.so
/home/tg/my_slam/devel/lib/camera_listeners/feature_tracker: /usr/lib/x86_64-linux-gnu/libboost_date_time.so
/home/tg/my_slam/devel/lib/camera_listeners/feature_tracker: /usr/lib/x86_64-linux-gnu/libboost_atomic.so
/home/tg/my_slam/devel/lib/camera_listeners/feature_tracker: /usr/lib/x86_64-linux-gnu/libpthread.so
/home/tg/my_slam/devel/lib/camera_listeners/feature_tracker: /usr/lib/x86_64-linux-gnu/libconsole_bridge.so
/home/tg/my_slam/devel/lib/camera_listeners/feature_tracker: /opt/ros/kinetic/lib/x86_64-linux-gnu/libopencv_highgui3.so.3.3.1
/home/tg/my_slam/devel/lib/camera_listeners/feature_tracker: /opt/ros/kinetic/lib/x86_64-linux-gnu/libopencv_videoio3.so.3.3.1
/home/tg/my_slam/devel/lib/camera_listeners/feature_tracker: /opt/ros/kinetic/lib/x86_64-linux-gnu/libopencv_imgcodecs3.so.3.3.1
/home/tg/my_slam/devel/lib/camera_listeners/feature_tracker: /opt/ros/kinetic/lib/x86_64-linux-gnu/libopencv_imgproc3.so.3.3.1
/home/tg/my_slam/devel/lib/camera_listeners/feature_tracker: /opt/ros/kinetic/lib/x86_64-linux-gnu/libopencv_core3.so.3.3.1
/home/tg/my_slam/devel/lib/camera_listeners/feature_tracker: camera_listeners/CMakeFiles/feature_tracker.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/tg/my_slam/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable /home/tg/my_slam/devel/lib/camera_listeners/feature_tracker"
	cd /home/tg/my_slam/build/camera_listeners && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/feature_tracker.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
camera_listeners/CMakeFiles/feature_tracker.dir/build: /home/tg/my_slam/devel/lib/camera_listeners/feature_tracker

.PHONY : camera_listeners/CMakeFiles/feature_tracker.dir/build

camera_listeners/CMakeFiles/feature_tracker.dir/requires: camera_listeners/CMakeFiles/feature_tracker.dir/src/feature_tracker.cpp.o.requires

.PHONY : camera_listeners/CMakeFiles/feature_tracker.dir/requires

camera_listeners/CMakeFiles/feature_tracker.dir/clean:
	cd /home/tg/my_slam/build/camera_listeners && $(CMAKE_COMMAND) -P CMakeFiles/feature_tracker.dir/cmake_clean.cmake
.PHONY : camera_listeners/CMakeFiles/feature_tracker.dir/clean

camera_listeners/CMakeFiles/feature_tracker.dir/depend:
	cd /home/tg/my_slam/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/tg/my_slam/src /home/tg/my_slam/src/camera_listeners /home/tg/my_slam/build /home/tg/my_slam/build/camera_listeners /home/tg/my_slam/build/camera_listeners/CMakeFiles/feature_tracker.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : camera_listeners/CMakeFiles/feature_tracker.dir/depend
