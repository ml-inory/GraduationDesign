# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.7

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
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/inory/GraduationDesign/ev_face

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/inory/GraduationDesign/ev_face/build

# Include any dependencies generated for this target.
include CMakeFiles/ev_face.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/ev_face.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/ev_face.dir/flags.make

CMakeFiles/ev_face.dir/main.cpp.o: CMakeFiles/ev_face.dir/flags.make
CMakeFiles/ev_face.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/inory/GraduationDesign/ev_face/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/ev_face.dir/main.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ev_face.dir/main.cpp.o -c /home/inory/GraduationDesign/ev_face/main.cpp

CMakeFiles/ev_face.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ev_face.dir/main.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/inory/GraduationDesign/ev_face/main.cpp > CMakeFiles/ev_face.dir/main.cpp.i

CMakeFiles/ev_face.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ev_face.dir/main.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/inory/GraduationDesign/ev_face/main.cpp -o CMakeFiles/ev_face.dir/main.cpp.s

CMakeFiles/ev_face.dir/main.cpp.o.requires:

.PHONY : CMakeFiles/ev_face.dir/main.cpp.o.requires

CMakeFiles/ev_face.dir/main.cpp.o.provides: CMakeFiles/ev_face.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/ev_face.dir/build.make CMakeFiles/ev_face.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/ev_face.dir/main.cpp.o.provides

CMakeFiles/ev_face.dir/main.cpp.o.provides.build: CMakeFiles/ev_face.dir/main.cpp.o


# Object files for target ev_face
ev_face_OBJECTS = \
"CMakeFiles/ev_face.dir/main.cpp.o"

# External object files for target ev_face
ev_face_EXTERNAL_OBJECTS =

ev_face: CMakeFiles/ev_face.dir/main.cpp.o
ev_face: CMakeFiles/ev_face.dir/build.make
ev_face: /home/inory/SeetaFaceEngine/FaceDetection/build/libseeta_facedet_lib.so
ev_face: /home/inory/SeetaFaceEngine/FaceAlignment/build/libseeta_fa_lib.so
ev_face: /home/inory/SeetaFaceEngine/FaceIdentification/build/libviplnet.so
ev_face: /usr/local/lib/libopencv_xphoto.so.3.1.0
ev_face: /usr/local/lib/libopencv_xobjdetect.so.3.1.0
ev_face: /usr/local/lib/libopencv_tracking.so.3.1.0
ev_face: /usr/local/lib/libopencv_surface_matching.so.3.1.0
ev_face: /usr/local/lib/libopencv_structured_light.so.3.1.0
ev_face: /usr/local/lib/libopencv_stereo.so.3.1.0
ev_face: /usr/local/lib/libopencv_sfm.so.3.1.0
ev_face: /usr/local/lib/libopencv_saliency.so.3.1.0
ev_face: /usr/local/lib/libopencv_rgbd.so.3.1.0
ev_face: /usr/local/lib/libopencv_reg.so.3.1.0
ev_face: /usr/local/lib/libopencv_plot.so.3.1.0
ev_face: /usr/local/lib/libopencv_optflow.so.3.1.0
ev_face: /usr/local/lib/libopencv_line_descriptor.so.3.1.0
ev_face: /usr/local/lib/libopencv_hdf.so.3.1.0
ev_face: /usr/local/lib/libopencv_fuzzy.so.3.1.0
ev_face: /usr/local/lib/libopencv_dpm.so.3.1.0
ev_face: /usr/local/lib/libopencv_dnn.so.3.1.0
ev_face: /usr/local/lib/libopencv_datasets.so.3.1.0
ev_face: /usr/local/lib/libopencv_ccalib.so.3.1.0
ev_face: /usr/local/lib/libopencv_bioinspired.so.3.1.0
ev_face: /usr/local/lib/libopencv_bgsegm.so.3.1.0
ev_face: /usr/local/lib/libopencv_aruco.so.3.1.0
ev_face: /usr/local/lib/libopencv_videostab.so.3.1.0
ev_face: /usr/local/lib/libopencv_superres.so.3.1.0
ev_face: /usr/local/lib/libopencv_stitching.so.3.1.0
ev_face: /usr/local/lib/libopencv_photo.so.3.1.0
ev_face: /usr/lib/x86_64-linux-gnu/libglog.so
ev_face: /usr/local/lib/libopencv_text.so.3.1.0
ev_face: /usr/local/lib/libopencv_face.so.3.1.0
ev_face: /usr/local/lib/libopencv_ximgproc.so.3.1.0
ev_face: /usr/local/lib/libopencv_xfeatures2d.so.3.1.0
ev_face: /usr/local/lib/libopencv_shape.so.3.1.0
ev_face: /usr/local/lib/libopencv_video.so.3.1.0
ev_face: /usr/local/lib/libopencv_objdetect.so.3.1.0
ev_face: /usr/local/lib/libopencv_calib3d.so.3.1.0
ev_face: /usr/local/lib/libopencv_features2d.so.3.1.0
ev_face: /usr/local/lib/libopencv_ml.so.3.1.0
ev_face: /usr/local/lib/libopencv_highgui.so.3.1.0
ev_face: /usr/local/lib/libopencv_videoio.so.3.1.0
ev_face: /usr/local/lib/libopencv_imgcodecs.so.3.1.0
ev_face: /usr/local/lib/libopencv_imgproc.so.3.1.0
ev_face: /usr/local/lib/libopencv_flann.so.3.1.0
ev_face: /usr/local/lib/libopencv_core.so.3.1.0
ev_face: CMakeFiles/ev_face.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/inory/GraduationDesign/ev_face/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ev_face"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ev_face.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/ev_face.dir/build: ev_face

.PHONY : CMakeFiles/ev_face.dir/build

CMakeFiles/ev_face.dir/requires: CMakeFiles/ev_face.dir/main.cpp.o.requires

.PHONY : CMakeFiles/ev_face.dir/requires

CMakeFiles/ev_face.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/ev_face.dir/cmake_clean.cmake
.PHONY : CMakeFiles/ev_face.dir/clean

CMakeFiles/ev_face.dir/depend:
	cd /home/inory/GraduationDesign/ev_face/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/inory/GraduationDesign/ev_face /home/inory/GraduationDesign/ev_face /home/inory/GraduationDesign/ev_face/build /home/inory/GraduationDesign/ev_face/build /home/inory/GraduationDesign/ev_face/build/CMakeFiles/ev_face.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/ev_face.dir/depend

