#include "Engine.h"
#include <Renderer.h>
#include <cmath>
#include <ostream>
#include <v3Util.h>

// should only be globals here
inline Triangle triangleProj, triangleTranslated;
inline Triangle triangleRot_Z, triangleRot_ZX;
Engine::Engine() {
  // projection matrix
  // initialise everthing to zero first
  initProjectionMatrix(_projectionMatrix);
  cout << _projectionMatrix;
  /*Matrix4(_matProj);*/
  initRotMatX(_rotationMatrix_x, 45.0f);
  cout << "Rotation on the x-axis\n" << _rotationMatrix_x;

  initRotMatZ(_rotationMatrix_z, 45.0f);
  cout << "Rotation on the z-axis\n" << _rotationMatrix_z;
  createCube();
  CCW_cube();
}
void Engine::initProjectionMatrix(Matrix4x4 &mat) {
  mat.m[0][0] = 1.0f / (_fAspectRatio * tan(_fFOVRad));
  mat.m[1][1] = 1.0f / tan(_fFOVRad); // 1/tan(angle_in_rad)
  mat.m[2][2] = -(_fFar + _fNear) / (_fFar - _fNear);
  mat.m[3][2] = -1.0f;
  mat.m[2][3] = -(2 * _fFar * _fNear) / (_fFar - _fNear);
}
void Engine::CCW_cube() {
  _CCW_cube.tris = {
      // Front Face
      Triangle(V3D(), V3D(1, 0, 0), V3D(1, 1, 0)),
      Triangle(V3D(1, 1, 0), V3D(0, 1, 0), V3D()),
      // Right Face
      Triangle(V3D(1.0f, 0.0f, 0.0f), V3D(1.0f, 0.0f, 1.0f),
               V3D(1.0f, 1.0f, 1.0f)),
      Triangle(V3D(1.0f, 1.0f, 1.0f), V3D(1.0f, 1.0f, 0.0f),
               V3D(1.0f, 0.0f, 0.0f)),
      // Back Face
      Triangle(V3D(1.0f, 0.0f, 1.0f), V3D(0.0f, 0.0f, 1.0f),
               V3D(0.0f, 1.0f, 1.0f)),
      Triangle(V3D(0.0f, 1.0f, 1.0f), V3D(1.0f, 1.0f, 1.0f),
               V3D(1.0f, 0.0f, 1.0f)),
      // Left Face
      Triangle(V3D(0.0f, 0.0f, 1.0f), V3D(), V3D(0.0f, 1.0f, 0.0f)),
      Triangle(V3D(0.0f, 1.0f, 0.0f), V3D(0.0f, 1.0f, 1.0f),
               V3D(0.0f, 0.0f, 1.0f)),
      // Top Face
      Triangle(V3D(0.0f, 1.0f, 0.0f), V3D(1.0f, 1.0f, 0.0f),
               V3D(1.0f, 1.0f, 1.0f)),
      Triangle(V3D(1.0f, 1.0f, 1.0f), V3D(0.0f, 1.0f, 1.0f),
               V3D(0.0f, 1.0f, 0.0f)),
      // Bottom Face
      Triangle(V3D(), V3D(1.0f, 0.0f, 0.0f), V3D(1.0f, 0.0f, 1.0f)),
      Triangle(V3D(1.0f, 0.0f, 1.0f), V3D(0.0f, 0.0f, 1.0f), V3D())

  };
  // let's somar make this pool here
}
void Engine::createCube() {

  _meshCube.tris = {
      //************Front Face*****************
      Triangle(V3D(), V3D(0.0f, 1.0f, 0.0f), V3D(1.0f, 1.0f, 0.0f)),
      Triangle(V3D(0.0f, 0.0f, 0.0f), V3D(1.0f, 1.0f, 0.0f),
               V3D(1.0f, 0.0f, 0.0f)),

      //************Left Face*****************
      Triangle(V3D(0.0f, 0.0f, 1.0f), V3D(0.0f, 1.0f, 1.0f),
               V3D(0.0f, 1.0f, 0.0f)),
      Triangle(V3D(0.0f, 0.0f, 1.0f), V3D(0.0f, 1.0f, 0.0f), V3D()),

      //***********Back Face******************
      Triangle(V3D(1.0f, 0.0f, 1.0f), V3D(1.0f, 1.0f, 1.0f),
               V3D(0.0f, 1.0f, 1.0f)),
      Triangle(V3D(1.0f, 0.0f, 1.0f), V3D(0.0f, 1.0f, 1.0f),
               V3D(0.0f, 0.0f, 1.0f)),

      //***********Right Face******************
      Triangle(V3D(1.0f, 0.0f, 0.0f), V3D(1.0f, 1.0f, 0.0f),
               V3D(1.0f, 1.0f, 1.0f)),
      Triangle(V3D(1.0f, 0.0f, 0.0f), V3D(1.0f, 1.0f, 1.0f),
               V3D(1.0f, 0.0f, 1.0f)),

      //***********Top Face******************
      Triangle(V3D(1.0f, 1.0f, 1.0f), V3D(1.0f, 1.0f, 0.0f),
               V3D(0.0f, 1.0f, 0.0f)),
      Triangle(V3D(1.0f, 1.0f, 1.0f), V3D(0.0f, 1.0f, 0.0f),
               V3D(0.0f, 1.0f, 1.0f)),
      //***********Bottom  Face******************
      Triangle(V3D(0.0f, 0.0f, 1.0f), V3D(), V3D(1.0f, 0.0f, 0.0f)),
      Triangle(V3D(0.0f, 0.0f, 1.0f), V3D(1.0f, 0.0f, 0.0f),
               V3D(1.0f, 0.0f, 1.0f)),

  };
}
void Engine::multiplyMatrixVector(const V3D &in, V3D &out,
                                  const Matrix4x4 &matrix) {

  // Avoids doing any calculations where there are any 0s in the perspective
  // projection matrix
  /*out.x = in.x * matrix.m[0][0];*/
  /*out.y = in.y * matrix.m[1][1];*/
  /*out.z = (in.z * matrix.m[2][2]) + (matrix.m[3][2] * in.w);*/
  /*V3D Out;*/
  out.x = (in.x * matrix.m[0][0]) + (in.y * matrix.m[1][0]) +
          (in.z * matrix.m[2][0]) + (1 * matrix.m[3][0]);

  out.y = (in.x * matrix.m[0][1]) + (in.y * matrix.m[1][1]) +
          (in.z * matrix.m[2][1]) + (1 * matrix.m[3][1]);

  out.z = (in.x * matrix.m[0][2]) + (in.y * matrix.m[1][2]) +
          (in.z * matrix.m[2][2]) + (1 * matrix.m[3][2]);
  // forth element in our matrix -> 1 to normalise all out elements
  float w = (in.x * matrix.m[0][3]) + (in.y * matrix.m[1][3]) +
            (in.z * matrix.m[2][3]) + (1 * matrix.m[3][3]);
  // start scaling the shape from 4D to 3D
  if (w != 0) {
    out.x /= w;
    out.y /= w;
    out.z /= w;
  }
  /*return out;*/
}
void Engine::update(Renderer &renderer, float total_rot_x, float total_rot_z) {
  std::cout << __FUNCTION__ << " Line " << __LINE__
            << ": Elapsed Time= " << f_elapsed_time << "\n";
  for (auto &t : _CCW_cube.tris) {

    // rotate the points around the z-axis
    multiplyMatrixVector(t.p1, triangleRot_Z.p1, getRotZ(f_elapsed_time));
    multiplyMatrixVector(t.p2, triangleRot_Z.p2, getRotZ(f_elapsed_time));
    multiplyMatrixVector(t.p3, triangleRot_Z.p3, getRotZ(f_elapsed_time));

    // rotate the points around the x-axis
    multiplyMatrixVector(triangleRot_Z.p1, triangleRot_ZX.p1,
                         getRotX(f_elapsed_time));
    multiplyMatrixVector(triangleRot_Z.p2, triangleRot_ZX.p2,
                         getRotX(f_elapsed_time));
    multiplyMatrixVector(triangleRot_Z.p3, triangleRot_ZX.p3,
                         getRotX(f_elapsed_time));
    // translate the 'transformed' points further into the z-axis
    triangleTranslated = triangleRot_ZX;

    // should be adjustable in im gui
    triangleTranslated.p1.z += _distance_from_camera;
    triangleTranslated.p2.z += _distance_from_camera;
    triangleTranslated.p3.z += _distance_from_camera;
    // project the translated points from 3D to 2D with 3D perspective
    multiplyMatrixVector(triangleTranslated.p1, triangleProj.p1,
                         _projectionMatrix);
    multiplyMatrixVector(triangleTranslated.p2, triangleProj.p2,
                         _projectionMatrix);
    multiplyMatrixVector(triangleTranslated.p3, triangleProj.p3,
                         _projectionMatrix);

    // scale to the points to our viewport
    scaleToView(triangleProj);
    renderer.drawSquare(triangleProj);
    /*SDL_RenderPresent(renderer.getRender());*/
  }
}

Mesh Engine::getMeshCube() { return _meshCube; }
Matrix4x4 Engine::getProjectionMatrix4x4() { return _projectionMatrix; }

void Engine::scaleToView(Triangle &shape) {
  // Scale the projected vector result from [-1,1] to [0,2]

  shape.p1.x += 1.0f;
  shape.p1.y += 1.0f;
  shape.p2.x += 1.0f;
  shape.p2.y += 1.0f;
  shape.p3.x += 1.0f;
  shape.p3.y += 1.0f;

  // Scale to fit the viewport
  shape.p1.x = shape.p1.x * 0.5f * VIEWPORT_WIDTH;
  shape.p1.y = shape.p1.y * 0.5f * VIEWPORT_HEIGHT;

  shape.p2.y = shape.p2.y * 0.5f * VIEWPORT_HEIGHT;
  shape.p2.x = shape.p2.x * 0.5f * VIEWPORT_WIDTH;

  shape.p3.y = shape.p3.y * 0.5f * VIEWPORT_HEIGHT;
  shape.p3.x = shape.p3.x * 0.5f * VIEWPORT_WIDTH;
}

// Im testing something here
void Engine::Matrix4(Matrix4x4 &mat) {
  // fov in degrees
  float fov_rad = 45 * (M_PI / 180.0f);
  float focal = 1.0f / std::tan(fov_rad / 2.0f);
  float far = _fFar, near = _fNear;

  _matProj.m[0][0] = focal / (_fAspectRatio);
  _matProj.m[1][1] = focal; // 1/tan(angle_in_rad)
  _matProj.m[2][2] = (far + near) / (near - far);
  _matProj.m[3][2] = -1.0f;
  _matProj.m[2][3] = (2 * far * near) / (near - far);
}
Matrix4x4 Engine::getMatProj() { return _matProj; }
/**
 *@brief calculates the surface normal of a triangle. All surfaces in this
 * engine are all flat surfaces
 * @param tri triangle of which we're calculating the surface normal for
 */
V3D Engine::calculateNormal(const Triangle &tri) {
  V3D u(tri.p3.x - tri.p2.x, tri.p3.y - tri.p2.y, tri.p3.z - tri.p2.z);
  V3D w(tri.p1.x - tri.p2.x, tri.p1.y - tri.p2.y, tri.p1.z - tri.p2.z);
  auto x = (u.y * w.z) - (u.z * w.y);
  auto y = (u.z * w.x) - (u.x * w.z);
  auto z = (u.x * w.y) - (u.y * w.x);

  _surfaceNormal.x = x, _surfaceNormal.y = y, _surfaceNormal.z = z;
  cout << "Surface Normal \n" << _surfaceNormal;
  return _surfaceNormal;
}

void Engine::initRotMatX(Matrix4x4 &matX, float angle_deg) {
  // convert angle in degrees to rad
  /*f_theta_x = (f_theta_x * M_PI) / 180.0f;*/
  /*f_theta += 1.0f * f_elapsed_time;*/
  matX.m[0][0] = 1;
  matX.m[1][1] = cos(f_theta_x);
  matX.m[1][2] = -sin(f_theta_x);
  matX.m[2][1] = sin(f_theta_x);
  matX.m[2][2] = cos(f_theta_x);
  matX.m[3][3] = 1;
}
void Engine::initRotMatZ(Matrix4x4 &matZ, float angle_deg) {
  // convert angle in degrees to rad
  /*f_theta_z = (f_theta_z * M_PI) / 180.0f;*/

  // need a different rotation 'speed' to avoid gymbal lock
  matZ.m[0][0] = cos(f_theta_z);
  matZ.m[0][1] = -sin(f_theta_z);
  matZ.m[1][0] = sin(f_theta_z);
  matZ.m[1][1] = cos(f_theta_z);
  matZ.m[2][2] = 1;
  matZ.m[3][3] = 1;
}

Matrix4x4 Engine::getRotX(float elapsed_time) {

  /*f_theta = (f_theta * M_PI) / 180.0f;*/
  /*f_theta_x = ((0.0f * M_PI) / 180.0f) * elapsed_time;*/
  f_theta_x += elapsed_time;
  _rotationMatrix_x.m[0][0] = 1;
  _rotationMatrix_x.m[1][1] = cos(f_theta_x);
  _rotationMatrix_x.m[1][2] = -sin(f_theta_x);
  _rotationMatrix_x.m[2][1] = sin(f_theta_x);
  _rotationMatrix_x.m[2][2] = cos(f_theta_x);
  return _rotationMatrix_x;
}

Matrix4x4 Engine::getRotZ(float elapsed_time) {
  /*f_theta = (f_theta * M_PI) / 180.0f;*/
  f_theta_z += elapsed_time;
  // Take angle of rotation * delta to get new angle in radian
  //
  //
  /*f_theta_z = ((90.0f * M_PI) / 180.0f) * elapsed_time;*/
  _rotationMatrix_z.m[0][0] = cos(f_theta_z * 0.5f);
  _rotationMatrix_z.m[0][1] = -sin(f_theta_z * 0.5f);
  _rotationMatrix_z.m[1][0] = sin(f_theta_z * 0.5f);
  _rotationMatrix_z.m[1][1] = cos(f_theta_z * 0.5f);
  _rotationMatrix_z.m[2][2] = 1;
  _rotationMatrix_z.m[3][3] = 1;

  return _rotationMatrix_z;
}
V3D Engine::getSurfaceNormal(const Triangle &t) { return calculateNormal(t); }

float Engine::getNormalDirection(V3D &normal_vec) {
  return acosf(normal_vec.z / normal_vec.length());
}
