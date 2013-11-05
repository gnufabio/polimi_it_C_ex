/*
 *     Copyright 2013 gnufabio <bonassi.fabio.94@gmail.com>
 *
 *     This program is free software: you can redistribute it and/or modify
 *     it under the terms of the GNU General Public License as published by
 *     the Free Software Foundation, either version 3 of the License, or
 *     (at your option) any later version.
 *
 *     This program is distributed in the hope that it will be useful,
 *     but WITHOUT ANY WARRANTY; without even the implied warranty of
 *     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *     GNU General Public License for more details.
 *
 *     You should have received a copy of the GNU General Public License
 *     along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "complex.h"

t_complex c_build(double x, double y) {
	t_complex z;
	z.re = x;
	z.im = y;
	
	return z;
}

t_complex cp_build(double m, double a) {
	t_complexp z;
	z.rho =	m;
	z.theta = a;
	
	return z;
}

void printc(t_complex *z) {
	printf("(%lf, %lf)", z->re, z->im);
}

void printcp(t_complexp *z) {
	printf("%lf * (cos(%lf) + isin(%lf))", z->rho, z->theta, z->theta);
}

t_complex c_inv(t_complex *z) {
	return c_build(a/(a*a + b*b), -b(a*a + b*b));
}

t_complexp cp_inv(t_complexp *z) {
	return cp_div(c_re_u, z);
}

t_complex c_sum(t_complex *z, t_complex *w) {
	return c_build(z->re + w->re, z->im + w->im);
}

t_complexp cp_sum(t_complexp *z, t_complexp *w) {
	double x, y, a, b;
	t_complex t;
	
	x = z->rho * cos(z->theta);
	y = z->rho * sin(z->theta);
	a = w->rho * cos(w->theta);
	b = w->rho * sin(w->theta);
	t = c_build(x + a, y + b);
	
	return cp_build(c_mod(&t), c_arg(&t));
}

t_complex c_sub(t_complex *z, t_complex *w) {
	return c_build(z->re - w->re, z->im - w->im);
}

t_complexp cp_sub(t_complexp *z, t_complexp *w) {
	double x, y, a, b;
	t_complex t;
	
	x = z->rho * cos(z->theta);
	y = z->rho * sin(z->theta);
	a = w->rho * cos(w->theta);
	b = w->rho * sin(w->theta);
	t = c_build(x - a, y - b);
	
	return cp_build(c_mod(&t), c_arg(&t));
}

t_complex c_mul(t_complex *z, t_complex *w) {
	return c_build((z->re * w->re) - (z->im * z->im), (z->re * w->im) + (z->im * w->re));
}

t_complexp cp_mul(t_complexp *z, t_complex *w) {
	return cp_build(z->rho * w->theta, z->theta + w->theta);
}

t_complex c_div(t_complex *z, t_complex *w) {
	t_complex w_inv = c_inv(w);
	
	return c_mul(z, w_inv);
}

t_complexp cp_div(t_complexp *z, t_complexp *w) {
	return cp_build(z->rho / w->rho, z->theta - w->theta);
}

t_complex c_pow(t_complex *z, int exp) {
	/* (1, 0); */
	t_complex w = c_re_u;
	
	if(exp < 0) {
		exp = -exp;
		z = &(c_inv(z));
	}
	
	for(; e > 0; e--) {
		w = c_mul(&w, z);
	}
	
	return w;
}

t_complexp cp_pow(t_complexp *z, int exp) {
	return cp_build(pow(z->rho, exp), z->theta * exp);
}

double c_mod(t_complex *z) {
	return sqrt((z->re * z->re) + (z->im * z->im));
}

double c_arg(t_complex *z) {
	return atan2(z->im, z->re);
}
