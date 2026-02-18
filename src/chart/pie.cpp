#include "pie.hpp"
#include <cmath>
#include <algorithm>
#include <vector>
#include <sstream>
#include <iomanip>

// ##########################################
//             PieSlice class
// ##########################################
PieSlice::PieSlice(const std::string& lbl, float val, u8 r, u8 g, u8 b, u8 a)
  : label_(lbl), value_(val) {
  color_.r = r;
  color_.g = g;
  color_.b = b;
  color_.a = a;
}

// ##########################################
//             Texture class
// ##########################################
bool Texture::loadFromText
(SDL_Renderer* renderer, TTF_Font* font, const std::string& text, SDL_Color fg) {
  free();
  
  SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), fg);
  if (!surface) {
    std::cerr << "couldnt create text surface: " << TTF_GetError() << std::endl;
    return false;
  }

  SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
  if (!texture) {
    std::cerr << "Unable to create texture from surface: " << SDL_GetError() << std::endl;
    SDL_FreeSurface(surface);
    return false;
  }

  width_ = surface->w;
  height_ = surface->h;

  SDL_FreeSurface(surface);
  return true;
}

// copy portion of texture to current renderer
void Texture::render(SDL_Renderer* renderer, int x, int y) {
  if (texture_) {
    SDL_Rect renderQuad = { x - width_/2, y - height_/2, width_, height_ };
    if (!SDL_RenderCopy(renderer, texture_, nullptr, &renderQuad)) {
      std::cerr << "unable to copy texture to renderer" << std::endl;
    }
  }
}

void Texture::free() {
  if (texture_) {
    SDL_DestroyTexture(texture_);
    texture_ = nullptr;
    width_   = 0;
    height_  = 0;
  }
}

void PieChart::drawFilledTriangle_
(SDL_Renderer* renderer, int x1, int y1, int x2, int y2, int x3, int y3,
 SDL_Color color) {
  SDL_Vertex vertices[3] = {
    { {(float)x1, (float)y1}, color, {0, 0} },
    { {(float)x2, (float)y2}, color, {0, 0} },
    { {(float)x3, (float)y3}, color, {0, 0} }
  };
  SDL_RenderGeometry(renderer, nullptr, vertices, 3, nullptr, 0);
}

void PieChart::drawSlice_
(SDL_Renderer* renderer, float startAngle, float endAngle, SDL_Color color) {
  int numSegments = 60;
  float angleStep = (endAngle - startAngle) / numSegments;
    
  for (int i = 0; i < numSegments; i++) {
    float angle1 = startAngle + i * angleStep;
    float angle2 = startAngle + (i + 1) * angleStep;
        
    int x1 = centerX_ + radius_ * cos(angle1);
    int y1 = centerY_ + radius_ * sin(angle1);
    int x2 = centerX_ + radius_ * cos(angle2);
    int y2 = centerY_ + radius_ * sin(angle2);
        
    drawFilledTriangle_(renderer, centerX_, centerY_, x1, y1, x2, y2, color);
  }
}

void PieChart::draw(SDL_Renderer* renderer) {
  if (slices_.empty()) return;

  float total = 0;
  for (const auto& slice: slices_) {
    total += slice.getValue();
  }

  if (total == 0) return;

  labelTextures_.clear();	// clear prev label
  float currentAngle = -PI/2.0f;

  for(const auto& slice: slices_) {
    float sliceAngle = (slice.getValue() / total) * 2 * PI;
    float endAngle = currentAngle + sliceAngle;

    // draw filled slice
    drawSlice_ (renderer, currentAngle, endAngle, slice.getColor());
    
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // outline

    // draw arc
    int x1 = centerX_ + radius_ * cos(currentAngle);
    int y1 = centerY_ + radius_ * sin(currentAngle);
    int x2 = centerX_ + radius_ * cos(endAngle);
    int y2 = centerY_ + radius_ * sin(endAngle);

    // draw radius line
    SDL_RenderDrawLine(renderer, centerX_, centerY_, x1, y1);
    SDL_RenderDrawLine(renderer, centerX_, centerY_, x2, y2);

    // label
    if (font_) {
      float labelAngle = currentAngle + sliceAngle / 2;
      int labelX = centerX_ + (radius_ * 0.7) * cos(labelAngle);
      int labelY = centerY_ + (radius_ * 0.7) * sin(labelAngle);

      std::ostringstream labelStream;
      labelStream << slice.getLabel() << " " 
		  << std::fixed << std::setprecision(1) 
		  << (slice.getValue() / total * 100) << "%";

      Texture labelTexture;
      SDL_Color textColor = {0, 0, 0, 255}; // black text

      if (labelTexture.loadFromText(renderer, font_, labelStream.str(), textColor)) {
	labelTexture.render(renderer, labelX, labelY);
	labelTextures_.push_back(std::move(labelTexture));
      }
    }

    currentAngle = endAngle;
  }

  // draw center point
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderDrawPoint(renderer, centerX_, centerY_);

  for (int i = 0; i < 360; i++) {
    float angle = i * PI / 180;
    int x = centerX_ + radius_ * cos(angle);
    int y = centerY_ + radius_ * sin(angle);
    SDL_RenderDrawPoint(renderer, x, y);
  }
}
