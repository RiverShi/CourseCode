#define MYDLL __declspec(dllexport)

MYDLL double Add(double a, double b)
{
    return a + b;
}

MYDLL double Sub(double a, double b)
{
    return a - b;
}

MYDLL double Mul(double a, double b)
{
    return a * b;
}