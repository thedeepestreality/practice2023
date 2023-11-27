#include <iostream>
#include <cmath>

int Sqrt(double val, double& res){
    if (val < 0)
        return 1;
    res = sqrt(val);
    return 0;
}

double Sqrt(double val){   
    if (val < 0)
        throw "negative value!";
    return sqrt(val);
}

int norm(double x, double y, double& res)
{   
    if (x < 0 || y < 0)
        return 2;
    int err = Sqrt(x*x+y*y, res);
    return err;
}

int main()
{

    return 0;
}