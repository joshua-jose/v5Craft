#ifndef _TEXTURE_SHEET_H_
#define _TEXTURE_SHEET_H_
#include "main.h"

class TextureSheet{
public:
  TextureSheet(std::string path, int TexturesX, int TexturesY);
  int pixelWidth, pixelHeight, textureWidth, textureHeight, TexturesX,TexturesY;

  std::vector<unsigned char> image;
  std::vector<std::vector<std::vector<int32>>> texSheet;

  int32* getTexture(int x, int y);
};

#endif
