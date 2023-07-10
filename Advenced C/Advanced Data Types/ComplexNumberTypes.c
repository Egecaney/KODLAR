#include <stdio.h>
#include <complex.h>

/*
 *  Z1 = a+bi , Z2= c+di
 *      1. Addition (Z1+Z2) = (a+c) + (b+d)i
 *      2. Multiplication (Z1*Z2) = (ac - bd) + (ad + bc)i
 *      3. Division (Z1/Z2) = ((ac + bd) + (bc - ad)i)/(c^2+d^2)
 *      4 . Conjugation (Z1*) = a-bi
 */

/*
 *  You can test whether your compiler supports complex arithmetic using preprocessor directives
 *      #ifdef __STDC_NO_COMPLEX__
 *          printf("Complex Arithmetic is not supported.\n");
 *      #else
 *          printf("Complex Arithmetic is supported.\n");
 *      #endif
 */

/*  Complex and Imaginary Types in C
 *      float _Complex          : store a complex number with real and imaginary parts as type float     
 *      double _Complex         : store a complex number with real and imaginary parts as type double 
 *      long double _Complex    : store a complex number with real and imaginary parts as type long double    
 * 
 *      float _Imaginary        : store an imaginary number as type float     
 *      double _Imaginary       : store an imaginary number as type double 
 *      long double _Imaginary  : store an imaginary number as type long double
 */

/*  Complex Functions
 
**Manipulation Functions**
  creal()     : computes the real part of the funtion.
  crealf()      for float
  creall()      for long double.

  cimag()     : computes the imaginary part of the function.
  cimagf()      for float
  cimagl()      for long double
  
  conj()      : returns the complex conjugate of its double complex argument
  conjf()       for float
  conjl()       for long double

**Exponential Functions**
  cexp()      : computes the complex base-e exponential
  cexpf()       for float
  cexpl()       for double

**Trigonometric Functions**
  csin()      : computes the complex sine
  csinf()       for float
  csinl()       for double

  ccos()      : computes the complex cosine
  ccosf()       for float
  ccosl()       for double
  
  ctan()      : computes the complex tangent
  ctanf()       for float
  ctanl()       for double
  
  casin()     : computes the complex arc sine
  casinf()      for float
  casinl()      for double

  cacos()     : computes the complex arc cosine
  cacosf()      for float
  cacosl()      for double
  
  catan()     : computes the complex arc tangent
  catanf()      for float
  catanl()      for double
  
**Power Function**
  cpow()      : computes the complex power function
  cpowf()       for float
  cpowl()       for double
  
  csqrt()     : computes the complex square root
  csqrtf()      for float
  csqrtl()      for double
 */

/* Using the Math.h library for complex operations may not always be correct. 
   So that Complex.h library should be used.*/

int main(void){

    double complex Z1 = 1.0 + 3.0*I;
    double complex Z2 = 1.0 - 4.0*I;

    printf("\nWorking with complex numbers: \n");
    printf("Starting values: Z1 = %.2f%+.2fi  and Z2 = %.2f%+.2fi\n\n", creal(Z1), cimag(Z1), creal(Z2), cimag(Z2));

    double complex Summation = Z1 + Z2;
    printf("The Summation  Z1+Z2 = %.2f%+.2fi\n", creal(Summation), cimag(Summation));

    double complex Difference = Z1 - Z2;
    printf("The Difference Z1-Z2 = %.2f%+.2fi\n", creal(Difference), cimag(Difference));

    double complex Product = Z1*Z2;
    printf("The Product    Z1-Z2 = %.2f%+.2fi\n", creal(Product), cimag(Product));

    double complex Division = Z1/Z2;
    printf("The Division   Z1/Z2 = %.2f%+.2fi\n", creal(Division), cimag(Division));

    double complex Conjugate = conj(Z1);
    printf("The Conjugate of  Z1 = %.2f%+.2fi\n", creal(Conjugate), cimag(Conjugate));

    double complex Power = cpow(Z1,Z2);
    printf("(Power) Z1 to the Z2 = %.2f%+.2fi\n", creal(Power), cimag(Power));

    return(0);

}