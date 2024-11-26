#pragma once
#define _USE_MATH_DEFINES 

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <math.h>
#include <random>
#include <utility>
#include <algorithm>

using namespace std;

string rgbToHex(int r, int g, int b) {
    std::stringstream stream;
    stream << "#" << std::setfill('0') << std::setw(2) << std::hex << r
        << std::setw(2) << g << std::setw(2) << b;
    return stream.str();
}

struct VectorWithGid {
    double value;
    int gid;
};

bool compare_by_value(const VectorWithGid& a, const VectorWithGid& b) {
    return a.value < b.value;
}

vector<pair<int, int>> generate_exc_connlist(int num_cell) {
    vector<pair<int, int>> ans;
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<double> uniform_dist(0.0, 1.0);

    for (int i = 0; i < num_cell; i++) {
        if (i < num_cell * 3 / 4) { // this is excitatory cell
            for (int j = 0; j < num_cell; j++) {
                if (j != i) { // don't connect with myself
                    double random_number = uniform_dist(gen); // lets make connection!
                    if (random_number < 0.02) {
                        ans.push_back(make_pair(i, j));
                    }
                }

            }

        }
    }
    return ans;
}

vector<pair<int, int>> generate_gl_inh_connlist(int num_cell) {
    vector<pair<int, int>> ans;

    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<double> uniform_dist(0.0, 1.0);

    for (int i = 0; i < num_cell; i++) {
        if (num_cell * 3 / 4 <= i < num_cell * 3 / 4 + (num_cell / 4) * 0.65) { // this is global inhibitory cell
            for (int j = 0; j < num_cell; j++) {
                if (j != i) { // don't connect with myself
                    double random_number = uniform_dist(gen); // lets make connection!
                    if (random_number < 0.02) {
                        ans.push_back(make_pair(i, j));
                    }
                }
            }
        }
    }
    return ans;
}


vector<pair<int, int>> generate_loc_inh_connlist(int num_cell, const vector<vector<double>> distance_map) {
    vector<pair<int, int>> ans;
    int boundary = num_cell * 500 / 20000;
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<double> uniform_dist(0.0, 1.0);

    for (int i = 0; i < num_cell; i++) {
        if ((num_cell * 3 / 4 + (num_cell / 4) * 0.65) <= i) { // this is local inhibitory cell
            std::vector<VectorWithGid> pos_with_gid(num_cell);

            for (int j = 0; j < num_cell; ++j) {
                pos_with_gid[j].value = distance_map[i][j];
                pos_with_gid[j].gid = j;
            }
            std::sort(pos_with_gid.begin(), pos_with_gid.end(), compare_by_value);

            for (int j = 0; j < boundary; ++j) {
                double random_number = uniform_dist(gen); // lets make connection!
                if (random_number < 5) {
                    ans.push_back(make_pair(i, pos_with_gid[j].gid));
                }
            }

        }
    }
    return ans;
}


template <typename T>
void export2csv_trace(string filename, vector<T*> cell_list) {

    int cell_num = cell_list.size();
    int t_size = cell_list[0]->rate_trace.size();

    ofstream myfile;
    myfile.open(filename);
    for (int gid = 0;gid < cell_num;gid++) {
        if (gid == 0) { myfile << "cell_0"; }
        else {
            myfile << ",cell_" << gid;
        }
    }
    myfile << endl;

    for (int t = 0;t < t_size;t++) {
        for (int gid = 0;gid < cell_num;gid++) {
            if (gid == 0) { myfile << cell_list[gid]->rate_trace.at(t); }
            else {
                myfile << "," << cell_list[gid]->rate_trace.at(t);
            }
        }
        myfile << endl;
    }
    myfile.close();
}


void export2csv_vectorvector(string filename, vector<vector<double>> data){
    int cell_num = data.size();
    int t_size = data[0].size();

   // cout << cell_num << " " << t_size << endl;

    ofstream myfile;
    myfile.open(filename);
    for (int i = 0;i < cell_num;i++) {
        if (i == 0) { myfile << "precell_0"; }
        else {
            myfile << ",precell_" << i;
        }
    }
    myfile << endl;

    for (int t = 0;t < t_size;t++) {
        for (int i = 0;i< cell_num;i++) {
            //cout << i << " " << t << " " << data[i][t] << endl;
            if (i== 0) { myfile << data[i][t]; }
            else {
                myfile << "," << data[i][t];
            }
        }
        myfile << endl;
    }
    myfile.close();
}