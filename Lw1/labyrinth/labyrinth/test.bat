set PROGRAM="%~1"

rem invalid arguments  
%PROGRAM% > "%TEMP%\output.txt"
if NOT ERRORLEVEL 1 goto err
fc.exe "%TEMP%\output.txt" correctAnswers\correctInvalidArguments.txt
if ERRORLEVEL 1 goto err
echo Test for invalid argements succeed!

rem empty file 
%PROGRAM% "tests\emptyFile.txt" %TEMP%\answer > "%TEMP%\output.txt"
if NOT ERRORLEVEL 1 goto err
fc.exe "%TEMP%\output.txt" correctAnswers\correctInvalidData.txt
if ERRORLEVEL 1 goto err
echo Test for empty file succeed!

rem width more 100
%PROGRAM% "tests\invalidWidth.txt" %TEMP%\answer > "%TEMP%\output.txt"
if NOT ERRORLEVEL 1 goto err
fc.exe "%TEMP%\output.txt" correctAnswers\correctInvalidData.txt
if ERRORLEVEL 1 goto err
echo Test for invlid labyrinth's width succeed!

rem height more 100
%PROGRAM% "tests\invalidHeight.txt" %TEMP%\answer > "%TEMP%\output.txt"
if NOT ERRORLEVEL 1 goto err
fc.exe "%TEMP%\output.txt" correctAnswers\correctInvalidData.txt
if ERRORLEVEL 1 goto err
echo Test for invlid labyrinth's height succeed!
                                                                                 
rem labyrinth have more points 
%PROGRAM% "tests\morePoint.txt" %TEMP%\answer > "%TEMP%\output.txt"
if NOT ERRORLEVEL 1 goto err
fc.exe "%TEMP%\output.txt" correctAnswers\correctInvalidData.txt
if ERRORLEVEL 1 goto err
echo Test for more points succeed!

rem labyrinth have less points
%PROGRAM% "tests\lessPoint.txt" %TEMP%\answer > "%TEMP%\output.txt"
if NOT ERRORLEVEL 1 goto err
fc.exe "%TEMP%\output.txt" correctAnswers\correctInvalidData.txt
if ERRORLEVEL 1 goto err
echo Test for less point succeed!

rem labyrinth without exit
%PROGRAM% "tests\noAccess.txt" %TEMP%\answer > "%TEMP%\output.txt"
if NOT ERRORLEVEL 1 goto err
fc.exe "%TEMP%\output.txt" correctAnswers\correctNoAccess.txt
if ERRORLEVEL 1 goto err
echo Test for labyrinth without exit succeed!

rem correct labyrinth
%PROGRAM% "tests\labyrinth.txt" %TEMP%\answerLabyrinth.txt > "%TEMP%\output.txt"
if ERRORLEVEL 1 goto err
fc.exe %TEMP%\answerLabyrinth.txt correctAnswers\correctLabyrinth.txt
if ERRORLEVEL 1 goto err
echo Test for correct labyrinth succeed!

echo Program testing succeeded
exit 0

:err
echo Program testing failed
exit 1