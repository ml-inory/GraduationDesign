# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.8

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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.8.0/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.8.0/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/rzyang/GraduationDesign/ev_face

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/rzyang/GraduationDesign/ev_face/build

# Include any dependencies generated for this target.
include CMakeFiles/ev_face.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/ev_face.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/ev_face.dir/flags.make

CMakeFiles/ev_face.dir/main.cpp.o: CMakeFiles/ev_face.dir/flags.make
CMakeFiles/ev_face.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/rzyang/GraduationDesign/ev_face/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/ev_face.dir/main.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ev_face.dir/main.cpp.o -c /Users/rzyang/GraduationDesign/ev_face/main.cpp

CMakeFiles/ev_face.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ev_face.dir/main.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/rzyang/GraduationDesign/ev_face/main.cpp > CMakeFiles/ev_face.dir/main.cpp.i

CMakeFiles/ev_face.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ev_face.dir/main.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/rzyang/GraduationDesign/ev_face/main.cpp -o CMakeFiles/ev_face.dir/main.cpp.s

CMakeFiles/ev_face.dir/main.cpp.o.requires:

.PHONY : CMakeFiles/ev_face.dir/main.cpp.o.requires

CMakeFiles/ev_face.dir/main.cpp.o.provides: CMakeFiles/ev_face.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/ev_face.dir/build.make CMakeFiles/ev_face.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/ev_face.dir/main.cpp.o.provides

CMakeFiles/ev_face.dir/main.cpp.o.provides.build: CMakeFiles/ev_face.dir/main.cpp.o


CMakeFiles/ev_face.dir/src/Cap_Controller.cpp.o: CMakeFiles/ev_face.dir/flags.make
CMakeFiles/ev_face.dir/src/Cap_Controller.cpp.o: ../src/Cap_Controller.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/rzyang/GraduationDesign/ev_face/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/ev_face.dir/src/Cap_Controller.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ev_face.dir/src/Cap_Controller.cpp.o -c /Users/rzyang/GraduationDesign/ev_face/src/Cap_Controller.cpp

CMakeFiles/ev_face.dir/src/Cap_Controller.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ev_face.dir/src/Cap_Controller.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/rzyang/GraduationDesign/ev_face/src/Cap_Controller.cpp > CMakeFiles/ev_face.dir/src/Cap_Controller.cpp.i

CMakeFiles/ev_face.dir/src/Cap_Controller.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ev_face.dir/src/Cap_Controller.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/rzyang/GraduationDesign/ev_face/src/Cap_Controller.cpp -o CMakeFiles/ev_face.dir/src/Cap_Controller.cpp.s

CMakeFiles/ev_face.dir/src/Cap_Controller.cpp.o.requires:

.PHONY : CMakeFiles/ev_face.dir/src/Cap_Controller.cpp.o.requires

CMakeFiles/ev_face.dir/src/Cap_Controller.cpp.o.provides: CMakeFiles/ev_face.dir/src/Cap_Controller.cpp.o.requires
	$(MAKE) -f CMakeFiles/ev_face.dir/build.make CMakeFiles/ev_face.dir/src/Cap_Controller.cpp.o.provides.build
.PHONY : CMakeFiles/ev_face.dir/src/Cap_Controller.cpp.o.provides

CMakeFiles/ev_face.dir/src/Cap_Controller.cpp.o.provides.build: CMakeFiles/ev_face.dir/src/Cap_Controller.cpp.o


# Object files for target ev_face
ev_face_OBJECTS = \
"CMakeFiles/ev_face.dir/main.cpp.o" \
"CMakeFiles/ev_face.dir/src/Cap_Controller.cpp.o"

# External object files for target ev_face
ev_face_EXTERNAL_OBJECTS =

ev_face: CMakeFiles/ev_face.dir/main.cpp.o
ev_face: CMakeFiles/ev_face.dir/src/Cap_Controller.cpp.o
ev_face: CMakeFiles/ev_face.dir/build.make
ev_face: /Users/rzyang/SeetaFaceEngine/FaceDetection/build/libseeta_facedet_lib.dylib
ev_face: /Users/rzyang/SeetaFaceEngine/FaceAlignment/build/libseeta_fa_lib.dylib
ev_face: /Users/rzyang/SeetaFaceEngine/FaceIdentification/build/libviplnet.dylib
ev_face: /usr/local/lib/libopencv_stitching.3.2.0.dylib
ev_face: /usr/local/lib/libopencv_superres.3.2.0.dylib
ev_face: /usr/local/lib/libopencv_videostab.3.2.0.dylib
ev_face: /usr/local/lib/libopencv_aruco.3.2.0.dylib
ev_face: /usr/local/lib/libopencv_bgsegm.3.2.0.dylib
ev_face: /usr/local/lib/libopencv_bioinspired.3.2.0.dylib
ev_face: /usr/local/lib/libopencv_ccalib.3.2.0.dylib
ev_face: /usr/local/lib/libopencv_datasets.3.2.0.dylib
ev_face: /usr/local/lib/libopencv_dpm.3.2.0.dylib
ev_face: /usr/local/lib/libopencv_face.3.2.0.dylib
ev_face: /usr/local/lib/libopencv_fuzzy.3.2.0.dylib
ev_face: /usr/local/lib/libopencv_hdf.3.2.0.dylib
ev_face: /usr/local/lib/libopencv_line_descriptor.3.2.0.dylib
ev_face: /usr/local/lib/libopencv_optflow.3.2.0.dylib
ev_face: /usr/local/lib/libopencv_plot.3.2.0.dylib
ev_face: /usr/local/lib/libopencv_reg.3.2.0.dylib
ev_face: /usr/local/lib/libopencv_saliency.3.2.0.dylib
ev_face: /usr/local/lib/libopencv_stereo.3.2.0.dylib
ev_face: /usr/local/lib/libopencv_structured_light.3.2.0.dylib
ev_face: /usr/local/lib/libopencv_surface_matching.3.2.0.dylib
ev_face: /usr/local/lib/libopencv_text.3.2.0.dylib
ev_face: /usr/local/lib/libopencv_xfeatures2d.3.2.0.dylib
ev_face: /usr/local/lib/libopencv_ximgproc.3.2.0.dylib
ev_face: /usr/local/lib/libopencv_xobjdetect.3.2.0.dylib
ev_face: /usr/local/lib/libopencv_xphoto.3.2.0.dylib
ev_face: /usr/local/lib/libglog.dylib
ev_face: /usr/local/lib/libopencv_shape.3.2.0.dylib
ev_face: /usr/local/lib/libopencv_video.3.2.0.dylib
ev_face: /usr/local/lib/libopencv_phase_unwrapping.3.2.0.dylib
ev_face: /usr/local/lib/libopencv_rgbd.3.2.0.dylib
ev_face: /usr/local/lib/libopencv_calib3d.3.2.0.dylib
ev_face: /usr/local/lib/libopencv_features2d.3.2.0.dylib
ev_face: /usr/local/lib/libopencv_flann.3.2.0.dylib
ev_face: /usr/local/lib/libopencv_objdetect.3.2.0.dylib
ev_face: /usr/local/lib/libopencv_ml.3.2.0.dylib
ev_face: /usr/local/lib/libopencv_highgui.3.2.0.dylib
ev_face: /usr/local/lib/libopencv_photo.3.2.0.dylib
ev_face: /usr/local/lib/libopencv_videoio.3.2.0.dylib
ev_face: /usr/local/lib/libopencv_imgcodecs.3.2.0.dylib
ev_face: /usr/local/lib/libopencv_imgproc.3.2.0.dylib
ev_face: /usr/local/lib/libopencv_core.3.2.0.dylib
ev_face: CMakeFiles/ev_face.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/rzyang/GraduationDesign/ev_face/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable ev_face"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ev_face.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/ev_face.dir/build: ev_face

.PHONY : CMakeFiles/ev_face.dir/build

CMakeFiles/ev_face.dir/requires: CMakeFiles/ev_face.dir/main.cpp.o.requires
CMakeFiles/ev_face.dir/requires: CMakeFiles/ev_face.dir/src/Cap_Controller.cpp.o.requires

.PHONY : CMakeFiles/ev_face.dir/requires

CMakeFiles/ev_face.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/ev_face.dir/cmake_clean.cmake
.PHONY : CMakeFiles/ev_face.dir/clean

CMakeFiles/ev_face.dir/depend:
	cd /Users/rzyang/GraduationDesign/ev_face/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/rzyang/GraduationDesign/ev_face /Users/rzyang/GraduationDesign/ev_face /Users/rzyang/GraduationDesign/ev_face/build /Users/rzyang/GraduationDesign/ev_face/build /Users/rzyang/GraduationDesign/ev_face/build/CMakeFiles/ev_face.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/ev_face.dir/depend

