#define BOOST_TEST_MODULE test
#include <boost/test/included/unit_test.hpp>
#include "LogregClassifier.h"
#include "helpers.h"
using namespace std;

struct ArgsFixture {
    ArgsFixture(): argc(boost::unit_test::framework::master_test_suite().argc),
                   argv(boost::unit_test::framework::master_test_suite().argv){}
    int argc;
    char **argv;
};

BOOST_AUTO_TEST_SUITE( TestSuite )

    struct cout_redirect {
        cout_redirect( std::streambuf * new_buffer )
                : old( std::cout.rdbuf( new_buffer ) )
        { }

        ~cout_redirect( ) {
            std::cout.rdbuf( old );
        }

    private:
        std::streambuf * old;
    };

    BOOST_FIXTURE_TEST_CASE ( test, ArgsFixture ) {
        {
            string coeff_file = "model/logreg_coef.txt";

            auto coef = read_coeff_vectors(coeff_file);
            auto predictor = LogregClassifier{};
            auto features = features_t{};

            std::ifstream istream{"data/test_data_logreg.txt"};
            int class_expected;
            assert(istream.is_open());
            for (int i = 0;i < 9; i++) {
                istream >> class_expected;
                if (!read_features(istream, features)) {
                    break;
                }

                auto y_pred = predictor.predict_proba(features, coef);
                auto largest = std::max_element( y_pred.begin(), y_pred.end() );
                auto class_predicted = std::distance(y_pred.begin(), largest);
                BOOST_CHECK(class_expected == class_predicted);
            }
            istream.close();
        }
    }


BOOST_AUTO_TEST_SUITE_END()
