: dll copy
copy /y ..\Debug\Helper.dll %jklim%\dll\
copy /y ..\Debug\Helper.pdb %jklim%\dll\
: lib copy
copy /y ..\Debug\Helper.lib %jklim%\lib\
: header file copy
copy /y .\Helper.h %jklim%\include\
copy /y .\Helper_define.h %jklim%\include\
copy /y .\singleton.hpp %jklim%\include\
copy /y .\INIHelper.hpp %jklim%\include\