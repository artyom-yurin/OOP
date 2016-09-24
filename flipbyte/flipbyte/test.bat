set PROGRAM="%~1"

rem invalid arguments  
%PROGRAM% > "%TEMP%\output.txt"
if NOT ERRORLEVEL 1 goto err
fc.exe "%TEMP%\output.txt" correctAnswers\correctInvalidArguments.txt
if ERRORLEVEL 1 goto err
echo Test for invalid argements succeed!
                                                                                                                          
rem invalid value 256 
%PROGRAM% "256" > "%TEMP%\output.txt"
if NOT ERRORLEVEL 1 goto err
fc.exe "%TEMP%\output.txt" correctAnswers\correctInvalidValue.txt
if ERRORLEVEL 1 goto err
echo Test for invalid value 256 succeed!

rem invalid value -1
%PROGRAM% "-1" > "%TEMP%\output.txt"
if NOT ERRORLEVEL 1 goto err
fc.exe "%TEMP%\output.txt" correctAnswers\correctInvalidValue.txt
if ERRORLEVEL 1 goto err
echo Test for invalid value -1 succeed!

rem string value
%PROGRAM% "hello" > "%TEMP%\output.txt"
if NOT ERRORLEVEL 1 goto err
fc.exe "%TEMP%\output.txt" correctAnswers\correctInvalidValue.txt
if ERRORLEVEL 1 goto err
echo Test for string value succeed!

rem flip byte 6
%PROGRAM% "6" > "%TEMP%\output.txt"
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\output.txt" correctAnswers\correctValue6.txt 
if ERRORLEVEL 1 goto err
echo Test for flip byte 6 succeed!

rem flip byte 0
%PROGRAM% "0" > "%TEMP%\output.txt"
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\output.txt" correctAnswers\correctValue0.txt 
if ERRORLEVEL 1 goto err
echo Test for flip byte 0 succeed!

rem flip byte 255
%PROGRAM% "255" > "%TEMP%\output.txt"
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\output.txt" correctAnswers\correctValue255.txt 
if ERRORLEVEL 1 goto err
echo Test for flip byte 255 succeed!

echo Program testing succeeded
exit 0

:err
echo Program testing failed
exit 1