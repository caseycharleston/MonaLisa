# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.27

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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.27.7/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.27.7/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/caseycharleston/ximena-jr/CPPInterface

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/caseycharleston/ximena-jr/CPPInterface/build

# Include any dependencies generated for this target.
include CMakeFiles/calc.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/calc.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/calc.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/calc.dir/flags.make

CMakeFiles/calc.dir/calc.cpp.o: CMakeFiles/calc.dir/flags.make
CMakeFiles/calc.dir/calc.cpp.o: /Users/caseycharleston/ximena-jr/CPPInterface/calc.cpp
CMakeFiles/calc.dir/calc.cpp.o: CMakeFiles/calc.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/caseycharleston/ximena-jr/CPPInterface/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/calc.dir/calc.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/calc.dir/calc.cpp.o -MF CMakeFiles/calc.dir/calc.cpp.o.d -o CMakeFiles/calc.dir/calc.cpp.o -c /Users/caseycharleston/ximena-jr/CPPInterface/calc.cpp

CMakeFiles/calc.dir/calc.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/calc.dir/calc.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/caseycharleston/ximena-jr/CPPInterface/calc.cpp > CMakeFiles/calc.dir/calc.cpp.i

CMakeFiles/calc.dir/calc.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/calc.dir/calc.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/caseycharleston/ximena-jr/CPPInterface/calc.cpp -o CMakeFiles/calc.dir/calc.cpp.s

CMakeFiles/calc.dir/client.cpp.o: CMakeFiles/calc.dir/flags.make
CMakeFiles/calc.dir/client.cpp.o: /Users/caseycharleston/ximena-jr/CPPInterface/client.cpp
CMakeFiles/calc.dir/client.cpp.o: CMakeFiles/calc.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/caseycharleston/ximena-jr/CPPInterface/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/calc.dir/client.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/calc.dir/client.cpp.o -MF CMakeFiles/calc.dir/client.cpp.o.d -o CMakeFiles/calc.dir/client.cpp.o -c /Users/caseycharleston/ximena-jr/CPPInterface/client.cpp

CMakeFiles/calc.dir/client.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/calc.dir/client.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/caseycharleston/ximena-jr/CPPInterface/client.cpp > CMakeFiles/calc.dir/client.cpp.i

CMakeFiles/calc.dir/client.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/calc.dir/client.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/caseycharleston/ximena-jr/CPPInterface/client.cpp -o CMakeFiles/calc.dir/client.cpp.s

# Object files for target calc
calc_OBJECTS = \
"CMakeFiles/calc.dir/calc.cpp.o" \
"CMakeFiles/calc.dir/client.cpp.o"

# External object files for target calc
calc_EXTERNAL_OBJECTS =

calc: CMakeFiles/calc.dir/calc.cpp.o
calc: CMakeFiles/calc.dir/client.cpp.o
calc: CMakeFiles/calc.dir/build.make
calc: /usr/local/lib/libopencv_gapi.4.8.1.dylib
calc: /usr/local/lib/libopencv_stitching.4.8.1.dylib
calc: /usr/local/lib/libopencv_alphamat.4.8.1.dylib
calc: /usr/local/lib/libopencv_aruco.4.8.1.dylib
calc: /usr/local/lib/libopencv_bgsegm.4.8.1.dylib
calc: /usr/local/lib/libopencv_bioinspired.4.8.1.dylib
calc: /usr/local/lib/libopencv_ccalib.4.8.1.dylib
calc: /usr/local/lib/libopencv_dnn_objdetect.4.8.1.dylib
calc: /usr/local/lib/libopencv_dnn_superres.4.8.1.dylib
calc: /usr/local/lib/libopencv_dpm.4.8.1.dylib
calc: /usr/local/lib/libopencv_face.4.8.1.dylib
calc: /usr/local/lib/libopencv_freetype.4.8.1.dylib
calc: /usr/local/lib/libopencv_fuzzy.4.8.1.dylib
calc: /usr/local/lib/libopencv_hfs.4.8.1.dylib
calc: /usr/local/lib/libopencv_img_hash.4.8.1.dylib
calc: /usr/local/lib/libopencv_intensity_transform.4.8.1.dylib
calc: /usr/local/lib/libopencv_line_descriptor.4.8.1.dylib
calc: /usr/local/lib/libopencv_mcc.4.8.1.dylib
calc: /usr/local/lib/libopencv_quality.4.8.1.dylib
calc: /usr/local/lib/libopencv_rapid.4.8.1.dylib
calc: /usr/local/lib/libopencv_reg.4.8.1.dylib
calc: /usr/local/lib/libopencv_rgbd.4.8.1.dylib
calc: /usr/local/lib/libopencv_saliency.4.8.1.dylib
calc: /usr/local/lib/libopencv_sfm.4.8.1.dylib
calc: /usr/local/lib/libopencv_stereo.4.8.1.dylib
calc: /usr/local/lib/libopencv_structured_light.4.8.1.dylib
calc: /usr/local/lib/libopencv_superres.4.8.1.dylib
calc: /usr/local/lib/libopencv_surface_matching.4.8.1.dylib
calc: /usr/local/lib/libopencv_tracking.4.8.1.dylib
calc: /usr/local/lib/libopencv_videostab.4.8.1.dylib
calc: /usr/local/lib/libopencv_viz.4.8.1.dylib
calc: /usr/local/lib/libopencv_wechat_qrcode.4.8.1.dylib
calc: /usr/local/lib/libopencv_xfeatures2d.4.8.1.dylib
calc: /usr/local/lib/libopencv_xobjdetect.4.8.1.dylib
calc: /usr/local/lib/libopencv_xphoto.4.8.1.dylib
calc: /usr/local/lib/libopencv_shape.4.8.1.dylib
calc: /usr/local/lib/libopencv_highgui.4.8.1.dylib
calc: /usr/local/lib/libopencv_datasets.4.8.1.dylib
calc: /usr/local/lib/libopencv_plot.4.8.1.dylib
calc: /usr/local/lib/libopencv_text.4.8.1.dylib
calc: /usr/local/lib/libopencv_ml.4.8.1.dylib
calc: /usr/local/lib/libopencv_phase_unwrapping.4.8.1.dylib
calc: /usr/local/lib/libopencv_optflow.4.8.1.dylib
calc: /usr/local/lib/libopencv_ximgproc.4.8.1.dylib
calc: /usr/local/lib/libopencv_video.4.8.1.dylib
calc: /usr/local/lib/libopencv_videoio.4.8.1.dylib
calc: /usr/local/lib/libopencv_imgcodecs.4.8.1.dylib
calc: /usr/local/lib/libopencv_objdetect.4.8.1.dylib
calc: /usr/local/lib/libopencv_calib3d.4.8.1.dylib
calc: /usr/local/lib/libopencv_dnn.4.8.1.dylib
calc: /usr/local/lib/libopencv_features2d.4.8.1.dylib
calc: /usr/local/lib/libopencv_flann.4.8.1.dylib
calc: /usr/local/lib/libopencv_photo.4.8.1.dylib
calc: /usr/local/lib/libopencv_imgproc.4.8.1.dylib
calc: /usr/local/lib/libopencv_core.4.8.1.dylib
calc: CMakeFiles/calc.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/Users/caseycharleston/ximena-jr/CPPInterface/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable calc"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/calc.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/calc.dir/build: calc
.PHONY : CMakeFiles/calc.dir/build

CMakeFiles/calc.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/calc.dir/cmake_clean.cmake
.PHONY : CMakeFiles/calc.dir/clean

CMakeFiles/calc.dir/depend:
	cd /Users/caseycharleston/ximena-jr/CPPInterface/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/caseycharleston/ximena-jr/CPPInterface /Users/caseycharleston/ximena-jr/CPPInterface /Users/caseycharleston/ximena-jr/CPPInterface/build /Users/caseycharleston/ximena-jr/CPPInterface/build /Users/caseycharleston/ximena-jr/CPPInterface/build/CMakeFiles/calc.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/calc.dir/depend
