// Rational.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include "../Rational/CRational.h"

int main()
{
	/*CRational rat = CRational(1, 3);
	CRational rat2 = CRational(2, 3);
	CRational rat3 = rat + rat2;
	cout << rat3.GetNumerator() << endl;
	cout << rat3.GetDenominator() << endl;*/

	/*CRational rat = CRational(1, 3);
	CRational rat2 = CRational(2, 3);
	CRational rat3 = -rat2;
	cout << rat3.GetNumerator() << endl;
	cout << rat3.GetDenominator() << endl;*/

	/*CRational rat = CRational(1, 3);
	CRational rat2 = CRational(2, 3);
	CRational rat3 = +rat2;
	cout << rat3.GetNumerator() << endl;
	cout << rat3.GetDenominator() << endl;*/

	/*CRational rat = CRational(1, 3);
	CRational rat2 = CRational(2, 1);
	CRational rat3 = CRational();
	rat3 += rat2;
	cout << rat3.GetNumerator() << endl;
	cout << rat3.GetDenominator() << endl;*/
	CRational rat(-10, 5);
	cout << rat.GetNumerator() << endl;
	cout << rat.GetDenominator() << endl;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
