#include <unittest/unittest.h>

#include <cusp/io.h>
#include <cusp/dense_matrix.h>
#include <cusp/convert.h>
#include <cusp/equal.h>

void TestLoadMatrixMarketFileCoordinateRealGeneral(void)
{
    // load matrix
    cusp::coo_matrix<int, float, cusp::host> coo;
    cusp::load_matrix_market_file(coo, "data/test/coordinate_real_general.mtx");

    // convert to dense_matrix
    cusp::dense_matrix<float, cusp::host> D;
    cusp::convert(D, coo);

    // expected result
    cusp::dense_matrix<float, cusp::host> E(5, 5);
    E(0,0) =  1.000e+00; E(0,1) =  0.000e+00; E(0,2) =  0.000e+00; E(0,3) =  6.000e+00; E(0,4) =  0.000e+00;
    E(1,0) =  0.000e+00; E(1,1) =  1.050e+01; E(1,2) =  0.000e+00; E(1,3) =  0.000e+00; E(1,4) =  0.000e+00;
    E(2,0) =  0.000e+00; E(2,1) =  0.000e+00; E(2,2) =  2.500e-01; E(2,3) =  0.000e+00; E(2,4) =  0.000e+00;
    E(3,0) =  0.000e+00; E(3,1) =  2.505e+02; E(3,2) =  0.000e+00; E(3,3) = -2.500e+02; E(3,4) =  3.875e+01;
    E(4,0) =  0.000e+00; E(4,1) =  0.000e+00; E(4,2) =  0.000e+00; E(4,3) =  0.000e+00; E(4,4) =  1.200e+01;

    ASSERT_EQUAL(cusp::equal(D,E), true);
}
DECLARE_UNITTEST(TestLoadMatrixMarketFileCoordinateRealGeneral);

void TestLoadMatrixMarketFileCoordinatePatternSymmetric(void)
{
    // load matrix
    cusp::coo_matrix<int, float, cusp::host> coo;
    cusp::load_matrix_market_file(coo, "data/test/coordinate_pattern_symmetric.mtx");

    // convert to dense_matrix
    cusp::dense_matrix<float, cusp::host> D;
    cusp::convert(D, coo);

    // expected result
    cusp::dense_matrix<float, cusp::host> E(5, 5);
    E(0,0) =  1.000e+00; E(0,1) =  0.000e+00; E(0,2) =  0.000e+00; E(0,3) =  0.000e+00; E(0,4) =  0.000e+00;
    E(1,0) =  0.000e+00; E(1,1) =  1.000e+00; E(1,2) =  0.000e+00; E(1,3) =  1.000e+00; E(1,4) =  0.000e+00;
    E(2,0) =  0.000e+00; E(2,1) =  0.000e+00; E(2,2) =  1.000e+00; E(2,3) =  0.000e+00; E(2,4) =  0.000e+00;
    E(3,0) =  0.000e+00; E(3,1) =  1.000e+00; E(3,2) =  0.000e+00; E(3,3) =  1.000e+00; E(3,4) =  1.000e+00;
    E(4,0) =  0.000e+00; E(4,1) =  0.000e+00; E(4,2) =  0.000e+00; E(4,3) =  1.000e+00; E(4,4) =  1.000e+00;

    ASSERT_EQUAL(cusp::equal(D,E), true);
}
DECLARE_UNITTEST(TestLoadMatrixMarketFileCoordinatePatternSymmetric);

////    E(0,0) =  0.000e+00; E(0,1) =  0.000e+00; E(0,2) =  0.000e+00; E(0,3) =  0.000e+00; E(0,4) =  0.000e+00;
////    E(1,0) =  0.000e+00; E(1,1) =  0.000e+00; E(1,2) =  0.000e+00; E(1,3) =  0.000e+00; E(1,4) =  0.000e+00;
////    E(2,0) =  0.000e+00; E(2,1) =  0.000e+00; E(2,2) =  0.000e+00; E(2,3) =  0.000e+00; E(2,4) =  0.000e+00;
////    E(3,0) =  0.000e+00; E(3,1) =  0.000e+00; E(3,2) =  0.000e+00; E(3,3) =  0.000e+00; E(3,4) =  0.000e+00;
////    E(4,0) =  0.000e+00; E(4,1) =  0.000e+00; E(4,2) =  0.000e+00; E(4,3) =  0.000e+00; E(4,4) =  0.000e+00;
