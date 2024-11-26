#pragma once
#include "CA3.h"

CA3::CA3(int gid, double center)
{
    this->gid = gid;
    string type;

    this->center_pos = center; // set place field

    this->vramp = 0.0;
    this->rate = 0.0; // initial rate = 0 Hz
    this->rate_max = 40.0;
    this->sigma = 15.0;
}

void CA3::cal_rate(double pos)
{
    rate = rate_max * exp((-1.0 / 2.0) * pow((center_pos - pos) / sigma, 2));
    rate_trace.push_back(rate);
}
