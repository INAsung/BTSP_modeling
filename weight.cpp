#pragma once
#include "weight.h"


double sigmoid(double x, double alpha, double beta) {
	return (1 / (1 + exp(-beta * (x - alpha))));
}

double nonlinear(double x, double alpha, double beta) {
	return (sigmoid(x, alpha, beta) - sigmoid(0, alpha, beta)) / (sigmoid(1, alpha, beta) - sigmoid(0, alpha, beta));
}


weight::weight()
{
	this->dt = 1.0;

	this->w = 1.0;
	this->weight_max = 5.0;

	this->alpha_plus = 0.5;		// 5
	this->alpha_minus = 0.01;   //0.01
	this->beta_plus = 4;	    // 4
	this->beta_minus = 44.4;    //44.44
	this->k_plus = 1.7 / 1000;		    // 1.7
	this->k_minus = 0.204 / 1000;		// 0.204

	this->ET = 0.0;
	this->touET = 2500.0;
	this->gammaET = 0.0647;

	this->IS = 0.0;
	this->touIS = 1500.0;
	this->gammaIS = 2.8;
}


void weight::cal_ET(double Ri)
{
	ET += (1 / touET) * (-ET + gammaET * Ri) * dt;
	if (ET > 1) { ET = 1; };

	ET_trace.push_back(ET);
}

void weight::cal_IS(double P)
{
	IS += (1 / touIS) * (-IS + gammaIS * P) * dt;
	if (IS> 1) { IS = 1; };

	IS_trace.push_back(IS);
}

void weight::cal_weight()
{
	this->chem_signal_trace.push_back(ET * IS);
	double nonlinearPlus = nonlinear(ET * IS, alpha_plus, beta_plus);
	double nonlinearMinus = nonlinear(ET * IS, alpha_minus, beta_minus);
	double dw = ((weight_max - w) * k_plus * nonlinearPlus - w * k_minus * nonlinearMinus) * dt;
	dweightdt_trace.push_back(dw);
	w += dw;

	weight_trace.push_back(w);
}
