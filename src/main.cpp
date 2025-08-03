#include "Engine.h"
#include "Renderer.h"
#include "SDL2/SDL_stdinc.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_timer.h>
#include <iostream>
#include <print>

int main(int argc, char *argv[]) {
  // Initialise SDL
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    std::cerr << "Failed to initialise SDL2 with error " << SDL_GetError()
              << "\n";
    exit(-1); // what do you look like using return in a constructor
  }

  Renderer render("3D Rotations", WINDOW_WIDTH, WINDOW_HEIGHT);
  bool running = true;
  Engine engine;

  SDL_Event event; // event handlers

  Uint64 now, last = SDL_GetPerformanceCounter();
  double frequency = static_cast<double>(SDL_GetPerformanceFrequency());
  double frameTime = 0;
  float dT = 0;
  while (running) {
    now = SDL_GetPerformanceCounter();
    dT = (now - last) / frequency;
    last = now;

    while (SDL_PollEvent(&event) != 0) {

      now = SDL_GetPerformanceCounter();
      last = now;
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

    //**********Do the updating and calculations*****
    engine.update(dT, dT);

    //***************Do the rendering ***************
    // Clear the previous frame
    render.clear();
    render.draw(engine.getCCWCube());
    engine.resetCCW_cube(); // reset the mesh back to unit points/vectors
    //****************Rendering ends here************

    //*******************Do manual frame delaying*************************
    frameTime =
        static_cast<double>(SDL_GetPerformanceCounter() - now) / frequency;
    if (frameTime < (1 / 60.0f))
      SDL_Delay((Uint32)(((1 / 60.0) - frameTime) * 1000.0f));
  }
  render.cleanUp();
  render.~Renderer();
  SDL_Quit();
  return 0;
}
