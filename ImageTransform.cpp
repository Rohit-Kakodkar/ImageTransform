#include <iostream>
#include <cmath>
#include <cstdlib>

#include "Image/PNG.h"
#include "Image/HSLAPixel.h"
#include "ImageTransform.h"

/* ******************

Name: Rohit Kakodkar
Email: kakodkar.rohit@gmail.com

******************** */

using Image::PNG;
using Image::HSLAPixel;

/**
 * Returns an image that has been transformed to grayscale.
 *
 * The saturation of every pixel is set to 0, removing any color.
 *
 * @return The grayscale image.
 */
PNG grayscale(PNG image) {
  for (unsigned x = 0; x < image.width(); x++) {
    for (unsigned y = 0; y < image.height(); y++) {
      HSLAPixel & pixel = image.getPixel(x, y);

      // `pixel` is a reference to the memory stored inside of the PNG `image`,
      // which means you're changing the image directly. No need to `set`
      // the pixel since you're directly changing the memory of the image.
      pixel.s = 0;
    }
  }

  return image;
}



/**
 * Returns an image with a spotlight centered at (`centerX`, `centerY`).
 *
 * A spotlight adjusts the luminance of a pixel based on the distance the pixel
 * is away from the center by decreasing the luminance by 0.5% per 1 pixel euclidean
 * distance away from the center.
 *
 * For example, a pixel 3 pixels above and 4 pixels to the right of the center
 * is a total of `sqrt((3 * 3) + (4 * 4)) = sqrt(25) = 5` pixels away and
 * its luminance is decreased by 2.5% (0.975x its original value).  At a
 * distance over 160 pixels away, the luminance will always decreased by 80%.
 *
 * The modified PNG is then returned.
 *
 * @param image A PNG object which holds the image data to be modified.
 * @param centerX The center x coordinate of the crosshair which is to be drawn.
 * @param centerY The center y coordinate of the crosshair which is to be drawn.
 *
 * @return The image with a spotlight.
 */
PNG createSpotlight(PNG image, int centerX, int centerY) {

  for (unsigned int x = 0; x < image.width(); x++){
    for (unsigned int y = 0; y < image.height(); y++){
      HSLAPixel & pixel = image.getPixel(x, y);

      double distance = std::sqrt(std::pow(double(x - centerX), 2.0) + std::pow(double(y - centerY), 2));

      double luminance = (1.0 - 0.05*distance);

      if (luminance < 0.20){
        luminance = 0.20;
      }


      pixel.l = luminance*pixel.l;

    }
  }

  return image;

}


/**
 * Returns a image transformed to Illini colors.
 *
 * The hue of every pixel is set to the a hue value of either orange or
 * blue, based on if the pixel's hue value is closer to orange than blue.
 *
 * @param image A PNG object which holds the image data to be modified.
 *
 * @return The illinify'd image.
**/
PNG illinify(PNG image) {

  for (unsigned x = 0; x < image.width(); x++) {
    for (unsigned y = 0; y < image.height(); y++) {
      HSLAPixel & pixel = image.getPixel(x, y);

      // `pixel` is a reference to the memory stored inside of the PNG `image`,
      // which means you're changing the image directly. No need to `set`
      // the pixel since you're directly changing the memory of the image.


      if (std::abs(pixel.cdistance(pixel.h, 11.0)) < std::abs(pixel.cdistance(pixel.h, 216.0))){
        pixel.h = 11.0;
      } else {
        pixel.h = 216.0;
      }
    }
  }

  return image;
}


/**
* Returns an immge that has been watermarked by another image.
*
* The luminance of every pixel of the second image is checked, if that
* pixel's luminance is 1 (100%), then the pixel at the same location on
* the first image has its luminance increased by 0.2.
*
* @param firstImage  The first of the two PNGs, which is the base image.
* @param secondImage The second of the two PNGs, which acts as the stencil.
*
* @return The watermarked image.
*/
PNG watermark(PNG firstImage, PNG secondImage) {

  for (unsigned x = 0; x < firstImage.width(); x++) {
    for (unsigned y = 0; y < firstImage.height(); y++) {
      HSLAPixel & fpixel = firstImage.getPixel(x, y);
      HSLAPixel & spixel = secondImage.getPixel(x, y);

      if (spixel.l == 1.0){
        fpixel.l = fpixel.l + 0.2;
      }

      // `pixel` is a reference to the memory stored inside of the PNG `image`,
      // which means you're changing the image directly. No need to `set`
      // the pixel since you're directly c, hanging the memory of the image.
    }
  }


  return firstImage;
}
