#pragma once

#include <SDL2/SDL.h>		// https://wiki.libsdl.org/SDL2/CategoryAPI
#include <SDL2/SDL_ttf.h>	// https://wiki.libsdl.org/SDL2_ttf/CategoryAPI
#include <string>
#include <iostream>
#include <vector>

// ##################################################################
//                           Data Type
// ##################################################################
using u8 = Uint8;

// ##################################################################
//                         Global data member
// ##################################################################
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const double PI = 3.14159265358979323846;

/*
 *@class: PieSlice
 *@see:
*/
class PieSlice {
private:
  std::string label_;
  float value_;
  SDL_Color color_;

public:
  // #################################
  //     Constructor & Destructor 
  // #################################
  PieSlice(const std::string& lbl, float val, u8 r, u8 g, u8 b, u8 a = 255);
  
  // #################################
  //            Methods
  // #################################
  float getValue() const { return value_; }
  SDL_Color getColor() const { return color_; }
  std::string getLabel() const { return label_; }
};

/*
 *@class: Texture
 *@see:
*/
class Texture {
private:
  SDL_Texture* texture_;
  int width_, height_;
  
public:
  // #################################
  //     Constructor & Destructor 
  // #################################
  Texture() : texture_(nullptr), width_(0), height_(0) {}
  ~Texture() { free(); }
  
  // #################################
  //            Methods
  // #################################
  bool loadFromText(SDL_Renderer* renderer, TTF_Font* font, const std::string& text, SDL_Color fg);
  void render(SDL_Renderer* renderer, int x, int y);
  void free();

  int getWidth() const { return width_; }
  int getHeight() const { return height_; };
};

/*
 *@class: PieChart
 *@see:
*/
class PieChart {
private:
  int centerX_, centerY_, radius_;
  std::vector<PieSlice> slices_;
  std::vector<Texture> labelTextures_;
  TTF_Font* font_;

  void drawFilledTriangle_ (SDL_Renderer* renderer,
			    int x1, int y1, int x2, int y2, int x3, int y3,
			    SDL_Color color);
  void drawSlice_ (SDL_Renderer* renderer,
		  float startAngle, float endAngle, SDL_Color color);
public:
  // #################################
  //     Constructor & Destructor 
  // #################################
  PieChart(int x, int y, int r, TTF_Font* f)
    : centerX_(x), centerY_(y), radius_(r), font_(f)
  {}
    
  ~PieChart() { labelTextures_.clear(); }

  // #################################
  //            Methods
  // #################################
  void addSlice(const PieSlice& slice) { slices_.push_back(slice); }
  void draw(SDL_Renderer* renderer);
};
