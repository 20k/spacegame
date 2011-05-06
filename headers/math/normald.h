#ifndef INCLUDES_MATH_NORMALD_H
#define INCLUDES_MATH_NORMALD_H

namespace normald {
	double random_normal();
	inline double stdnormal_pdf(double u);
	double quad8_stdnormal_pdf(double a, double b, double Q = 1.0);
	double stdnormal_cdf(double u);
	double stdnormal_inv(double p);
	double InverseNormal(double val, double mu, double stddev);
};

#endif