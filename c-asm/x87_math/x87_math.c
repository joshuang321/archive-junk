#include <stdio.h>
#include <math.h>

extern void x87__sine();
extern void x87__cosine();
extern void x87__tangent();
extern void x87__cosecant();
extern void x87__secant();
extern void x87__cotangent();
extern void x87__arcsine();
extern void x87__arccosine();
extern void x87__arctangent();
extern void x87__arccotangent();
extern void x87__arcsecant();
extern void x87__arccosecant();
extern void x87__exponent();
extern void x87__10_exponent();
extern void x87__nat_exponent();
extern void x87__log();
extern void x87__10_log();
extern void x87__nat_log();
extern void x87__modf();
extern void x87__sqrt();
extern void x87__fabs();
extern void x87__floor();
extern void x87__ceil();
extern void x87__fmod();
extern void x87__sgn();

void x87__test_sine();
void x87__test_cosine();
void x87__test_tangent();
void x87__test_cosecant();
void x87__test_secant();
void x87__test_cotangent();
void x87__test_arcsine();
void x87__test_arccosine();
void x87__test_arctangent();
void x87__test_arccotangent();
void x87__test_arcsecant();
void x87__test_arccosecant();
void x87__test_exponent();
void x87__test_10_exponent();
void x87__test_nat_exponent();
void x87__test_log();
void x87__test_10_log();
void x87__test_nat_log();
void x87__test_modf();
void x87__test_sqrt();
void x87__test_fabs();
void x87__test_floor();
void x87__test_ceil();
void x87__test_fmod();
void x87__test_sgn();

int main(void)
{ 
	x87__test_sine();
	x87__test_cosine();
	x87__test_tangent();
	x87__test_cosecant();
	x87__test_secant();
	x87__test_cotangent();
	x87__test_arcsine();
	x87__test_arccosine();
	x87__test_arctangent();
	x87__test_arccotangent();
	x87__test_arcsecant();
	x87__test_arccosecant();
	x87__test_exponent();
	x87__test_10_exponent();
	x87__test_nat_exponent();
	x87__test_log();
	x87__test_10_log();
	x87__test_nat_log();
	x87__test_modf();
	x87__test_sqrt();
	x87__test_fabs();
	x87__test_floor();
	x87__test_ceil();
	x87__test_fmod();
	x87__test_sgn();
	return 0;
}

void x87__test_sine()
{
	double x = 1.57;
	x87__sine();
	printf("sine(1.57): %lf\n", x); 
}

void x87__test_cosine()
{
	double x = 1.57;
	x87__cosine();
	printf("cosine(1.57): %lf\n", x);
}
void x87__test_tangent()
{
	double x = 0.785;
	x87__tangent();
	printf("tangent(0.785): %lf\n", x);
}

void x87__test_cosecant()
{
	double x = 0.785;
	x87__cosecant();
	printf("cosecant(0.785): %lf\n", x);
}

void x87__test_secant()
{
	double x = 0.785;
	x87__secant();
	printf("secant(0.785): %lf\n", x);
}

void x87__test_cotangent()
{
	double x = 0.785;
	x87__cotangent();
	printf("contagent(0.785): %lf\n", x);
}

void x87__test_arcsine()
{
	double x = 0.5;
	x87__arcsine();
	printf("arcsine(0.5): %lf\n", x);
}

void x87__test_arccosine()
{
	double x = 0.5;
	x87__arccosine();
	printf("accosine(0.5): %lf\n", x);
}

void x87__test_arctangent()
{
	double x = 0.5;
	x87__arctangent();
	printf("arctangent(0.5): %lf\n", x);
}

void x87__test_arccotangent()
{
	double x = 0.5;
	x87__arccotangent();
	printf("arccotangent(0.5): %lf\n", x);
}

void x87__test_arcsecant()
{
	double x = 0.5;
	x87__arcsecant();
	printf("arcsecant(0.5): %lf\n", x);
}

void x87__test_arccosecant()
{
	double x = 0.5;
	x87__arccosecant();
	printf("arccosecant(0.5): %lf\n", x);
}

void x87__test_exponent()
{
	double x = 2.2, y = 3.3;
	x87__exponent();
	printf("x^y: %lf\n", x);
}

void x87__test_10_exponent()
{
	double x = 2.0;
	x87__10_exponent();
	printf("10^2: %lf\n", x);
}

void x87__test_nat_exponent()
{
	double x = -1.2;
	x87__nat_exponent();
	printf("e^x: %lf\n", x);
}

void x87__test_log()
{
	double x = 2.7, y = 1.0;
	x87__log();
	printf("logx y: %lf\n", x);
}

void x87__test_10_log()
{
	double x = 10.0;
	x87__10_log();
	printf("log10 x: %lf\n", x);
}

void x87__test_nat_log()
{
	double x = 2.7;
	x87__nat_log();
	printf("ln x: %lf\n", x);
}

void x87__test_modf()
{
	double x = 2.3;
	x87__modf();
	printf("modf(2.3):%lf\n", x);
}

void x87__test_sqrt()
{
	double x = 4.0;
	x87__sqrt();
	printf("sqrt(4.0): %lf\n", x);
}

void x87__test_fabs()
{
	double x = -23.3;
	x87__fabs();
	printf("fabs(-23.3): %lf\n", x);
}

void x87__test_floor()
{
	double x = 2.3;
	x87__floor();
	printf("floor(2.3): %lf\n", x);
}

void x87__test_ceil()
{
	double x = 2.3;
	x87__ceil();
	printf("ceil(2.3): %lf\n", x);
}

void x87__test_fmod()
{
	double x = 2.3, y = 2;
	x87__fmod();
	printf("rem(x/y): %lf\n", x);
}

void x87__test_sgn()
{
	double x = -2.3;
	x87__sgn();
	printf("sgn(2.3): %lf\n", x);
}

