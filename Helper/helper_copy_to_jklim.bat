: dll copy
copy /y ..\Debug\Helper.dll %jklim%\dll\
copy /y ..\Debug\Helper.pdb %jklim%\dll\
: lib copy
copy /y ..\Debug\Helper.lib %jklim%\lib\
: header file copy
: base header
copy /y .\Helper.h %jklim%\include\
copy /y .\Helper_define.h %jklim%\include\
: pattern header
copy /y .\singleton.hpp %jklim%\include\
copy /y .\AutoUnlocker.hpp %jklim%\include\
copy /y .\GetArraySize.hpp %jklim%\include\
: helper header
copy /y .\INIHelper.hpp %jklim%\include\
copy /y .\DLLHelper.h %jklim%\include\
copy /y .\ThreadHelper.h %jklim%\include\
copy /y .\TimeHelper.h %jklim%\include\