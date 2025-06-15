#include "Engine.h"
#include "Renderer.h"
#include "SDL2/SDL_stdinc.h"
#include "v3Util.h"
#include <SDL.h>
#include <SDL_events.h>
#include <SDL_render.h>
#include <SDL_timer.h>
#include <iostream>
#include <ostream>

// Function Signatures
void triangleDebug(const Triangle &tri1, const Triangle &tri2,
                   std::string tri1_name = "Left Triangle\n",
                   std::string tri2_name = "Right Triangle\n") {
  cout << tri2_name << tri2.p1 << tri2.p2 << tri2.p3;
  cout << tri1_name << tri1.p1 << tri1.p2 << tri1.p3;
  cout << endl;
}
// Global Scope
const int ROTATION_SPEED_X = 45.0f;
const int ROTATION_SPEED_Z = 90.0f;

int main(int argc, char *argv[]) {
  // Initialise SDL
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0) {
    std::cerr << "Failed to initialise SDL2 with error " << SDL_GetError()
              << "\n";
    exit(-1); // what do you look like using return in a constructor
  }

  Renderer render("3D Rotations", WINDOW_WIDTH, WINDOW_HEIGHT);
  bool running = true;
  Engine engine;

  Uint64 NOW = SDL_GetPerformanceCounter();
  Uint64 LAST = 0;
  float dT = 0;
  float total_rotations_z = 0.0f;
  float total_rotations_x = 0.0f;
  SDL_Event event; // event handlers

  while (running) {
    /*start_time = std::chrono::high_resolution_clock::now();*/
    while (SDL_PollEvent(&event) != 0) {

      switch (event.type) {
      case SDL_QUIT:
        running = false;
        break;
      case SDL_KEYDOWN:
        // Escape closes the window only for debuggin reasons
        if (event.key.keysym.sym == SDLK_ESCAPE)
          running = false;
        break;
      default:
        break;
      }
    }
    LAST = NOW;
    NOW = SDL_GetPerformanceCounter();
    dT = (NOW - LAST) / (float)SDL_GetPerformanceFrequency();
    cout << "Main " << __LINE__ << ": Delta Time-> " << dT << '\n';
    total_rotations_z += ROTATION_SPEED_Z * dT; // 90degrees per sec
    total_rotations_x += ROTATION_SPEED_X * dT;
    std::cout << "Main " << __LINE__ << ": Total Z-Rotations -> "
              << total_rotations_z << "\n"
              << "Main " << __LINE__ << ": Total X-Rotations -> "
              << total_rotations_x << "\n";
    //******************************************
    // do the updating and calculations
    /*SDL_SetRenderDrawColor(render.getRender(), 0, 0, 0, 255);*/
    /*SDL_RenderClear(render.getRender());*/
    /*SDL_SetRenderDrawColor(render.getRender(), 255, 255, 255, 255);*/

    engine.update(render, total_rotations_x, total_rotations_z);
    /// render the calculated pointes

    //**************************************

    /*end_time = std::chrono::high_resolution_clock::now();*/

    /*int counter = 0;*/

    /*float delta_time = 1.0f / 60.0f;*/
    /*for (auto &t : engine.getMeshCube().tris) // triangles make up the mesh*/
    /*{*/
    /*  counter++;*/
    /**/
    /*  cout << "====Reading from meshCube triangle number " << counter*/
    /*       << "=====\n";*/
    /**/
    /*  // First rotate in the Z axis*/
    /*  cout << "Rotation around the z axis\n";*/
    /*  engine.multiplyMatrixVector(t.p1, triangleRot_Z.p1,*/
    /*                              engine.getRotZ(delta_time));*/
    /*  engine.multiplyMatrixVector(t.p2, triangleRot_Z.p2,*/
    /*                              engine.getRotZ(delta_time));*/
    /*  engine.multiplyMatrixVector(t.p3, triangleRot_Z.p3,*/
    /*                              engine.getRotZ(delta_time));*/
    /**/
    /*  triangleDebug(t, triangleRot_Z, "Original triangle\n", "Rotated on
     * Z\n");*/
    /*  // rotate in the X axis*/
    /*  cout << "Rotation around the ZX axis\n";*/
    /**/
    /*  engine.multiplyMatrixVector(triangleRot_Z.p1, triangleRot_ZX.p1,*/
    /*                              engine.getRotX(delta_time));*/
    /*  engine.multiplyMatrixVector(triangleRot_Z.p2, triangleRot_ZX.p2,*/
    /*                              engine.getRotX(delta_time));*/
    /*  engine.multiplyMatrixVector(triangleRot_Z.p3, triangleRot_ZX.p3,*/
    /*                              engine.getRotX(delta_time));*/
    /**/
    /*  triangleTranslated = triangleRot_ZX;*/
    /**/
    /*  triangleTranslated.p1.z = triangleRot_ZX.p1.z + 6.0f;*/
    /*  triangleTranslated.p2.z = triangleRot_ZX.p2.z + 6.0f;*/
    /*  triangleTranslated.p3.z = triangleRot_ZX.p3.z + 6.0f;*/
    /**/
    /*triangleDebug(triangleRot_ZX, triangleTranslated,*/
    /*"Rotated around Z then X\n", "Translated by 3 into Z\n");*/
    /**/
    /*  engine.multiplyMatrixVector(triangleTranslated.p1,
       triangleProj.p1,*/
    /*                              engine.getProjectionMatrix4x4());*/
    /*  engine.multiplyMatrixVector(triangleTranslated.p2,
       triangleProj.p2,*/
    /*                              engine.getProjectionMatrix4x4());*/
    /*  engine.multiplyMatrixVector(triangleTranslated.p3,
       triangleProj.p3,*/
    /*                              engine.getProjectionMatrix4x4());*/
    /**/
    /*  triangleDebug(triangleTranslated, triangleProj, "Translated
       Triangle\n",*/
    /*                "Projected Triangle\n");*/
    /**/
    /*  engine.scaleToView(triangleProj);*/
    /**/
    /*render.drawTriangle(triangleProj);*/
    /*  render.drawSquare(triangleProj);*/
    /**/
    /*  SDL_RenderPresent(render.getRender());*/
    /**/
  }
  render.cleanUp();
  render.~Renderer();
  SDL_Quit();
  return 0;
}
