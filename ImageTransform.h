#pragma once

#include "Image/PNG.h"
using namespace Image;

PNG grayscale(PNG image);
PNG createSpotlight(PNG image, int centerX, int centerY);
PNG illinify(PNG image);
PNG watermark(PNG firstImage, PNG secondImage);
