: dll copy
copy /y ..\Debug\Helper.dll %jklim%\dll\
copy /y ..\Debug\Helper.pdb %jklim%\dll\
: lib copy
copy /y ..\Debug\Helper.lib %jklim%\lib\
: header file copy
: copy all header
copy /y .\*.h %jklim%\include\
copy /y .\*.hpp %jklim%\include\
