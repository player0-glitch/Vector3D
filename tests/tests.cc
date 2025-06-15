#include "../include/v3Util.h"
#include <cmath>
#include <gtest/gtest.h>
#include <vector>

#define TEST_SIZE 3
static const float EPSILON = 1e-5;

template <typename T>
void expectEqualLoop(const T &value, const std::vector<T> &container) {
  for (const auto &e : container) {
    EXPECT_EQ(e, value);
  }
}
/*@brief performs vector matrix multiplication with a 4by1 vector
 */
V3D vectorMatrixMultiplication(const V3D &in, const Matrix4x4 &matrix) {
  V3D out(0.0f, 0.0f, 0.0f);

  // Hand written computations to avoid all zeros
  out.x = in.x * matrix.m[0][0];
  out.y = in.y * matrix.m[1][1];
  out.z = (in.z * matrix.m[2][2]) + (matrix.m[3][2] * in.w);

  float w = 1;
  w = in.z * matrix.m[2][3];
  // start scaling the matrix from 4D back to 3D
  if (w != 0.0f) {
    /*out.x /= w;*/
    /*out.y /= w;*/
    /*out.z /= w;*/
  }

  return out;
};
/**
 * @brief calculates the direction of the normal to the surface of the
 * triangle
 */
auto calculateNormal(const Triangle &tri) -> V3D {
  /*
   * Normal = U cross W
   * where:
   *      U=P3P2=P3-P2  //P2-P3
   *      W=P1P2=P1-P2  //P2-P1
   */
  V3D u(-tri.p3.x + tri.p2.x, -tri.p3.y + tri.p2.y, -tri.p3.z + tri.p2.z);
  V3D w(-tri.p1.x + tri.p2.x, -tri.p1.y + tri.p2.y, -tri.p1.z + tri.p2.z);
  auto x = (u.y * w.z) - (u.z * w.y);
  auto y = (u.z * w.x) - (u.x * w.z);
  auto z = (u.x * w.y) - (u.y * w.x);

  V3D crossed(x, y, z);
  /*std::cout<<x;*/
  return crossed;
}
/*@brief use this to do Expect equal in a loop
 *
 */
template <typename T> void Expect_EQ_Loop(T &t1, T t2) { EXPECT_EQ(t1, t2); }

/*
 * @brief method will be used to create the perspective projection matrix
 * that will be used to do the necessary projections
 */
void makePerspectiveProjMatrix(Matrix4x4 &mat) {
  float FOV = 90.0f;
  float aspectRatio = (620.0f / 1020.0f);
  float FOVRad = tanf(FOV / (2 * (acos(-1.0f) / 180)));
  float FOVrad = (45.0f * M_PI) / 180;
  // Make the perspecpective matrix
  mat.m[0][0] = 1.0f / (aspectRatio * tan(FOVrad));
  mat.m[1][1] = 1.0f / tan(FOVrad);
  mat.m[2][2] = -(1000.0f + 0.1f) / (1000.0f - 0.1f);
  mat.m[3][2] = -1.0f;
  mat.m[2][3] = -(2 * 1000.0f * 0.1f) / (1000.0f - 0.1f);
}

/*@brief TEST to make an empty matrix of 4 by 4 */
TEST(Matrix, Initialisation) {

  Matrix4x4 mat(0);
  Matrix4x4 expected(0);
  for (int r = 0; r < 4; r++) {
    for (int c = 0; c < 4; c++) {

      EXPECT_EQ(expected.m[r][c], mat.m[r][c])
          << "\nMismatching entries at " << r << ", " << c;
    }
  }
}

/*@brief TEST that the creation of the perspecpective projection matrix is
 * correct
 */
TEST(Projection, perspecpectiveMatrixInit) {
  Matrix4x4 expected(0), matrix(0);

  makePerspectiveProjMatrix(matrix);
  makePerspectiveProjMatrix(expected);
  // making our expected result to match our functions
  EXPECT_EQ(expected.m[0][0], matrix.m[0][0])
      << "aspectRatio or tangent function went wrong\n";
  EXPECT_EQ(expected.m[1][1], matrix.m[1][1])
      << "1/tanf seems to not work right\n";
  EXPECT_EQ(expected.m[2][2], matrix.m[2][2]);
  EXPECT_EQ(expected.m[2][3], matrix.m[2][3]);
}
/*@ brief TEST for perspecpective projection matrix multiplication
 */
TEST(Projection, vectorMatrixMultiplication) {
  // Triangle 1  points. All these triangles are translated by 3
  // in the postive direction
  V3D tri1_p1(0.0f, 0.0f, 3.0f); //{0,0,0}
  V3D tri1_p2(0.0f, 1.0f, 3.0f); //{0,1,0}
  V3D tri1_p3(1.0f, 1.0f, 3.0f); //{1,1,0}

  // Make the projection matrix
  Matrix4x4 matrix(0);
  makePerspectiveProjMatrix(matrix);
  // This results array represents the points of our triangle (even after
  // the transformation the points go from )
  V3D resultant_1 = vectorMatrixMultiplication(tri1_p1, matrix);
  V3D resultant_2 = vectorMatrixMultiplication(tri1_p2, matrix);
  V3D resultant_3 = vectorMatrixMultiplication(tri1_p3, matrix);

  // These are all points to one triangle after
  // vector and matrix multiplication
  V3D resultants[3] = {resultant_1, resultant_2, resultant_3};
  /* V3D expectedResults[3] = {{0.0f, 0.0f, -4.0006f},
                             {0.0f, 1.0f, -4.0006f},
                             {1.64516f, 1.0f, -4.0006f}};*/
  V3D expected_1(0.0f, 0.0f, -4.0006f);
  V3D expected_2(0.0f, 1.0f, -4.0006f);
  V3D expected_3(1.64516f, 1.0f, -4.0006f);

  std::vector<V3D> resultants_vec(TEST_SIZE);
  resultants_vec.at(0) = resultant_1;
  resultants_vec.at(1) = resultant_2;
  resultants_vec.at(2) = resultant_3;

  std::vector<V3D> expected_vec(TEST_SIZE);
  expected_vec.at(0) = expected_1;
  expected_vec.at(1) = expected_2;
  expected_vec.at(2) = expected_3;

  for (auto r = resultants_vec.begin(), e = expected_vec.begin();
       r != resultants_vec.end(); r++, e++) {
    /*EXPECT_FLOAT_EQ(e->x, r->x) << "mismatching x values\n";*/
    // Because of floating point precision, we only care about accuracry
    // to the 5th decimal place 1e-5
    EXPECT_NEAR(e->x, r->x, EPSILON) << "Mismatching x values\n";
    EXPECT_NEAR(e->y, r->y, EPSILON) << "Mismatching y values\n";
    EXPECT_NEAR(e->z, r->z, EPSILON) << "Mismatching z values\n";

    /*EXPECT_FLOAT_EQ(e->y, r->y) << "mismatching y values\n";*/
    /*EXPECT_FLOAT_EQ(e->z, r->z) << "mismatching z values\n";*/
  }
};

TEST(Matrix, Normalise) {
  // front face of a cube
  //
  // Order of parameters in the constructor is point1,point2,point3
  Triangle example_tri(V3D(-4.0f, 0.0f, 6.0f), V3D(0.0f, 0.0f, 1.0f),
                       V3D(3.0f, 4.0f, 7.0f));
  /*Triangle tri2_f(V3D(0.0f, 0.0f, 0.0f), V3D(1.0f, 1.0f, 0.0f),V3D(1.0f, 0.0f,
   * 0.0f));*/

  auto result = calculateNormal(example_tri);
  std::cout << "surface normal with V=P2P3=P3-P2 \n" << result;
  V3D expected(20.0f, -39.0f, 16.0f);

  EXPECT_NEAR(expected.x, result.x, EPSILON) << "Mismatching x normal values\n";
  EXPECT_NEAR(expected.y, result.y, EPSILON) << "Mismatching y normal values\n";
  EXPECT_NEAR(expected.z, result.z, EPSILON) << "Mismatching z normal values\n";
}
