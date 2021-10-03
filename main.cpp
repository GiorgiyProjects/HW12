#include "LogregClassifier.h"
#include "helpers.h"

using namespace std;

int main([[maybe_unused]]int argc, char** argv) {
    string coeff_file = argv[1];
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <parameters file>" << endl;
        return EXIT_FAILURE;
    }
    auto coef = read_coeff_vectors(coeff_file);
    auto predictor = LogregClassifier{};
    auto features = features_t{};

    int class_expected;
    string buff;
    std::ifstream istream{"data/fashion-mnist_train.csv"};
    assert(istream.is_open());
    int accurate_predictions = 0;
    int total_predictions = 0;
    while (getline(istream, buff, ','))
    {
        class_expected = atoi(buff.c_str());
        if (!read_features_csv(istream, features)) {
            break;
        }
        auto y_pred = predictor.predict_proba(features, coef);
        auto largest = std::max_element( y_pred.begin(), y_pred.end() );
        auto class_predicted = std::distance(y_pred.begin(), largest);
        //cout << class_expected << " " << class_predicted << endl;
        total_predictions++;
        if (class_expected == class_predicted) accurate_predictions++;
    }
    cout << "Accuracy for logistic regression: "<< (float) accurate_predictions / float(total_predictions) << endl;
    istream.close();

}