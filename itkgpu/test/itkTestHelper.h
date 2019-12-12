/*=========================================================================
 *
 *  Copyright UMC Utrecht and contributors
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *        http://www.apache.org/licenses/LICENSE-2.0.txt
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *=========================================================================*/
//
// \author Denis P. Shamonin and Marius Staring. Division of Image Processing,
// Department of Radiology, Leiden, The Netherlands
//
// \note This work was funded by the Netherlands Organisation for
// Scientific Research (NWO NRG-2010.02 and NWO 639.021.124).
//
#ifndef __itkTestHelper_h
#define __itkTestHelper_h

#include <string>
#include <vector>
#include <iomanip>
#include <time.h>

#include "itkTestOutputWindow.h"
#include "itkOpenCLContext.h"

namespace itk
{

#define ITK_OPENCL_COMPARE( actual, expected )                                    \
  if( !itk::Compare( actual, expected, #actual, #expected, __FILE__, __LINE__ ) ) \
    itkGenericExceptionMacro( << "Compared values are not the same" )             \

template< typename T >
inline bool
Compare( T const & t1, T const & t2, const char * actual, const char * expected,
  const char * file, int line )
{
  return ( t1 == t2 ) ? true : false;
}


//------------------------------------------------------------------------------
bool
CreateContext()
{
  // Create and check OpenCL context
  OpenCLContext::Pointer context = OpenCLContext::GetInstance();

#if defined( OPENCL_USE_INTEL_CPU ) || defined( OPENCL_USE_AMD_CPU )
  context->Create( OpenCLContext::DevelopmentSingleMaximumFlopsDevice );
#else
  context->Create( OpenCLContext::SingleMaximumFlopsDevice );
#endif

  if( !context->IsCreated() )
  {
    std::cerr << "OpenCL-enabled device is not present." << std::endl;
    return false;
  }

  return true;
}


//------------------------------------------------------------------------------
void
ReleaseContext()
{
  itk::OpenCLContext::Pointer context = itk::OpenCLContext::GetInstance();
  if( context->IsCreated() )
  {
    context->Release();
  }
}


//------------------------------------------------------------------------------
void
SetupForDebugging()
{
  TestOutputWindow::Pointer tow = TestOutputWindow::New();
  OutputWindow::SetInstance( tow );

#if ( defined( _WIN32 ) && defined( _DEBUG ) ) || !defined( NDEBUG )
  Object::SetGlobalWarningDisplay( true );
  std::cout << "INFO: test called Object::SetGlobalWarningDisplay(true)\n";
#endif
}


//------------------------------------------------------------------------------
void
ITKObjectEnableWarnings( Object * object )
{
#if ( defined( _WIN32 ) && defined( _DEBUG ) ) || !defined( NDEBUG )
  object->SetDebug( true );
  std::cout << "INFO: " << object->GetNameOfClass() << " called SetDebug(true);\n";
#endif
}


}

#endif // end #ifndef __itkTestHelper_h
