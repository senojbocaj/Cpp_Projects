#include <iostream>
#include <sstream>
#include <fstream>
#include <cmath>
#include "functions.h"

using std::cout, std::endl, std::cin, std::string, std::stringstream;

int main() {
  // 2D array of pixels
  static Pixel image[MAX_WIDTH][MAX_HEIGHT];  
  
  // initialize 2D array
  initializeImage(image);

  // declare variables
  string filename;
  unsigned int width = 0;
  unsigned int height = 0;
  int targetWidth = 0;
  int targetHeight = 0;
  
  // accept filename
  cout << "Input filename: ";
  cin >> filename;

  try {
    // attempt to load image
    loadImage(filename, image, width, height);
    cout << "Detected image width: " << width << endl;
    cout << "Detected image height: " << height << endl;
  } catch (std::exception &ex) {
    cout << "Exception thrown: " << ex.what() << endl;
    return 1; // exit with error
  }

  // accept target dimensions
  cout << "Input target width: ";
  cin >> targetWidth;
  cout << "Input target height: ";
  cin >> targetHeight;

  // TODO: add code to validate input (part 1)
  // Exit program with error if there are problems with 
  //   targetWidth or targetHeight

  try {
    if (width <= 0 || width <= 0 || targetWidth <= 0 || targetHeight <= 0){
      throw std::runtime_error("Invalid target dimensions");
      return 1;
    }

    if (static_cast<int>(width) < targetWidth || static_cast<int>(height) < targetHeight){
      throw std::runtime_error("Invalid target dimensions");
      return 1;
    }
  } catch (std::exception &ex) {
    cout << ex.what() << endl;
    return 1;
  }

  cout << "Start carving..." << endl;
  
  // TODO: uncomment functions in the following while loop
  //       as you implement (part 2)
  
  while ((width - targetWidth > 0) || (height - targetHeight > 0)) {
    // find and remove a vertical seam
    if (width - targetWidth > 0) {
      unsigned int verticalSeam[MAX_HEIGHT];
      findMinVerticalSeam(image, width, height, verticalSeam); // uncomment when ready to use (part2)
      removeVerticalSeam(image, width, height, verticalSeam); // uncomment when ready to use (part 2)
    }
    // this is for the extra credit
    // find and remove a horizontal seam
    if (height - targetHeight > 0) {
      unsigned int horizontalSeam[MAX_WIDTH];
      findMinHorizontalSeam(image, width, height, horizontalSeam); // uncomment when ready to use (part 2 extra credit)
      removeHorizontalSeam(image, width, height, horizontalSeam); // uncomment when ready to use (part 2 extra credit)
    }
  }
  
  try {
    // attempt to output image
    stringstream ss;
    ss << "carved" << targetWidth << "X" << targetHeight << ".ppm";
    outputImage(ss.str().c_str(), image, targetWidth, targetHeight);
  } catch (std::exception &ex) {
    cout << "Exception thrown: " << ex.what() << endl;
    return 1; // exit with an error
  }

  cout << "Image output" << endl;

  return 0; // exit without errors
}