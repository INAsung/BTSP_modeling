#pragma once
#include <iostream>
#include <vector>
#include <map>
#include "CA3.h"
#include "weight.h"
#include "Vector3f.h"

using namespace std;

class CA1 {
private:
    int gid;

    double Vb; // mV. background level of depolarization
    double c; // scaling factor

public:
    int t;
    int dt;
    int runtime;
    int tot_plateaus;
    int lap;
    int prev_plateau;

    double vramp; // mV
    double rate; // Hz
    map<CA3*, weight*> exc_conns;
    map<CA3*, weight*> inh_conns;

    vector<double> voltage_trace;
    vector<double> rate_trace;

    vector<CA1*> neighbors;

    Vector3f pos;

    CA1(int gid, vector<CA3*> preCA3s);

    vector<int> plateau_timing;
    bool plateau_on;
    bool plateau_inh;

    bool operator<(const CA1& cell) const;

    void step(); // steps derivative function for membrane potential
    void control_weight();
    void control_vramp();

    int get_gid() { return gid; }

    void make_conns(vector<CA3*> preCA3s);

    void make_plateau_timings();
    void rise_plateau();

    void add_neighbor(CA1* cell) { neighbors.push_back(cell); }
};

