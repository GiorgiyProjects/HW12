#include <iostream>
#include <fstream>
#include <vector>
#include <istream>
#include <numeric>
#include <sstream>
#include <cmath>
#include <assert.h>
#include <algorithm>
#include <string>
#include <string.h>

using namespace std;
using matrix = std::vector<std::vector<float>>;
using features_t = std::vector<float>;

bool read_features_csv(std::istream& stream, features_t& features) {
    std::string line;
    std::getline(stream, line);
    features.clear();
    std::istringstream linestream{line};

    for (int i; linestream >> i;) {
        features.push_back(i);
        if (linestream.peek() == ',')
            linestream.ignore();
    }
    return stream.good();
}

bool read_features(std::istream& stream, features_t& features) {
    std::string line;
    std::getline(stream, line);

    features.clear();
    std::istringstream linestream{line};
    double value;
    while (linestream >> value) {
        features.push_back(value);
    }
    return stream.good();
}

matrix read_coeff_vectors(string coeff_file) {
    matrix result;
    std::ifstream istream{coeff_file};
    std::string line;
    while (getline(istream, line)) {
        std::istringstream linestream{line};
        vector<float> res;
        for (float x; linestream >> x;) {
            res.push_back(x);
            if (linestream.peek() == ' ')
                linestream.ignore();
        }
        result.push_back(res);
    }
    istream.close();
    return result;
}