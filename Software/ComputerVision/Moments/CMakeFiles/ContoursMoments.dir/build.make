# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = /usr/bin/ccmake

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/pi/Desktop/opencv/samples/cpp/tutorial_code/ShapeDescriptors/Moments

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/pi/Desktop/opencv/samples/cpp/tutorial_code/ShapeDescriptors/Moments

# Include any dependencies generated for this target.
include CMakeFiles/ContoursMoments.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/ContoursMoments.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/ContoursMoments.dir/flags.make

CMakeFiles/ContoursMoments.dir/moments_demo_cam.cpp.o: CMakeFiles/ContoursMoments.dir/flags.make
CMakeFiles/ContoursMoments.dir/moments_demo_cam.cpp.o: moments_demo_cam.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/pi/Desktop/opencv/samples/cpp/tutorial_code/ShapeDescriptors/Moments/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/ContoursMoments.dir/moments_demo_cam.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/ContoursMoments.dir/moments_demo_cam.cpp.o -c /home/pi/Desktop/opencv/samples/cpp/tutorial_code/ShapeDescriptors/Moments/moments_demo_cam.cpp

CMakeFiles/ContoursMoments.dir/moments_demo_cam.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ContoursMoments.dir/moments_demo_cam.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/pi/Desktop/opencv/samples/cpp/tutorial_code/ShapeDescriptors/Moments/moments_demo_cam.cpp > CMakeFiles/ContoursMoments.dir/moments_demo_cam.cpp.i

CMakeFiles/ContoursMoments.dir/moments_demo_cam.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ContoursMoments.dir/moments_demo_cam.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/pi/Desktop/opencv/samples/cpp/tutorial_code/ShapeDescriptors/Moments/moments_demo_cam.cpp -o CMakeFiles/ContoursMoments.dir/moments_demo_cam.cpp.s

CMakeFiles/ContoursMoments.dir/moments_demo_cam.cpp.o.requires:
.PHONY : CMakeFiles/ContoursMoments.dir/moments_demo_cam.cpp.o.requires

CMakeFiles/ContoursMoments.dir/moments_demo_cam.cpp.o.provides: CMakeFiles/ContoursMoments.dir/moments_demo_cam.cpp.o.requires
	$(MAKE) -f CMakeFiles/ContoursMoments.dir/build.make CMakeFiles/ContoursMoments.dir/moments_demo_cam.cpp.o.provides.build
.PHONY : CMakeFiles/ContoursMoments.dir/moments_demo_cam.cpp.o.provides

CMakeFiles/ContoursMoments.dir/moments_demo_cam.cpp.o.provides.build: CMakeFiles/ContoursMoments.dir/moments_demo_cam.cpp.o

# Object files for target ContoursMoments
ContoursMoments_OBJECTS = \
"CMakeFiles/ContoursMoments.dir/moments_demo_cam.cpp.o"

# External object files for target ContoursMoments
ContoursMoments_EXTERNAL_OBJECTS =

ContoursMoments: CMakeFiles/ContoursMoments.dir/moments_demo_cam.cpp.o
ContoursMoments: CMakeFiles/ContoursMoments.dir/build.make
ContoursMoments: /usr/local/lib/libopencv_videostab.so.3.0.0
ContoursMoments: /usr/local/lib/libopencv_videoio.so.3.0.0
ContoursMoments: /usr/local/lib/libopencv_video.so.3.0.0
ContoursMoments: /usr/local/lib/libopencv_ts.a
ContoursMoments: /usr/local/lib/libopencv_superres.so.3.0.0
ContoursMoments: /usr/local/lib/libopencv_stitching.so.3.0.0
ContoursMoments: /usr/local/lib/libopencv_shape.so.3.0.0
ContoursMoments: /usr/local/lib/libopencv_photo.so.3.0.0
ContoursMoments: /usr/local/lib/libopencv_objdetect.so.3.0.0
ContoursMoments: /usr/local/lib/libopencv_ml.so.3.0.0
ContoursMoments: /usr/local/lib/libopencv_imgproc.so.3.0.0
ContoursMoments: /usr/local/lib/libopencv_imgcodecs.so.3.0.0
ContoursMoments: /usr/local/lib/libopencv_highgui.so.3.0.0
ContoursMoments: /usr/local/lib/libopencv_flann.so.3.0.0
ContoursMoments: /usr/local/lib/libopencv_features2d.so.3.0.0
ContoursMoments: /usr/local/lib/libopencv_core.so.3.0.0
ContoursMoments: /usr/local/lib/libopencv_calib3d.so.3.0.0
ContoursMoments: /usr/local/lib/libopencv_features2d.so.3.0.0
ContoursMoments: /usr/local/lib/libopencv_ml.so.3.0.0
ContoursMoments: /usr/local/lib/libopencv_highgui.so.3.0.0
ContoursMoments: /usr/local/lib/libopencv_videoio.so.3.0.0
ContoursMoments: /usr/local/lib/libopencv_imgcodecs.so.3.0.0
ContoursMoments: /usr/local/lib/libopencv_flann.so.3.0.0
ContoursMoments: /usr/local/lib/libopencv_video.so.3.0.0
ContoursMoments: /usr/local/lib/libopencv_imgproc.so.3.0.0
ContoursMoments: /usr/local/lib/libopencv_core.so.3.0.0
ContoursMoments: CMakeFiles/ContoursMoments.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable ContoursMoments"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ContoursMoments.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/ContoursMoments.dir/build: ContoursMoments
.PHONY : CMakeFiles/ContoursMoments.dir/build

CMakeFiles/ContoursMoments.dir/requires: CMakeFiles/ContoursMoments.dir/moments_demo_cam.cpp.o.requires
.PHONY : CMakeFiles/ContoursMoments.dir/requires

CMakeFiles/ContoursMoments.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/ContoursMoments.dir/cmake_clean.cmake
.PHONY : CMakeFiles/ContoursMoments.dir/clean

CMakeFiles/ContoursMoments.dir/depend:
	cd /home/pi/Desktop/opencv/samples/cpp/tutorial_code/ShapeDescriptors/Moments && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/pi/Desktop/opencv/samples/cpp/tutorial_code/ShapeDescriptors/Moments /home/pi/Desktop/opencv/samples/cpp/tutorial_code/ShapeDescriptors/Moments /home/pi/Desktop/opencv/samples/cpp/tutorial_code/ShapeDescriptors/Moments /home/pi/Desktop/opencv/samples/cpp/tutorial_code/ShapeDescriptors/Moments /home/pi/Desktop/opencv/samples/cpp/tutorial_code/ShapeDescriptors/Moments/CMakeFiles/ContoursMoments.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/ContoursMoments.dir/depend

