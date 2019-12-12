
project(ITK4GPUCommon)

# Find ITK.
find_package( ITK REQUIRED )
include( ${ITK_USE_FILE} )

# Find OpenCL.
find_package( OpenCL REQUIRED )
if( NOT ${OPENCL_FOUND} )
  message( FATAL "Could not find OpenCL" )
endif()

# Define ITK4GPUCommon_TEST_BUILD
set( ITK4GPUCommon_TEST_BUILD
  ON
CACHE BOOL "Build ITK4GPUCommon test project. On build. Off don't build." )

# Define directory to OpenCL Debug kernels
set(OPENCL_KERNELS_DEBUG_PATH
  ${CMAKE_CURRENT_BINARY_DIR}
CACHE INTERNAL "Path to itkOpenCLKernels.h")

set(OPENCL_KERNELS_DEBUG_DIR
  ${OPENCL_KERNELS_DEBUG_PATH}/DebugOpenCL
CACHE INTERNAL "Directory to OpenCL debug kernels")

file(MAKE_DIRECTORY ${OPENCL_KERNELS_DEBUG_DIR})

configure_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/itkOpenCLKernels.h.in
  ${OPENCL_KERNELS_DEBUG_PATH}/itkOpenCLKernels.h
  @ONLY
)

# Microsoft specific items
if( MSVC )
  # Kill the anoying MS VS warning about non-safe functions.
  # They hide real warnings.
  add_definitions(
  /D_SCL_SECURE_NO_DEPRECATE
  /D_CRT_SECURE_NO_DEPRECATE
  /D_CRT_TIME_FUNCTIONS_NO_DEPRECATE
  )
endif()

add_library(ITK4GPUCommon STATIC
  itkGPUDataManager.cxx
  itkGPUDataManager.h
  itkGPUFunctorBase.h
  itkGPUImage.h
  itkGPUImage.hxx
  itkGPUImageDataManager.h
  itkGPUImageDataManager.hxx
  itkGPUImageToImageFilter.h
  itkGPUImageToImageFilter.hxx
  itkGPUInPlaceImageFilter.h
  itkGPUInPlaceImageFilter.hxx
  itkGPUUnaryFunctorImageFilter.h
  itkGPUUnaryFunctorImageFilter.hxx
  itkOpenCL.h
  itkOpenCLBuffer.cxx
  itkOpenCLBuffer.h
  itkOpenCLCommandQueue.cxx
  itkOpenCLCommandQueue.h
  itkOpenCLContext.cxx
  itkOpenCLContext.h
  itkOpenCLDevice.cxx
  itkOpenCLDevice.h
  itkOpenCLEvent.cxx
  itkOpenCLEvent.h
  itkOpenCLEventList.cxx
  itkOpenCLEventList.h
  itkOpenCLExport.h
  itkOpenCLExtension.h
  itkOpenCLGlobal.h
  itkOpenCLImage.cxx
  itkOpenCLImage.h
  itkOpenCLImageFormat.cxx
  itkOpenCLImageFormat.h
  itkOpenCLKernel.cxx
  itkOpenCLKernel.h
  itkOpenCLKernelManager.cxx
  itkOpenCLKernelManager.h
  itkOpenCLKernelToImageBridge.h
  itkOpenCLKernelToImageBridge.hxx
  itkOpenCLLogger.cxx
  itkOpenCLLogger.h
  itkOpenCLMacro.h
  itkOpenCLMemoryObject.cxx
  itkOpenCLMemoryObject.h
  itkOpenCLOstreamSupport.h
  itkOpenCLPlatform.cxx
  itkOpenCLPlatform.h
  itkOpenCLProfilingTimeProbe.cxx
  itkOpenCLProfilingTimeProbe.h
  itkOpenCLProgram.cxx
  itkOpenCLProgram.h
  itkOpenCLSampler.cxx
  itkOpenCLSampler.h
  itkOpenCLSize.cxx
  itkOpenCLSize.h
  itkOpenCLStringUtils.cxx
  itkOpenCLStringUtils.h
  itkOpenCLUserEvent.cxx
  itkOpenCLUserEvent.h
  itkOpenCLUtil.cxx
  itkOpenCLUtil.h
  itkOpenCLVector.h
  itkOpenCLVector.hxx
  itkOpenCLVectorBase.cxx
  itkOpenCLVectorBase.h
  ${OPENCL_KERNELS_DEBUG_PATH}/itkOpenCLKernels.h
)

# Add "Static" and "_d" to output names
MODULE_TARGET_NAME(ITK4GPUCommon)

# Define include directories
include_directories(
  ${ITK_INCLUDE_DIRS}
  ${OPENCL_INCLUDE_DIRS}
  ${OPENCL_KERNELS_DEBUG_PATH}
)

# Define the link libraries
target_link_libraries(ITK4GPUCommon
  # OpenCL libraries first
  ${OPENCL_LIBRARIES}
  # ITK libraries
  ${ITK_LIBRARIES}
)

# Build ITK4GPUCommon_TEST_BUILD
if( ITK4GPUCommon_TEST_BUILD )
  enable_testing()
  add_subdirectory( test )
  include( CTest )
endif()
