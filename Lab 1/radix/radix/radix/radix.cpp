#include <iostream>
#include <optional>
#include <string>
#include <cmath>

using namespace std;

const int MIN_NUMBER_SYSTEM = 2;
const int MAX_NUMBER_SYSTEM = 36;
const string DIGITS = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

struct Args
{
    int original_ns = 0;
    int final_ns = 0;
    string number = "";
};

int stringToInt(const string& str, int radix, bool& wasError)
{
    wasError = false;
    if (radix < MIN_NUMBER_SYSTEM || radix > MAX_NUMBER_SYSTEM)
    {
        cout << "Incorrect input: radix out of range." << endl;
        wasError = true;
        return 1;
    }

    if (str.length() == 0) 
    {
        cout << "Incorrect input: empty argument." << endl;
        wasError = true;
        return 1; 
    }

    const size_t NOT_POS = string::npos;
    const string NUMBER_SIGNS = "+-";

    if (str.find_last_of(NUMBER_SIGNS) != 0 && str.find_last_of(NUMBER_SIGNS) != NOT_POS) 
    {
        cout << "extraneous sign '+' or '-'" << endl;
        wasError = true;
        return 1;
    }
    if (str.find_first_not_of(DIGITS.substr(0, radix) + NUMBER_SIGNS) != NOT_POS) 
    {
        cout << "extraneous digits for your number system" << endl;
        wasError = true;
        return 1;
    }

    if (str.find_first_of(DIGITS.substr(0, radix)) == NOT_POS) 
    {
        cout << "number not entered" << endl;
        wasError = true;
        return 1;
    }

    long long result = 0;
    
    int sign = 1;
    if (str[0] == '-') 
    {
        sign = -1;
    }
    

    int rank = str.length() - 1;

    for (char digit : str) {
        if (NUMBER_SIGNS.find(digit) != NOT_POS)
        {
            rank--;
            continue;
        }
        //cout << digit  << " * " << radix << "^" << rank << endl;
        result += DIGITS.find(digit) * pow(radix, rank);
        rank--;
        if ((sign == 1 && result > (long long)INT_MAX) || (sign == -1 && result > abs((long long)INT_MIN))) 
        {
            cout << "Number is out of range" << endl;
            wasError = true;
            return 1;
        }

    }
    result *= sign;
    //cout << "number in 10 system: " << (int)result  << endl;
    return (int)result;

}

string intToString(int n, int radix, bool& wasError) 
{
    wasError = false;
    
    if (radix < MIN_NUMBER_SYSTEM || radix > MAX_NUMBER_SYSTEM)
    {
        cout << "Incorrect input: radix out of range." << endl;
        wasError = true;
        return "";
    }

    string result = "";

    if (n < 0)
        result = "-";

    if (n == 0)
        result = '0';

    size_t insertPos = result.length();

    while (n)
    {
        int curDigit = abs(n) % radix;
        result.insert(insertPos, 1, DIGITS[curDigit]);
        n /= radix;
    }
    //cout << "number in curr system: " << result << endl;
    return result;

}

optional<Args> parseArgs(int argc, char* argv[]) 
{
    if (argc != 4) 
    {
        cout << "Incorrect input. Please enter correct input: <input file> <original number system> <final number system> <number>" << endl;
        return nullopt;
    }

    Args args;
    bool err;
    args.original_ns = stringToInt(argv[1], 10, err);
    if (err)
    {
        return nullopt;
    }
    args.final_ns = stringToInt(argv[2], 10, err);
    if (err)
    {
        return nullopt;
    }
    args.number = argv[3];
    return args;
}

string convert(const int from, const int to, const string& value)
{
    bool error ;
    int number = stringToInt(value, from, error);
    if (error)
        return "";
    string result = intToString(number, to, error);
    if (error)
        return "";
    return result;
}

int main(int argc, char *argv[])
{
    auto args = parseArgs(argc, argv);
    if (!args) 
    {
        cout << "Incorrect input agrumnets.\n";
        return 1;
    }
    
    bool error = false;
    int original_ns = args -> original_ns;
    int final_ns = args->final_ns;
    string number = args->number;
    string result = convert(original_ns, final_ns, number);
    if (result == "") 
    {
        return 1;
    }
    cout << result << endl;
    return 0;

}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"
