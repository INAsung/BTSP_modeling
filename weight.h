#pragma once
#include <iostream>
#include <vector>

class weight {

public:
    double dt;

    double w;
    double weight_max;

    double alpha_plus;
    double alpha_minus;
    double beta_plus;
    double beta_minus;
    double k_plus;
    double k_minus;

    double ET;
    double IS;
    double touET; // ms
    double gammaET;
    double touIS; // ms
    double gammaIS;

    std::vector<double> weight_trace;
    std::vector<double> dweightdt_trace;
    std::vector<double> ET_trace;
    std::vector<double> IS_trace;
    std::vector<double> chem_signal_trace;

    weight();
    void cal_ET(double Ri);
    void cal_IS(double P);
    void cal_weight();
};