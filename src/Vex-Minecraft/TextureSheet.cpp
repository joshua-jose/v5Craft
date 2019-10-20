#include "main.h"
#include "FastPix3D/lodepng.h"
#include <exception>

TextureSheet::TextureSheet(std::string path, int itextureWidth, int itextureHeight){
  unsigned width, height;

  unsigned error = lodepng::decode(image, width, height, path,LCT_RGBA);

  pixelWidth = (int)width, pixelHeight = (int)height;
  textureWidth=itextureWidth, textureHeight=itextureHeight;
  TexturesX = (pixelWidth/textureWidth),TexturesY=(pixelHeight/textureHeight);
}

int32* TextureSheet::getTexture(int x, int y){

  if (x > TexturesX || y > TexturesY)
    throw std::invalid_argument("x or y is greater than amount of textures!");
  int32* ret = new int32[textureWidth*textureHeight*4];

  memset(ret,0,textureWidth*textureHeight*sizeof(int32));

  for (int i = 0; i < textureHeight;i++){
    //memset(ret,0b11001100,textureWidth*textureHeight*sizeof(int32));
    //fprintf(stderr,"Test: %d\n",image[17959]);
    memcpy(ret+(i*textureWidth),
    image.data()+( (pixelWidth*(i+ (y*textureHeight))) +(x*textureWidth) )*4,
    textureWidth*sizeof(int32)*4);
    //memcpy(ret+(i*textureWidth),image.data()+(13976),textureWidth*sizeof(int32));
    //memset(ret+(i*textureWidth),i*268435456,textureWidth*sizeof(int32));
  }
  return ret;
};
