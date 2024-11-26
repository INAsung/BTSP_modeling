#pragma once
#include <iostream>
#include <vector>
#include <random>
#include <map>
#include <cmath>


using namespace std;

class CA3 {
private:
    int gid;
    string type;

    double center_pos; // cm
    double sigma; // cm

    double vramp; // mV
    double rate; // Hz
    double rate_max; //Hz


public:
    vector<double> rate_trace;

    CA3(int gid, double center);
    void cal_rate(double pos);
    double get_rate() { return rate; };
    int get_gid() { return gid; };

};