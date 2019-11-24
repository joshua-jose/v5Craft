#ifndef _FASTPIX3D_H_
#define _FASTPIX3D_H_

#include <cstdint>

typedef int8_t sbyte;
typedef int16_t int16;
typedef int32_t int32;
typedef int64_t int64;
typedef uint8_t bbyte;
typedef uint16_t uint16;
typedef uint32_t uint32;
typedef uint64_t uint64;

#define _USE_MATH_DEFINES
#include <string>
#include <cmath>
#include <ctime>
#include "main.h"
using namespace std;

const float DegToRad = float(M_PI / 180);
const int32 FixedDepthExponent = 16, FixedDepth1 = 1 << FixedDepthExponent;
const int32 SubdivExponent = 4, Subdiv1 = 1 << SubdivExponent, SubdivModulo = Subdiv1 - 1;
const float InvertedSubdiv1 = 1.f / Subdiv1;
const int32 TextureTransparencyKey = 0xff00ff;

#include "SeekOrigin.h"
#include "CullMode.h"
#include "MouseButton.h"
#include "MathUtility.h"
#include "Convert.h"
#include "Directory.h"
#include "File.h"
#include "Path.h"
#include "FPSCounter.h"
#include "Vector3f.h"
#include "Vector2f.h"
#include "Point.h"
#include "Matrix.h"
#include "Color.h"
#include "LightType.h"
#include "Light.h"
#include "FreelookManager.h"
#include "Vertex.h"
#include "ProcessedVertex.h"
#include "Triangle.h"
#include "Texture.h"
#include "RenderStates.h"
#include "Subset.h"
#include "Drawer.h"
#include "ShadowTriangle.h"
#include "Mesh.h"
#include "ShadowVolume.h"
#include "Input.h"
#include "Font.h"
#include "Graphics.h"
#include "Device.h"

#endif
