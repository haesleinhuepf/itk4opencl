This is a readme file for
the Insight Journal paper: http://hdl.handle.net/10380/3393

1. The directory 'CMake' contains CMake files to find OpenCL platforms.

2. The directory 'common' contains all source code described in the paper.

3. The directory 'itkgpu' contains copied classes from ITK 4.1.0.
   For our implementation we introduced quite some changes and new classes 
   described in section 'Modifications to ITK core'

4. The directory 'data' should contain the data files used for testing:
    BSplineDisplacements.txt
    image-115x157x129-3D.mha
    image-256x256-2D.mha
    image-512-1D.mha

   The following data are not provided due to size restriction:
    image-100x100x100-3D.mha
    image-256x256x256-3D.mha
    image-512x512x256-3D.mha

   Therefore, tests that are using this
   [100x100x100], [256x256x256] and [512x512x256] data were disabled in test/CMakeLists.txt file. 
   If you need this data files for your tests, please contact Denis P. Shamonin.

5. The directory 'test' contains all tests used for this paper.

Enjoy ;) Denis and Marius.

Contact information:

Denis P. Shamonin, MSc
Division of Image Processing (LKEB)
Department of Radiology
Leiden University Medical Center
PO Box 9600, 2300 RC Leiden, The Netherlands
Phone: +31 (0)71 526 2137, fax: +31 (0)71 524 8256
D.P.Shamonin_at_lumc.nl (replace _at_ with at sign)

Marius Staring, PhD
Division of Image Processing (LKEB)
Department of Radiology
Leiden University Medical Center
PO Box 9600, 2300 RC Leiden, The Netherlands
Phone: +31 (0)71 526 2137, fax: +31 (0)71 524 8256
m.staring_at_lumc.nl (replace _at_ with at sign)
