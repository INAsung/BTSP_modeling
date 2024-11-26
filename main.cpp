#pragma once
#include <iostream>
#include <vector>
#include "functions.h"
#include "CA1.h"

using namespace std;

// configurations

int runtime = 7200; // ms
int total_lap = 7;
double t; //
double dt = 1.0; // ms
double track_length = 185.0; // cm

vector<double> timepoints;
vector<double> CA3_centers;
vector<vector<double>> CA3_rate_trace;
vector<vector<double>> weight_trace;
vector<vector<double>> IS_trace;
vector<vector<double>> ET_trace;
vector<vector<double>> chem_signal_trace;
vector<vector<double>> dwdt_trace;
vector<vector<double>> CA1_voltage_trace;


int runsteps = runtime / dt;


int num_CA3 = 200;
int num_CA1 = 30;
int neibor_size = 0;

double animal_pos = 0;// cm

vector<CA3*> CA3_list;
vector<CA1*> CA1_list;


int main() {
    //make CA3_centers

    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<double> uniform_dist(0.0, track_length);

    for (int i = 0; i < total_lap * runsteps + 1; i++) {
        timepoints.push_back(i * dt);
    }

    for (int i = 0; i < num_CA3; i++) {
        CA3_centers.push_back(uniform_dist(gen));
    }

    sort(CA3_centers.begin(), CA3_centers.end());


    // make cells
    for (int i = 0; i < num_CA3; i++) {
        CA3_list.push_back(new CA3(i, CA3_centers[i]));
    }

    for (int i = 0; i < num_CA1; i++) {
        CA1_list.push_back(new CA1(i, CA3_list));
    }

    // make CA1 connections
    for (int i = 0; i < num_CA1; i++) {
        vector<double> pos_list;
        vector<int> indices(CA1_list.size());
        for (int j = 0; j < CA1_list.size(); ++j) {
            indices[j] = j;
        }

        for (int j = 0; j < num_CA1; j++) {
            if (j == i) {
                pos_list.push_back(1000000);
            }
            else {
                pos_list.push_back(CA1_list[i]->pos.dist(CA1_list[j]->pos));
            }
        }

        sort(indices.begin(), indices.end(), [&pos_list](int a, int b) {
            return pos_list[a] < pos_list[b];
            });

        vector<int> neibors(indices.begin(), indices.begin() + neibor_size);

        for (int index : neibors) {
            CA1_list[i]->add_neighbor(CA1_list[index]);
        }
    }

    cout << "setup ended" << endl;
    //for (int i = 0; i < CA1_list[0]->plateau_timing.size(); i++) {
    //    cout << CA1_list[0]->plateau_timing[i] << endl;
    //}

    // run
    for (int lap = 0; lap < total_lap; lap++)
    {
        for (int i = 0;i < runsteps;i++) {

            if (i%1000 == 0) { cout << "lap: " << lap << ", time: " << i << " ms" << endl; }
            animal_pos += track_length / runsteps;

            // run CA3
            for (int j = 0; j < num_CA3; j++) {
                CA3_list[j]->cal_rate(animal_pos);
            }


            // run CA1
            for (int j = 0; j < num_CA1; j++) {
                CA1_list[j]->step();
            }

        }
        animal_pos = 0.0;
        // end of one lap
    }
    // end of learing
    cout << "run ended" << endl;

    //for (int i = 0; i < num_CA3; i++) {
    //    CA3_rate_trace.push_back(CA3_list[i]->rate_trace);
    //}

    for (int i = 0; i < num_CA3; i++) {
        weight_trace.push_back(CA1_list[0]->exc_conns[CA3_list[i]]->weight_trace);
        IS_trace.push_back(CA1_list[0]->exc_conns[CA3_list[i]]->IS_trace);
        ET_trace.push_back(CA1_list[0]->exc_conns[CA3_list[i]]->ET_trace);
        chem_signal_trace.push_back(CA1_list[0]->exc_conns[CA3_list[i]]->chem_signal_trace);
        dwdt_trace.push_back(CA1_list[0]->exc_conns[CA3_list[i]]->dweightdt_trace);
    }

    for (int i = 0; i < num_CA1; i++) {
        CA1_voltage_trace.push_back(CA1_list[i]->voltage_trace);
    }

    cout << "data ended" << endl;



    string filename = "_network_shortuniform";
   
    export2csv_vectorvector("rawdatas/CA1_voltage_" + filename + ".csv", CA1_voltage_trace);
    cout << "CA1_voltage_trace" << endl;
    export2csv_vectorvector("rawdatas/weight_trace" + filename + ".csv", weight_trace);
    cout << "weight_trace" << endl;

    //export2csv_trace("rawdatas/CA3_trace" + filename + ".csv", CA3_list);
    //cout << "CA3_trace" << endl;
    //export2csv_vectorvector("rawdatas/IS_trace" + filename + ".csv", IS_trace);
    //cout << "IS_trace" << endl;
    //export2csv_vectorvector("rawdatas/ET_trace" + filename + ".csv", ET_trace);
    //cout << "ET_trace" << endl;
    //export2csv_vectorvector("rawdatas/chem_signal_trace" + filename + ".csv", chem_signal_trace);
    //cout << "chem_signal_trace" << endl;
    //export2csv_vectorvector("rawdatas/dwdt_trace" + filename + ".csv", dwdt_trace);
    //cout << "dwdt_trace" << endl;

    return 0;
}