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

template<typename T>
auto sigma(T x) {
    return 1/(1 + std::exp(-x));
}

class LogregClassifier {
public:
    vector<float> predict_proba(const features_t& feat, const matrix& coef)
    {
        vector<float> result;
        for (size_t i = 0; i < coef.size(); i++)
        {
            auto z = std::inner_product(feat.begin(), feat.end(), ++coef[i].begin(), coef[i].front());
            result.push_back(sigma(z));
        }
        return result;
    }
};
