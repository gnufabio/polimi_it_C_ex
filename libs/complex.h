#define COMPLEX_L

/*
* Algebric complex number
*/
typedef struct {
	double re;
	double im;
} t_complex;

/*
* Polar complex number
*/
typedef struct {
	double rho;
	double theta;
} t_complexp;

global t_complex c_re_u = { 1.0, 0.0 };
global t_complex c_im_u = { 0.0, 1.0 };

/* Print functions */
void printc(t_complex *);
void printcp(t_complexp *);

/* Summ */
t_complex c_sum(t_complex *, t_complex *);
t_complexp cp_sum(t_complexp *, t_complexp *); */

/* Subtraction */
t_complex c_sub(t_complex *, t_complex *);
t_complexp cp_sub(t_complexp *, t_complexp *);

/* Multiplication */
t_complex c_mul(t_complex *, t_complex *);
t_complexp cp_mul(t_complexp *, t_complexp *);

/* Division */
t_complex c_div(t_complex *, t_complex *));
t_complexp cp_div(c_complexp *, t_complexp *);

/* Invert */
t_complex c_inv(t_complex *);
t_complexp cp_inv(t_complexp *);

/* Power */
t_complex c_pow(t_complex *, int);
t_complexp cp_pow(t_complexp *, int);

/* Module of a complex number */
double c_mod(t_complex *);
/* Argument of a complex number */
double c_arg(t_complex *);

t_complex c_build(double, double);
t_complex cp_build(double, double);
