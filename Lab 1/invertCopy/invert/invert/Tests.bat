SET MyProgram="%~1"

if %MyProgram%=="" (
	echo Please specify path to program
	exit /b 1
)

echo  Test1: #1 Get the inverse matrix
%MyProgram% "In1.txt" > "RealityOut.txt" || goto err
fc "RealityOut.txt" "ExpOut1.txt" > nul || goto err
echo Test1 passed

echo  Test2: #2 Get the inverse matrix
%MyProgram% "In2.txt" > "RealityOut.txt" || goto err
fc "RealityOut.txt" "ExpOut2.txt" > nul || goto err
echo Test2 passed

echo  Test3: Extra number in line will give an error
%MyProgram% "extraNum.txt" > nul && goto err
echo Test3 passed

echo  Test4: Not enough numbers in the line will give an error
%MyProgram% "notEnoughNums.txt" > nul && goto err
echo Test4 passed

echo  Test5: Extra line in matrix will give an error
%MyProgram% "extraLine.txt" > nul && goto err
echo Test5 passed
 
echo  Test6: Matrix with determinant = 0 will give an error
%MyProgram% "nullDeterminant.txt" > nul && goto err
echo Test6 passed

echo  Test7: Without arguments will give an error
%MyProgram% "" > nul && goto err
echo Test7 passed

echo  Test8: Not exist inp file will give an error
%MyProgram% "matrix1.txt" > nul && goto err
echo Test8 passed

echo  Test9: empty matrix will give an error
%MyProgram% "emptyMatrix.txt" > nul && goto err
echo Test9 passed

REM All test passed successfully
echo All test passed successfully 
exit /B 0

REM Test failed
:err
echo Test failed
exit /B 1