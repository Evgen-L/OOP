SET MyProgram="%~1"

if %MyProgram%=="" (
	echo Please specify path to program
	exit /b 1
)

echo  Test1: 122 in 3 NS equals 23 in 7 NS
%MyProgram% "3" "7" "122" > "RealityOut.txt" || goto err
echo 23> "ExpectedOut.txt"
fc "RealityOut.txt" "ExpectedOut.txt" > nul || goto err
echo Test1 passed

echo  Test2: AD12 in 17 NS equals 52906 in 10 NS
%MyProgram% "17" "10" "AD12" > "RealityOut.txt" || goto err
echo 52906> "ExpectedOut.txt"
fc "RealityOut.txt" "ExpectedOut.txt" > nul || goto err
echo Test2 passed

echo  Test3: 52906 in 10 NS equals AD12 in 17 NS
%MyProgram% "10" "17" "52906" > "RealityOut.txt" || goto err
echo AD12> "ExpectedOut.txt"
fc "RealityOut.txt" "ExpectedOut.txt" > nul || goto err
echo Test3 passed

echo  Test4: The maximum number is processed correctly
%MyProgram% "10" "17" "2147483647" > "RealityOut.txt" || goto err
echo 53G7F548> "ExpectedOut.txt"
fc "RealityOut.txt" "ExpectedOut.txt" > nul || goto err
echo Test4 passed

 echo Test 5 : Extraneous numbers or signs fo'r this number system cause an error
 %MyProgram% "10" "17" "AB10" > nul && goto err
 echo Test 5 passed

echo Test 6 : An error occurred while trying to enter a blank number
%MyProgram% "10" "17" "" > nul && goto err
echo Test 6 passed

echo Test 7 : Error when trying to enter an empty NS
%MyProgram% "10" "" "17" > nul && goto err
echo Test 7 passed

echo Test 8 : Error when trying to enter a NS that is out of scope
%MyProgram% "10" "-17" "2" > nul && goto err
echo Test 8 passed

echo Test 9 : Error trying to enter too large number
%MyProgram% "10" "17" "21474836476" > nul && goto err
echo Test 9 passed

echo Test 10 : An error occurred while trying to enter an extra parameter
%MyProgram% "10" "6" "17" "gigi za shagi" > nul && goto err
echo Test 10 passed


REM All test passed successfully
echo All test passed successfully 
exit /B 0

REM —юда попадаем в случае ошибки
:err
echo Test failed
exit /B 1