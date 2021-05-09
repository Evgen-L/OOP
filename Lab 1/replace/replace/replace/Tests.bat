SET MyProgram="%~1"

if %MyProgram%=="" (
	echo Please specify path to program
	exit /b 1
)

echo 1) hello is not on line edges
%MyProgram% inpT1.txt "%TEMP%\output.txt" "hello" "bye" > nul || goto err
fc outT1.txt "%TEMP%\output.txt" > nul || goto err
echo Test1 passed

echo 2) hello is on the edges of the line
%MyProgram% inpT2.txt "%TEMP%\output.txt" "hello" "bye" > nul || goto err
fc outT2.txt "%TEMP%\output.txt" > nul || goto err
echo Test2 passed

echo 3) There are several lines in the file
%MyProgram% inpT3.txt "%TEMP%\output.txt" "hello" "bye" > nul || goto err
fc outT3.txt "%TEMP%\output.txt" > nul || goto err
echo Test3 passed

echo 4) "o" is replaced by "oo" without looping
%MyProgram% inpT4.txt "%TEMP%\output.txt" "o" "oo" > nul || goto err
fc outT4.txt "%TEMP%\output.txt" > nul || goto err
echo Test4 passed

echo 5) "oo" is replaced by "o" without looping
%MyProgram% inpT5.txt "%TEMP%\output.txt" "oo" "o" > nul || goto err
fc outT5.txt "%TEMP%\output.txt" > nul || goto err
echo Test5 passed

echo 6) empty input and empty output
%MyProgram% emptyInpT6.txt "%TEMP%\output.txt" "oo" "o" > nul || goto err
fc emptyOutT6.txt "%TEMP%\output.txt" > nul || goto err
echo Test6 passed

echo 7) empty argument searchString
%MyProgram% inpT7.txt "%TEMP%\output.txt" "" "REPUBLIC" > nul || goto err
fc outT7.txt "%TEMP%\output.txt" > nul || goto err
echo Test7 passed

echo 8) empty input and output arguments
%MyProgram% "" "" "Jc" "Bl" > nul && goto err
echo Test8 passed

echo 9) not enough arguments
%MyProgram% inpT8.txt "Jc" "Bl" > nul && goto err
echo Test9 passed

echo 10) 1231234 replac'e with x
%MyProgram% inpT9.txt "%TEMP%\output.txt" "1231234" "x" > nul || goto err
fc outT9.txt "%TEMP%\output.txt" > nul || goto err
echo Test10 passed

REM All test passed successfully
echo All test passed successfully 
exit /B 0

REM —юда попадаем в случае ошибки
:err
echo Test failed
exit /B 1