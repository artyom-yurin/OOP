set PROGRAM="%~1"

rem invalid arguments  
%PROGRAM% > "%TEMP%\output.txt"
if NOT ERRORLEVEL 1 goto err
fc.exe "%TEMP%\output.txt" correctAnswers\correctInvalidArguments.txt
if ERRORLEVEL 1 goto err
echo Test for invalid argements succeed!
                                                                                                                          
rem matrix value letter 
%PROGRAM% "tests\letters.txt" > "%TEMP%\output.txt"
if NOT ERRORLEVEL 1 goto err
fc.exe "%TEMP%\output.txt" correctAnswers\correctInvalidValue.txt
if ERRORLEVEL 1 goto err
echo Test for invalid value letter succeed!

rem matrix have 8 arguments 
%PROGRAM% "tests\fewArguments.txt" > "%TEMP%\output.txt"
if NOT ERRORLEVEL 1 goto err
fc.exe "%TEMP%\output.txt" correctAnswers\correctInvalidValue.txt
if ERRORLEVEL 1 goto err
echo Test for few argements succeed!

rem invalid determinant
%PROGRAM% "tests\invalidDeterminant.txt" > "%TEMP%\output.txt"
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\output.txt" correctAnswers\correctInvalidDeterminant.txt
if ERRORLEVEL 1 goto err
echo Test for invalid determinant succeed!

rem correct matrix
%PROGRAM% "tests\matrix.txt" > "%TEMP%\output.txt"
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\output.txt" correctAnswers\correctMatrix.txt 
if ERRORLEVEL 1 goto err
echo Test for correct matrix succeed!

echo Program testing succeeded
exit 0

:err
echo Program testing failed
exit 1