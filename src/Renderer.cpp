#include "../include/Renderer.h"
#include "Engine.h"
#include "SDL2/SDL_error.h"
#include "SDL2/SDL_rect.h"
#include "SDL2/SDL_render.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include <SDL_error.h>
#include <SDL_rect.h>
#include <iostream>
#include <v3Util.h>
// These variables are used by the main render window
// They are also used in the Engine class internally
const int WINDOW_WIDTH = 1280;
const int WINDOW_HEIGHT = 720;
const float VIEWPORT_WIDTH = 820;
const float VIEWPORT_HEIGHT = 620;

Renderer::Renderer(const char *windowTitle, int windowWidth, int windowHeight) {
  _window = SDL_CreateWindow("windowTitle", SDL_WINDOWPOS_UNDEFINED,
                             SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH,
                             WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
  if (_window == NULL)
    std::cout << "Failed to make window " << SDL_GetError() << std::endl;

  _renderer = SDL_CreateRenderer(
      _window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
}
void Renderer::draw(const Mesh &shape) {
  // This is a very basic renderer that draws triangles
  // It does not handle textures or lighting
  // It only draws the triangles in the mesh
  // TODO This is our point of interest

  for (const Triangle &tri : shape.tris) {

    SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 255);

    // Draw the triangle
    SDL_RenderDrawLine(_renderer, tri.p1.x, tri.p1.y, tri.p2.x, tri.p2.y);
    SDL_RenderDrawLine(_renderer, tri.p2.x, tri.p2.y, tri.p3.x, tri.p3.y);
    // SDL_RenderDrawLine(_renderer, point3.x, point3.y, point1.x, point1.y);
  }
  SDL_RenderPresent(_renderer);
}

void Renderer::drawSquare(const Triangle &shape) {
  SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
  SDL_RenderClear(_renderer);
  SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 255);

  SDL_FPoint point1{shape.p1.x, shape.p1.y};
  SDL_FPoint point2{shape.p2.x, shape.p2.y};
  SDL_FPoint point3{shape.p3.x, shape.p3.y};
  /*SDL_FPoint points[3] = {point1, point2, point3};*/

  // Line 1
  SDL_RenderDrawLine(_renderer, point1.x, point1.y, point2.x, point2.y);
  // Line 2
  SDL_RenderDrawLine(_renderer, point2.x, point2.y, point3.x, point3.y);
  // Line 3
  /*SDL_RenderDrawLine(_renderer, point3.x, point3.y, point1.x, point1.y);*/
  SDL_RenderPresent(_renderer);
}

void Renderer::clear() {
  SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
  SDL_RenderClear(_renderer);
  // SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 255);
};

void Renderer::drawTriangle(const Triangle &shape) {
  /*clear();*/
  cout << "Points of a Triangle passed in\n";
  std::cout << shape.p1 << shape.p2 << shape.p3;
  SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
  SDL_RenderClear(_renderer);
  SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 255);

  // Triangle points are defined in a clockwise manner
  // This will allow for future back-face culling
  SDL_FPoint point1 = {shape.p1.x, shape.p1.y};
  SDL_FPoint point2 = {shape.p2.x, shape.p2.y};
  SDL_FPoint point3 = {shape.p3.x, shape.p3.y};
  /*SDL_FPoint points[3] = {point1, point2, point3};*/

  // need the count for the points to be rendererd
  /*auto count = sizeof(points) / sizeof(points[0]);*/
  int result = 0; // SDL_RenderDrawLinesF(_renderer, points, count);
  if (result) /*upon failure*/ {
    cout << "Failed to render a point \n";
  } else {
    cout << "Rendered a point\n";
  }
  /*cout << "Point that chould be rendererd ";*/

  // Line 1
  SDL_RenderDrawLine(_renderer, point1.x, point1.y, point2.x, point2.y);
  // Line 2
  SDL_RenderDrawLine(_renderer, point2.x, point2.y, point3.x, point3.y);
  // Line 3
  SDL_RenderDrawLine(_renderer, point3.x, point3.y, point1.x, point1.y);
}

void Renderer::presentRender() { SDL_RenderPresent(_renderer); }

void Renderer::cleanUp() {
  SDL_DestroyRenderer(_renderer);
  SDL_DestroyWindow(_window);
  _window = nullptr;
  _renderer = nullptr;
}
void Renderer::printPoints(SDL_FPoint a, SDL_FPoint b, SDL_FPoint c) {
  std::cout << "A->(" << a.x << ',' << a.y << ')' << std::endl;
  std::cout << "B->(" << b.x << ',' << b.y << ')' << std::endl;
  std::cout << "C->(" << c.x << ',' << c.y << ')' << std::endl;
  std::cout << "==========\n";
}
