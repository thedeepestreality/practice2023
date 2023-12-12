#include <iostream>

bool check_long(const char* str)
{
    int idx = 0;
    int counter = 0;
    while (str[idx] != '\0')
    {
        if (str[idx++] == '(')
            ++counter;
        else
            --counter;
        if (counter < 0)
            return false;
    }
    return counter == 0;
}

bool f(char*s){int c=0;for(;*s&&c>=0;c-=2**s++-81);return!c;}

#define check f

bool unitTest()
{
    bool total = true;
    bool empty_str = (check("") == true);
    total = total && empty_str;
    bool simple_str = (check("()") == true);
    total = total && simple_str;
    bool simple_wrong = (check(")(") == false);
    total = total && simple_wrong;
    bool open_only = (check("(") == false);
    total = total && open_only;
    bool close_only = (check(")") == false);
    total = total && close_only;
    bool too_many_open = (check("(()") == false);
    total = total && too_many_open;
    bool too_many_close = (check("())") == false);
    total = total && too_many_close;
    bool nested = (check("(())") == true);
    total = total && nested;
    bool sequence = (check("()()") == true);
    total = total && sequence;
    if (total)
        std::cout << "TESTS OK\n";
    else
        std::cout << "TESTS FAILED\n";
    return total;
}

int main() {
    std::cout << "Hello, World!" << std::endl;
    unitTest();
    return 0;
}
