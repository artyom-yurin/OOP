set PROGRAM="%~1"

rem invalid arguments  
%PROGRAM% > "%TEMP%\output.txt"
if NOT ERRORLEVEL 1 goto err
fc.exe "%TEMP%\output.txt" correctAnswers\correctInvalidArguments.txt
if ERRORLEVEL 1 goto err
echo Test for invalid argements succeed!

rem unknown mode
%PROGRAM% add "tests\input.txt" %TEMP%\answer.txt 123 > "%TEMP%\output.txt"
if NOT ERRORLEVEL 1 goto err
fc.exe "%TEMP%\output.txt" correctAnswers\correctUnknownMode.txt
if ERRORLEVEL 1 goto err
echo Test for unknown mode succeed!
                                                                                                                          
rem invalid key 
%PROGRAM% crypt "tests\input.txt" %TEMP%\answer.txt 256 > "%TEMP%\output.txt"
if NOT ERRORLEVEL 1 goto err
fc.exe "%TEMP%\output.txt" correctAnswers\correctInvalidKey.txt
if ERRORLEVEL 1 goto err
echo Test for invalid key succeed!

rem invalid key is letter
%PROGRAM% crypt "tests\input.txt" %TEMP%\answer.txt "Hello" > "%TEMP%\output.txt"
if NOT ERRORLEVEL 1 goto err
fc.exe "%TEMP%\output.txt" correctAnswers\correctInvalidKeyLetter.txt
if ERRORLEVEL 1 goto err
echo Test for invalid key letter succeed!

rem correct file
%PROGRAM% crypt "tests\input.txt" %TEMP%\answer.txt 123
if ERRORLEVEL 1 goto err
%PROGRAM% decrypt %TEMP%\answer.txt %TEMP%\output.txt 123
if ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt correctAnswers\correctInput.txt 
if ERRORLEVEL 1 goto err
echo Test for correct file succeed!

echo Program testing succeeded
exit 0

:err
echo Program testing failed
exit 1