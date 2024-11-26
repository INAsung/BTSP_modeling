#pragma once
#include "CA1.h"


CA1::CA1(int gid, vector<CA3*> preCA3s)
{
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<double> uniform_dist(0.0, 10.0);

    this->t = 0;
    this->dt = 1;
    this->prev_plateau = -1;
    this->gid = gid;
    this->c = 0.0026;
    this->Vb = 2;

    this->runtime = 7200;
    this->lap = 4;
    this->tot_plateaus = 2;
    this->plateau_inh = false;
    this->plateau_on = false;

    this->rate = 0;
    this->vramp = 0;

    this->pos = Vector3f(uniform_dist(gen), uniform_dist(gen), uniform_dist(gen));

    make_conns(preCA3s);
    make_plateau_timings();
}

bool CA1::operator<(const CA1& CA1) const
{
    return gid < CA1.gid;
}


void CA1::step()
{
    t += dt;
    rise_plateau();
    control_weight();
    control_vramp();
}

void CA1::control_weight()
{
    for (auto conn = exc_conns.begin(); conn != exc_conns.end(); conn++) {
        weight* preW = conn->second;
        //bool P = ((t > runtime + 2000 && t < runtime + 2000 + 300) || (t > runtime * 4 + 4000 && t < runtime * 4 + 4000 + 300)) ? true : false;
        preW->cal_ET(conn->first->get_rate());
        preW->cal_IS(plateau_on);
        preW->cal_weight();
    }
}

void CA1::control_vramp()
{
    double now = 0;
    for (auto conn = exc_conns.begin(); conn != exc_conns.end(); conn++) {
        now += c * conn->second->w * conn->first->get_rate();
    }
    now -= Vb;
    vramp = now;
    voltage_trace.push_back(vramp);
}


void CA1::make_conns(vector<CA3*> preCA3s)
{
    for (int i = 0; i < preCA3s.size(); i++) {
        weight* w = new weight();
        exc_conns[preCA3s[i]] = w;
    }
}

void CA1::make_plateau_timings()
{
    // uniform
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<double> uniform_dist(0.0, runtime * lap);

    for (int i = 0; i < tot_plateaus; i++) {
        plateau_timing.push_back(uniform_dist(gen));
    }
}

void CA1::rise_plateau()
{
    // control now going plateau
    if (plateau_on) {
        if (t - prev_plateau < 300) {
            plateau_on = true;
            plateau_inh = true;
        }
        else if (t - prev_plateau < 600) {
            plateau_on = false;
            plateau_inh = true;
        }
        else {
            plateau_on = false;
            plateau_inh = false;
        }
    }

    // search time for plateau
    for (int i = 0; i < plateau_timing.size(); i++) {
        if (t == plateau_timing[i]) {
            //cout << plateau_timing[i] << endl;
            prev_plateau = plateau_timing[i];
            // neighbor inhibition
            int cnt = 0;
            for (CA1* cell : neighbors) {
                if (cell->plateau_inh) {
                    cnt += 1;
                }
            }
            if (cnt < 1) {
                plateau_on = true;
            }
            else {
                plateau_on = false;
            }
            break;
        }
    }
}
