//
// Created by pc on 30.04.2021.
//

#include "canvas.h"
#include "../ppm_loader/file_exception.h"
#include <fstream>
#include <string>

exception::InvalidFileFormatException invalid_file_format;
exception::InvalidCharacterException invalid_character;

exception::BadDimensionsException bad_dimensions;
exception::InvalidPathException invalid_path;

exception::NotImplementedFileFormatException not_implemented_file_format;

Canvas::Canvas(size_t width, size_t height) {
  w_ = width;
  h_ = height;
  pixels_ = new RgbColor[w_ * h_];
  for (int i = 0; i < w_ * h_; ++i)
    pixels_[i] = RgbColor(255, 0, 0);
}

Canvas::Canvas(std::string path, size_t width, size_t height)
    : w_(width), h_(height) {

  LoadFromPpm(std::move(path));
}

Canvas::Canvas(const Canvas &other) {
  pixels_ = new RgbColor[other.w_ * other.h_];
  w_ = other.w_;
  h_ = other.h_;
  for (int i = 0; i < w_ * h_; ++i)
    pixels_[i] = other.pixels_[i];
}

Canvas::Canvas(size_t width, size_t height, RgbColor fill_color)
    : w_(width), h_(height), primary_color_(fill_color) {
  pixels_ = new RgbColor[w_ * h_];
  for (int i = 0; i < w_ * h_; ++i)
    pixels_[i] = fill_color;
}
// fixme somewhere x and y_ are mixed up

void Canvas::Fill(RgbColor fill_color) {
  for (int i = 0; i < w_ * h_; ++i)
    pixels_[i] = fill_color;
}

void Canvas::Clear() {
  for (int i = 0; i < w_ * h_; ++i)
    pixels_[i] = RgbColor();
}

void Canvas::SetPixel(Coord position, RgbColor color) {
  if (position.y_ >= h_ || position.y_ < 0 || position.x_ >= w_ ||
      position.x_ < 0)
    return;
  if (color.a_ != 255)
    return;
  pixels_[position.ToUint(w_)] = color;
}

RgbColor &Canvas::operator[](size_t position) { return pixels_[position]; }

RgbColor *Canvas::GetPixelPtr() { return pixels_; }

int Canvas::Pitch() const { return (int)w_ * 4; }

void Canvas::SetPrimaryColor(RgbColor color) { primary_color_ = color; }

RgbColor &Canvas::GetPixel(Coord position) {

  return pixels_[position.ToUint(w_)];
}

void Canvas::DrawCircle(Coord center, unsigned int radius,
                        RgbColor circle_color) {
  int x = radius;
  int y = 0;
  int err = 0;

  while (x >= y) {
    SetPixel({center.y_ + y, center.x_ + x}, circle_color);
    SetPixel({center.y_ + x, center.x_ + y}, circle_color);
    SetPixel({center.y_ + x, center.x_ - y}, circle_color);
    SetPixel({center.y_ + y, center.x_ - x}, circle_color);
    SetPixel({center.y_ - y, center.x_ - x}, circle_color);
    SetPixel({center.y_ - x, center.x_ - y}, circle_color);
    SetPixel({center.y_ - x, center.x_ + y}, circle_color);
    SetPixel({center.y_ - y, center.x_ + x}, circle_color);

    if (err <= 0) {
      ++y;
      err += 2 * y + 1;
    } else {
      --x;
      err -= 2 * x + 1;
    }
  }
}

void Canvas::DrawPoint(Coord center, unsigned int radius,
                       RgbColor point_color) {
  for (int i = 0; i < radius; i++)
    DrawCircle(center, i, point_color);
}

void Canvas::DrawPoint(Coord center, unsigned int radius) {
  for (int i = 0; i < radius; i++)
    DrawCircle(center, i, primary_color_);
}

void Canvas::DrawCircle(Coord center, unsigned int radius) {
  DrawCircle(center, radius, primary_color_);
}

const RgbColor Canvas::GetPixelCopy(Coord position) const {
  return pixels_[position.ToUint(w_)];
}

void Canvas::DrawButton(const Canvas &butt, Coord left_top_corner) {
  for (int y = 0; y < butt.h_; y++) {
    for (int x = 0; x < butt.w_; x++) {

      SetPixel({left_top_corner.y_ + y, left_top_corner.x_ + x},
               butt.GetPixelCopy({y, x}));
    }
  }
}

bool IsComment(const char &letter) { return letter == '#'; }

void IgnoreComment(std::fstream &plik) {

  std::string comment;
  std::getline(plik, comment, '\n');
}

void HandleChar(std::fstream &plik) {
  char letter;

  plik.clear(plik.goodbit);

  plik >> letter; // ponownie wczytuje znak

  if (IsComment(letter))
    IgnoreComment(plik);
  else {

    throw invalid_character;
    // napotkano nioczekiwany symbol
  }
}

int ReadNumber(std::fstream &plik) {
  int number;
  do {
    plik >> number;
    if (plik.fail())
      HandleChar(
          plik); // obiekt fstream gdy napotka nielegalny symbol wystawia blad
    // wiecej informacji : https://www.cplusplus.com/reference/ios/ios/rdstate/
    else
      return number;

  } while (!plik.eof());
  throw invalid_file_format;
  // plik nie posiada liczb albo ma ich za malo
}

unsigned char CheckColor(int color) {
  if (color < 0 || color > (int)256) {
    throw invalid_file_format;
  } else
    return (unsigned char)color;
}

void ReadHeader(std::fstream &plik) {
  char letter;
  do {

    plik >> letter;
    if (IsComment(letter))
      IgnoreComment(
          plik); // w_ przypadu gdy napotkamy '#' czyli poczatek komentarza

    else if (letter == 'P') {
      plik >> letter;
      if (letter == '3')
        return;

      else
        // napotkano nioczekiwany symbol
        throw invalid_character;
    }
  } while (!plik.eof());
  throw invalid_file_format;
  // nie znaleziono naglowka pliku
}

void Canvas::LoadFromPpm(std::string path) {

  std::fstream plik;
  plik.open(path, std::ios::in);
  int image_width, image_height;
  if (plik.good()) {

    ReadHeader(plik);

    image_width = ReadNumber(plik);

    if (image_width != w_) {
      throw bad_dimensions;
    }

    image_height = ReadNumber(plik);

    if (image_height != h_) {
      throw bad_dimensions;
    }

    int max_color = ReadNumber(plik);

    if (max_color < 0 || max_color > 255) {
      throw bad_dimensions;
    }

    size_t array_size = image_height * image_width; // tymczasowa  zmienna

    if (!pixels_)
      delete[] pixels_; // jeżeli obraz posiada już dane
    pixels_ = new RgbColor[w_ * h_];

    for (unsigned i = 0; i < array_size; i++) {

      if (plik.eof()) {
        throw bad_dimensions;
      } //   nizgodny rozmiar pliku z zadeklarowanym rozmiarem zdjecia

      unsigned char R = CheckColor(ReadNumber(plik));

      if (plik.eof()) {
        throw bad_dimensions;
      } //   nizgodny rozmiar pliku z zadeklarowanym rozmiarem zdjecia

      unsigned char G = CheckColor(ReadNumber(plik));

      if (plik.eof()) {
        throw bad_dimensions;
      } //   nizgodny rozmiar pliku z zadeklarowanym rozmiarem zdjecia

      unsigned char B = CheckColor(ReadNumber(plik));

      if (R == 0 && G == 0 && B == 0)
        pixels_[i] = {R, G, B, 0};
      else
        pixels_[i] = {R, G, B}; // dodaje pobrany kolor do tablicy
    }

  } else {
    // nie znaleziono pliku pod podanym adresem lub napodkano problem z
    // odczytaniem danych z niego
    // wiecej pod adresem: https://en.cppreference.com/w/cpp/io/basic_ios/good

    throw invalid_path;
  }
}

size_t Canvas::GetW() const { return w_; }

size_t Canvas::GetH() const { return h_; }

void Canvas::DrawLine(Coord start, Coord end, int width) {
  double a = (double)(end.y_ - start.y_) / (end.x_ - start.x_);
  if (end.x_ == start.x_) {
    a = 0;
  }

  double b = start.y_ - a * start.x_;

  double dx = a;

  double dy = (1 / a);

  // now go along the function and draw it onto a canvas

  DrawPoint(start, width);
  DrawPoint(end, width);

  int begin_x = (start.x_ < end.x_) ? start.x_ : end.x_;
  int end_x = (start.x_ > end.x_) ? start.x_ : end.x_;

  int begin_y = (start.y_ < end.y_) ? start.y_ : end.y_;
  int end_y = (start.y_ > end.y_) ? start.y_ : end.y_;

  //  for (int x = begin_x; x < end_x; x++) {
  //    DrawPoint({(int)(x * dx + b), x}, width, point_color);
  //  }

  if (a == 0) {
    for (int y = begin_y; y < end_y; y++) {
      // we
      DrawPoint({y, start.x_}, width);
    }
  } else
    for (int y = begin_y; y < end_y; y++) {
      // y = ax + b
      // (y - b) / a = x
      // dy = 1/a
      // x = (y - b) * dy

      DrawPoint({y, (int)((y - b) * dy)}, width);
    }
}

void Canvas::DrawLine(Coord start, Coord end, int width, RgbColor point_color) {
  double a = (double)(end.y_ - start.y_) / (end.x_ - start.x_);
  if (end.x_ == start.x_) {
    a = 0;
  }

  double b = start.y_ - a * start.x_;

  double dx = a;

  double dy = (1 / a);
  if (a == 0) {
    dy = 1;
  }

  // now go along the function and draw it onto a canvas

  DrawPoint(start, width, point_color);
  DrawPoint(end, width, point_color);

  int begin_x = (start.x_ < end.x_) ? start.x_ : end.x_;
  int end_x = (start.x_ > end.x_) ? start.x_ : end.x_;

  int begin_y = (start.y_ < end.y_) ? start.y_ : end.y_;
  int end_y = (start.y_ > end.y_) ? start.y_ : end.y_;

  //  for (int x = begin_x; x < end_x; x++) {
  //    DrawPoint({(int)(x * dx + b), x}, width, point_color);
  //  }

  if (a == 0) {
    for (int y = begin_y; y < end_y; y++) {
      // we
      DrawPoint({y, start.x_}, width, point_color);
    }
  } else
    for (int y = begin_y; y < end_y; y++) {
      // y = ax + b
      // (y - b) / a = x
      // dy = 1/a
      // x = (y - b) * dy

      DrawPoint({y, (int)((y - b) * dy)}, width, point_color);
    }
}
