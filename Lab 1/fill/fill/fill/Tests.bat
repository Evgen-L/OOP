SET MyProgram="%~1"

if %MyProgram%=="" (
	echo Please specify path to program
	exit /b 1
)

echo  Test1: Simple test with "O" and borders
%MyProgram% "in1.txt" "RealityOut.txt" || goto err
fc "RealityOut.txt" "expOut1.txt" > nul || goto err
echo Test1 passed

echo  Test2: Simple test with "O" and with a gap in the borders
%MyProgram% "in2.txt" "RealityOut.txt" || goto err
fc "RealityOut.txt" "expOut2.txt" > nul || goto err
echo Test2 passed

echo  Test3: A lot of borders with "O" and without "O" 
%MyProgram% "in3.txt" "RealityOut.txt" || goto err
fc "RealityOut.txt" "expOut3.txt" > nul || goto err
echo Test3 passed



REM All test passed successfully
echo All test passed successfully 
exit /B 0

REM Test failed
:err
echo Test failed
exit /B 1