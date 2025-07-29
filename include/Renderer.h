#ifndef RENDERER_H
#define RENDERER_H
// This renderer is very bare bones and does
// only the bare minimum needed to render vectors and matrices on a plot system
#include "SDL2/SDL_render.h"
#include "SDL2/SDL_video.h"
#include "v3Util.h"
#include <cxxabi.h>
extern const int WINDOW_WIDTH, WINDOW_HEIGHT;
extern const float VIEWPORT_WIDTH, VIEWPORT_HEIGHT;

class Renderer {

public:
  Renderer(const char *windowTitle, int windowWidth, int windowHeight);
  Renderer(const Renderer &&) = delete; // wtf are you doing
  Renderer(const Renderer &) = delete;  // no copying
  ~Renderer() = default;
  void drawSquare(const Triangle &shape);
  void drawSquares(const Mesh &shape);
  void render(const Mesh &shape);
  void clear(); // call SDL_Renderer clear
  void display();
  void drawTriangle(const Triangle &shape);
  void cleanUp();
  // i'll implement this in the future
  SDL_Renderer *getRender() const { return _renderer; }
  void setRender(SDL_Renderer *r) { _renderer = r; }
  void presentRender();
  void printPoints(SDL_FPoint a, SDL_FPoint b, SDL_FPoint c);
  float getFrameDelay() const { return _frameDelay; }
  void draw(const Mesh &m);

private:
  float _FOV = 10.0f;
  float _deltaTime = 0.0f;
  inline static const float _FPS = 60.f;
  float _frameDelay = 1000.0f / _FPS;
  float _rotation = 0.0f;
  SDL_Window *_window;
  SDL_Renderer *_renderer;
  Mesh _mesh; // a collection of triangles that make up a geometric shape
              //
  // template <typename T> void printType() {
  //   int stat{0};
  //   char *demangled =
  //       abi::__cxa_demangle(typeid(T).name(), nullptr, nullptr, &stat);
  //   if (stat == 0) {
  //     std::cout << "Type: " << demangled << std::endl;
  //     free(demangled);
  //   } else {
  //     std::cout << "Type: " << typeid(T).name() << std::endl;
  //   }
  //  };
};
#endif
