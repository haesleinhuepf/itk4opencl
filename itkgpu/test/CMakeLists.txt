project( ITK4GPUCommonTest )

# Find ITK.
find_package( ITK REQUIRED )
include( ${ITK_USE_FILE} )

# Find OpenCL.
find_package( OpenCL REQUIRED )
if( NOT ${OPENCL_FOUND} )
  message( FATAL_ERROR "Could not find OpenCL" )
else()
  include( ${CMAKE_MODULE_PATH}/elastixOpenCL.cmake )
endif()

# Enable ordered includes
set(CMAKE_INCLUDE_DIRECTORIES_BEFORE ON)

# macro that simplifies the addition of tests
# Usage:
# ADD_GPU_TEST( <_name_of_test> )
# We assume here that the _name of the source which includes the main is:
# "itk"_name_of_test".cxx".
macro( ADD_GPU_TEST _name _kernels )
  #message(STATUS "ADD_GPU_TEST macro variables")
  #message(STATUS "VAR _name: ${_name}")
  #message(STATUS "VAR _kernels: ${_kernels}")

  # Microsoft specific items
  if( MSVC )
    # Kill the anoying MS VS warning about non-safe functions.
    # They hide real warnings.
    add_definitions(
    /D_SCL_SECURE_NO_DEPRECATE
    /D_CRT_SECURE_NO_DEPRECATE
    /D_CRT_TIME_FUNCTIONS_NO_DEPRECATE
    )

    # Increases address capacity
    if ( WIN32 )
      set( CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /bigobj" )
      set( CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /bigobj" )
      set( CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} /bigobj" )
    endif()
  endif()

  set( GPUTEST_EXECUTABLE_NAME itk${_name} )
  set( OPEN_CL_KERNELS )
  set( OPEN_CL_KERNELS_SRC )

  # Count number of kernels provided
  set( kernels ${_kernels} )
  list( LENGTH kernels num_kernels )

  # single kernel
  if(${num_kernels} EQUAL 1)
    # Define OpenCL kernels
    file(GLOB open_cl_kernel_path ${_kernels})
    list(APPEND OPEN_CL_KERNELS ${open_cl_kernel_path})

    source_group( "Kernels" FILES ${OPEN_CL_KERNELS} )
    write_opencl_kernels( "${OPEN_CL_KERNELS}" OPEN_CL_KERNELS_SRC "OpenCLTest generated kernels" OFF ${_name})
  # multiple kernels kernel
  elseif(${num_kernels} GREATER 1)
    # Define OpenCL kernels
    foreach(elem ${_kernels})
      file(GLOB open_cl_kernel_path ${elem})
      list(APPEND OPEN_CL_KERNELS ${open_cl_kernel_path})
    endforeach()

    source_group( "Kernels" FILES ${OPEN_CL_KERNELS} )
    write_opencl_kernels( "${OPEN_CL_KERNELS}" OPEN_CL_KERNELS_SRC "OpenCLTest generated kernels" ON ${_name})
  endif()

  # Define some helper variables.
  set( GPUTEST_SOURCE_NAME itk${_name}.cxx
    itkTestHelper.h
    itkTestOutputWindow.cxx
    itkTestOutputWindow.h )

  if(${num_kernels} GREATER 0)
    list(APPEND GPUTEST_SOURCE_NAME ${OPEN_CL_KERNELS} itk${_name}.h)
  endif()

  set( GPUTEST_TEST_NAME ${_name} )

  # Create the test executable.
  if(${num_kernels} GREATER 0)
    add_executable( ${GPUTEST_EXECUTABLE_NAME} ${GPUTEST_SOURCE_NAME} ${OPEN_CL_KERNELS_SRC} )
  else()
    add_executable( ${GPUTEST_EXECUTABLE_NAME} ${GPUTEST_SOURCE_NAME} )
  endif()

  include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}

    ${ITK4GPUCommon_SOURCE_DIR}
    ${ITK4OpenCL_INCLUDE_DIRS}
    ${ITK4OpenCL_KERNELS_DIR}

    # 3rd party libraries
    ${OPENCL_INCLUDE_DIRS}
  )

  include_directories( AFTER
    ${ITK_INCLUDE_DIRS}
  )

  # Link against other libraries.
  target_link_libraries( ${GPUTEST_EXECUTABLE_NAME}
    # OpenCL libraries first
    ${OPENCL_LIBRARIES}

    # Other libraries
    ITK4GPUCommon
    ITK4OpenCL
    ${ITK_LIBRARIES}
  )

  # Group in IDE's like Visual Studio
  set_property( TARGET ${GPUTEST_EXECUTABLE_NAME} PROPERTY FOLDER "tests OpenCL core" )
endmacro()

# itkOpenCLBufferTest
ADD_GPU_TEST( OpenCLBufferTest "kernels/OpenCLBufferTest.cl" )
add_test( itkOpenCLBufferTest ${EXECUTABLE_OUTPUT_PATH}/itkOpenCLBufferTest )

# itkOpenCLContextTest
ADD_GPU_TEST( OpenCLContextTest "" )
add_test( itkOpenCLContextTest ${EXECUTABLE_OUTPUT_PATH}/itkOpenCLContextTest )

# itkOpenCLDeviceTest
ADD_GPU_TEST( OpenCLDeviceTest "" )
add_test( itkOpenCLDeviceTest ${EXECUTABLE_OUTPUT_PATH}/itkOpenCLDeviceTest )

ADD_GPU_TEST( OpenCLEventTest "kernels/OpenCLEventTest.cl" )
add_test( itkOpenCLEventTest ${EXECUTABLE_OUTPUT_PATH}/itkOpenCLEventTest )

# itkOpenCLImageTest
ADD_GPU_TEST( OpenCLImageTest "kernels/OpenCLImageTest.cl" )
add_test( itkOpenCLImageTest ${EXECUTABLE_OUTPUT_PATH}/itkOpenCLImageTest )

# itkOpenCLKernelManagerTest
ADD_GPU_TEST( OpenCLKernelManagerTest "" )
add_test( itkOpenCLKernelManagerTest ${EXECUTABLE_OUTPUT_PATH}/itkOpenCLKernelManagerTest )

# itkOpenCLImageTest
ADD_GPU_TEST( OpenCLKernelTest "" )
add_test( itkOpenCLKernelTest ${EXECUTABLE_OUTPUT_PATH}/itkOpenCLKernelTest )

# itkOpenCLKernelToImageBridgeTest
ADD_GPU_TEST( OpenCLKernelToImageBridgeTest "kernels/OpenCLKernelToImageBridgeTest.cl" )
add_test( itkOpenCLKernelToImageBridgeTest ${EXECUTABLE_OUTPUT_PATH}/itkOpenCLKernelToImageBridgeTest )

# itkOpenCLPlatformTest
ADD_GPU_TEST( OpenCLPlatformTest "" )
add_test( itkOpenCLPlatformTest ${EXECUTABLE_OUTPUT_PATH}/itkOpenCLPlatformTest )

# itkOpenCLProfilingTimeProbeTest
ADD_GPU_TEST( OpenCLProfilingTimeProbeTest "" )
add_test( itkOpenCLProfilingTimeProbeTest ${EXECUTABLE_OUTPUT_PATH}/itkOpenCLProfilingTimeProbeTest )

# itkOpenCLSamplerTest
ADD_GPU_TEST( OpenCLSamplerTest "" )
add_test( itkOpenCLSamplerTest ${EXECUTABLE_OUTPUT_PATH}/itkOpenCLSamplerTest )

# itkOpenCLSimpleTest
ADD_GPU_TEST( OpenCLSimpleTest "kernels/OpenCLSimpleTest1.cl;kernels/OpenCLSimpleTest2.cl" )
add_test( itkOpenCLSimpleTest ${EXECUTABLE_OUTPUT_PATH}/itkOpenCLSimpleTest )

# itkOpenCLSizeTest
ADD_GPU_TEST( OpenCLSizeTest "" )
add_test( itkOpenCLSizeTest ${EXECUTABLE_OUTPUT_PATH}/itkOpenCLSizeTest )

# itkOpenCLStringUtilsTest
ADD_GPU_TEST( OpenCLStringUtilsTest "" )
add_test( itkOpenCLStringUtilsTest ${EXECUTABLE_OUTPUT_PATH}/itkOpenCLStringUtilsTest )

# itkOpenCLVectorTest
ADD_GPU_TEST( OpenCLVectorTest "kernels/OpenCLVectorTest.cl" )
add_test( itkOpenCLVectorTest ${EXECUTABLE_OUTPUT_PATH}/itkOpenCLVectorTest )

