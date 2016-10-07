set PROGRAM="%~1"

rem invalid arguments  
%PROGRAM% > "%TEMP%\output.txt"
if NOT ERRORLEVEL 1 goto err
fc.exe "%TEMP%\output.txt" correctAnswers\correctInvalidArguments.txt
if ERRORLEVEL 1 goto err
echo Test for invalid argements succeed!

rem empty string 
%PROGRAM% "tests\name.txt" %TEMP%\answerEmptyString "" "A" > "%TEMP%\output.txt"
if NOT ERRORLEVEL 1 goto err
fc.exe "%TEMP%\output.txt" correctAnswers\correctEmptyString.txt
if ERRORLEVEL 1 goto err
echo Test for empty string succeed!
                                                                                                                          
rem delete all "V" 
%PROGRAM% "tests\name.txt" %TEMP%\answerName.txt "V" ""
if ERRORLEVEL 1 goto err
fc.exe %TEMP%\answerName.txt correctAnswers\correctName.txt
if ERRORLEVEL 1 goto err
echo Test for delete symbols succeed!

rem replace "1231234" to "12312312345"
%PROGRAM% "tests\recursion.txt" %TEMP%\answerRecursion.txt "1231234" "12312312345"
if ERRORLEVEL 1 goto err
fc.exe %TEMP%\answerRecursion.txt correctAnswers\correctRecursion.txt 
if ERRORLEVEL 1 goto err
echo Test for replace "1231234" to "12312312345" succeed!

rem replace "name" to "Artem"
%PROGRAM% "tests\hello.txt" %TEMP%\answerHello.txt "name" "Artyom"
if ERRORLEVEL 1 goto err
fc.exe %TEMP%\answerHello.txt correctAnswers\correctHello.txt
if ERRORLEVEL 1 goto err
echo Test for replace "name" to "Artyom" succeed!

echo Program testing succeeded
exit 0

:err
echo Program testing failed
exit 1