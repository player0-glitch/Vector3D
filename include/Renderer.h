#ifndef RENDERER_H
#define RENDERER_H
// This renderer is very bare bones and does
// only the bare minimum needed to render vectors and matrices on a plot system
#include "SDL2/SDL_render.h"
#include "SDL2/SDL_video.h"
#include "v3Util.h"

extern const int WINDOW_WIDTH, WINDOW_HEIGHT;
extern const float VIEWPORT_WIDTH, VIEWPORT_HEIGHT;

class Renderer {

public:
  Renderer(const char *windowTitle, int windowWidth, int windowHeight);
  Renderer(const Renderer &&) = delete; // wtf are you doing
  ~Renderer() = default;
  void drawSquare(const Triangle &shape);
  void drawSquares(const Mesh &shape);
  void render(const Mesh &shape);
  /*void render(SDL_Texture *texture);*/
  void clear(); // call SDL_Renderer clear
  void display();
  void drawTriangle(const Triangle &shape);
  void cleanUp();
  // i'll implement this in the future
  SDL_Renderer *getRender() const { return _renderer; }
  void printPoints(SDL_FPoint a, SDL_FPoint b, SDL_FPoint c);
  float getFrameDelay() const { return _frameDelay; }

private:
  float _FOV = 10.0f;
  float _deltaTime = 0.0f;
  inline static const float _FPS = 60.f;
  float _frameDelay = 1000.0f / _FPS;
  float _rotation = 0.0f;
  SDL_Window *_window;
  SDL_Renderer *_renderer;
  Mesh _mesh; // a collection of triangles that make up a geometric shape
};
#endif
