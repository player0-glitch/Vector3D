#ifndef ENGINE_H
#define ENGINE_H

#include "Renderer.h"
#include "v3Util.h"

using std::cout, std::endl;
inline const int FRAME_DELAY =
    1000.0 / 60.0; // 60FPS (how long each frame should take to execute)

class Engine {
public:
  Engine();
  Engine(int rows, int cols);
  ~Engine() = default;

  // I don't see why this engine needs to be moveable
  Engine(const Engine &&) = delete;
  // Nor copyable
  Engine(const Engine &) = delete;

  void update(Renderer &render, float total_rot_x, float total_rot_z);
  void createCube();
  void multiplyMatrixVector(const V3D &in, V3D &out, const Matrix4x4 &matrix);
  void scaleToView(Triangle &shape);

  Matrix4x4 &operator*(const Matrix4x4 &rhs);
  Matrix4x4 getRotZ(float elapsed_time);
  Matrix4x4 getRotX(float elapsed_time);
  Matrix4x4 getProjectionMatrix4x4();
  Matrix4x4 getMatProj();
  Mesh getMeshCube();
  float getNormalDirection(V3D &normal_vec);
  Mesh getCCWCube() const { return _CCW_cube; }
  V3D getSurfaceNormal(const Triangle &t);
  /*Mesh getCubeToDraw() const { return _mesh_to_draw; }*/
  void resetCCW_cube();
  double getTargetFrameRate() const { return 1 / 60.0f; }

private:
  void test(V3D &in);
  V3D calculateNormal(const Triangle &tri);
  void initProjectionMatrix(Matrix4x4 &mat);
  void initRotMatX(Matrix4x4 &matX, float angle_deg);
  void initRotMatZ(Matrix4x4 &matZ, float angle_deg);
  void Matrix4(Matrix4x4 &mat);
  void CCW_cube();
  float total_rotations = 0.0f;
  float total_rotations_z = 0.0f;
  float f_elapsed_time = 1.0f / 15.0f;
  float f_theta_z = 45.0f * (M_PI / 180.0f); // radians
  float f_theta_x = 90.0f * (M_PI / 180.0f); // radians
  Mesh _meshCube;
  Mesh _CCW_cube;
  float _fNear = 0.1f;
  float _fFar = 1000.0f;
  float _distance_from_camera = 9.0f;
  float _fFOV_degrees = 45.0f;
  float _fAspectRatio = (VIEWPORT_WIDTH / VIEWPORT_HEIGHT);
  float _fFOVRad = (_fFOV_degrees * M_PI) / 180.0f;
  V3D _surfaceNormal;
  Matrix4x4 _projectionMatrix = {0};
  Matrix4x4 _matProj = {0};
  Matrix4x4 _rotationMatrix_z = {0};
  Matrix4x4 _rotationMatrix_x = {0};
};

#endif
