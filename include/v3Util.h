#ifndef V3UTIL_H
#define V3UTIL_H

#include <array>
#include <cmath>
#include <iostream>
#include <vector>

#define MAT_SIZE 4 // We'll mostly be using 4x4 matrices in this codebase

struct V3D {
  float x = 0.0f, y = 0.0f, z = 0.0f,
        // this w will allow for us to have matrix multiplication further in
        // the pipeline
      w = 1.0f;
  // constructor that defaults to the origin besides for the w component
  V3D(float X, float Y, float Z) {
    x = X;
    y = Y;
    z = Z;
    w = 1.0f;
  }

  // No parameters constructor
  V3D() : x(0.0f), y(0.0f), z(0.0f), w(1.0f) {};

  // Overload = to allow for easier assignement (even in the tests)
  V3D &operator=(const V3D &rhs) {
    if (*this != rhs) {
      x = rhs.x;
      y = rhs.y;
      z = rhs.z;
    }
    return *(this);
  }

  // Overload == and != to make assignement of vectors easier
  bool operator==(const V3D &rhs) {
    if (x != rhs.x)
      return false;
    else if (y != rhs.y)
      return false;
    else if (z != rhs.z)
      return false;
    return true;
  }

  bool operator!=(const V3D &rhs) {

    // Deferences the struct and return false
    // how this works is with the assumption that this and rhs are equal
    return !(*(this) == rhs);
  }

  float length() { return std::sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2)); }

  // overloading to make it easier to print out Triangles
  friend std::ostream &operator<<(std::ostream &out, const V3D &p) {
    out << "< " << p.x << "x, " << p.y << "y, " << p.z << "z > w=" << p.w
        << "\n";
    return out;
  }
};
// Triangles and meshes have a special relationship
struct Triangle {
  V3D p1; //{0, 0, 0};
  V3D p2; //{0, 0, 0};
  V3D p3; //{0, 0, 0};

  // hold our actual cartesian points of our object
  std::array<V3D, 3> points;

  // Constructor
  Triangle(struct V3D P1, struct V3D P2, struct V3D P3) {
    p1 = P1;
    p2 = P2;
    p3 = P3;
    points.at(0) = p1;
    points.at(1) = p2;
    points.at(2) = p3;
  }

  // Default Constructor to set everything to initialise all points
  Triangle()
      : p1(0.0f, 0.0f, 0.0f), p2(0.0f, 0.0f, 0.0f), p3(0.0f, 0.0f, 0.0f) {
    points.at(0) = p1;
    points.at(1) = p2;
    points.at(2) = p3;
  }
};

struct Mesh {
  std::vector<Triangle> tris;
};

/**************************************************
 *               OPERATOR OVERLOADINGS             *
 ***************************************************/

/*
 * @brief this is an operator overloading that multplies the
 * squear 4x4 matrix on the left with the square 4x4 matric on the
 * right
 * NOTE: Matrix multiplication is no commucative, the ordering of the
 * matrices matter
 * @param rhs matrix on the right hand side
 * @return result of left-hand side matrix multiplied by the rhs matrix
 */
// I need to find a better way to initialise variables/data type
// and any sort of container
struct Matrix4x4 {
  float m[4][4];
  float default_value = 0;
  /*@brief constructor that initialises the underlying matrix
   *@param val is the default value all matrix entries are set to
   *
   */
  Matrix4x4(int val) { init_matrix4x4(val); }

  // Constructor
  Matrix4x4() { init_matrix4x4(0); }

  void init_matrix4x4(float val) {
    for (int i = 0; i < MAT_SIZE; i++) {
      for (int j = 0; j < MAT_SIZE; j++) {
        m[i][j] = val;
      }
    }
  }
  // Returns a new matrix all together of size 4x4
  Matrix4x4 operator*(const Matrix4x4 &rhs) {
    Matrix4x4 result;

    // This only works for matrices of nxn size
    for (int row = 0; row < MAT_SIZE; row++) {   // number of rows
      for (int col = 0; col < MAT_SIZE; col++) { // number of colums
        for (int i = 0; i < MAT_SIZE; i++) {
          result.m[row][col] += this->m[row][i] * rhs.m[i][col];
        }
        /*std::cout << result.m[row][col] << ", ";*/
      }
    }
    return result;
  }

  // This is strictly for matrix multiplication
  Matrix4x4 &operator=(Matrix4x4 &rhs) {
    // Setting the first row of this mat to be equal to the right
    for (int r = 0; r < MAT_SIZE; r++) {
      for (int c = 0; c < MAT_SIZE; c++) {
        this->m[r][c] = rhs.m[r][c];
      }
    }
    return (*this);
  }

  friend std::ostream &operator<<(std::ostream &out, const Matrix4x4 &obj) {
    for (int i = 0; i < MAT_SIZE; i++) {
      out << "[";
      for (int j = 0; j < MAT_SIZE; j++) {
        out << "\t" << obj.m[i][j] << "\t";
      }

      out << "]" << std::endl;
    }
    return out;
  }
};

#endif
