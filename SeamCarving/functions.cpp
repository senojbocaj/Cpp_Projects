#include <iostream>
#include <sstream>
#include <fstream>
#include <cmath>
#include "functions.h"

using std::cout, std::endl, std::string;

void initializeImage(Pixel image[][MAX_HEIGHT]) {
  // iterate through columns
  for (unsigned int col = 0; col < MAX_WIDTH; col++) {
    // iterate through rows
    for (unsigned int row = 0; row < MAX_HEIGHT; row++) {
      // initialize pixel
      image[col][row] = {0, 0, 0};
    }
  }
}


void loadImage(string filename, Pixel image[][MAX_HEIGHT], unsigned int& width, unsigned int& height) {
  // TODO: implement (part 1)
  std::ifstream ifs(filename);

  // Checks if file is able to open.
  if (!ifs.is_open()) {
    throw std::runtime_error("Failed to open " + filename);
  }

  // Checks file type.
  string fileType;
  ifs >> fileType;

  if (fileType != "P3") {
    throw std::runtime_error("Invalid type" + fileType);
  }

  // Checks width and height.
  ifs >> width >> height;
  
  if (width <= 0 || height <= 0  || width > MAX_WIDTH || height > MAX_HEIGHT) {
    throw std::runtime_error("Invalid dimensions");
    }

  int maxColor;
  ifs >> maxColor;

  if (maxColor < 0 || maxColor > 255) {
    throw std::runtime_error("Invalid color value");
  }

  // Reads and validates all pixels.
  for (unsigned int i = 0; i < height; ++i) {
    for (unsigned int j = 0; j < width; ++j) {
     int red, green, blue;
     ifs >> red >> green >> blue;

      if (ifs.fail()) {
        throw std::runtime_error("Invalid color value");
      }

      if (red < 0 || blue < 0 || green < 0 || red >= 256 || green >= 256 || blue >= 256){
        throw std::runtime_error("Invalid color value");
      }

      image[j][i].r = red;
      image[j][i].g = green;
      image[j][i].b = blue;
    }
  }

  // Checks for any extra values in the ppm file.
  int extraVal;

  if (ifs >> extraVal) {
    throw std::runtime_error("Too many values");
  }
}

void outputImage(string filename, Pixel image[][MAX_HEIGHT], unsigned int targetWidth, unsigned int targetHeight) {
  // TODO: implement (part 1)

  // Opens an output file stream and checks if it is able to be opened.
  std::ofstream ofs(filename, std::ios::out | std::ios::binary);

  if (!ofs.is_open()) {
    throw std::runtime_error("Failed to open " + filename);
  }

  // Outputs PPM.
  ofs << "P3\n";
  ofs << targetWidth << " " << targetHeight << "\n";
  ofs << "255";

  // Outputs individual pixel values.
  for (unsigned int y = 0; y < targetHeight; ++y) {
    ofs << "\n";
    for (unsigned int x = 0; x < targetWidth; ++x) {
      ofs << image[x][y].r << " " << image[x][y].g << " " << image[x][y].b << " ";
    }
  }

  ofs.close();
}

unsigned int energy(Pixel image[][MAX_HEIGHT], unsigned int x, unsigned int y, unsigned int width, unsigned int height) {
  // TODO: implement (part 1)

   Pixel left, right, up, down;
   if (x > 0) {
       left = image[x - 1][y];
       if (x < width - 1) {
           right = image[x + 1][y];
       }
       else {
           right = image[0][y];
       }
   }
   else {
       left = image[width - 1][y];
       if (x < width - 1) {
           right = image[x + 1][y];
       }
       else {
           right = image[0][y];
       }
   }
   if (y > 0) {
       up = image[x][y - 1];
       if (y < height - 1) {
           down = image[x][y + 1];
       }
       else {
           down = image[x][0];
       }
   }
   else {
       up = image[x][height - 1];
       if (y < height - 1) {
           down = image[x][y + 1];
       }
       else {
           down = image[x][0];
       }
   }

   // Calculates x and y gradients.
   Pixel xGrad;
   Pixel yGrad;
   xGrad.r = right.r - left.r;
   xGrad.g = right.g - left.g;
   xGrad.b = right.b - left.b;

   yGrad.r = down.r - up.r;
   yGrad.g = down.g - up.g;
   yGrad.b = down.b - up.b;

   int xVal = xGrad.b * xGrad.b + xGrad.g * xGrad.g + xGrad.r * xGrad.r;
   int yVal = yGrad.b * yGrad.b + yGrad.g * yGrad.g + yGrad.r * yGrad.r;
   unsigned totEnergy = xVal + yVal;

   return totEnergy;
}

unsigned int loadVerticalSeam(Pixel image[][MAX_HEIGHT], unsigned int start_col, unsigned int width, unsigned int height, unsigned int seam[]) {
  // TODO: implement (part 2)
  unsigned int totEnergy = energy(image, start_col, 0, width, height); // Initializes totEnergy to the E of the initial pixel
  seam[0] = start_col; // Sets the first element of seam to the initial col
  unsigned int currCol = start_col; // currCol is used throughout to track the col of the current iteration
  unsigned int leftE, centerE, rightE; // Initializes energy vars as unsigned ints

  for(unsigned int i = 1; i < height; i++) { //Row iteration loop
 
    // Conditional to avoid out of bounds issue with the 2D array
    if (currCol == 0) {
      leftE = INT32_MAX;
      centerE = energy(image, currCol, i, width, height);
      rightE = energy(image, currCol+1, i, width, height);
    } else if (currCol == width-1) {
      leftE = energy(image, currCol-1, i, width, height);
      centerE = energy(image, currCol, i, width, height);
      rightE = INT32_MAX;
    } else {
      leftE = energy(image, currCol-1, i, width, height);
      centerE = energy(image, currCol, i, width, height);
      rightE = energy(image, currCol+1, i, width, height);
    }

    // No ties
    if (leftE < centerE && leftE < rightE) {
      totEnergy += leftE;
      currCol -= 1;
      seam[i] = currCol;
    } else if (rightE < centerE && rightE < leftE) {
        totEnergy += rightE;
        currCol += 1;
        seam[i] = currCol;
    } else if (centerE < leftE && centerE < rightE) {
        totEnergy += centerE;
        seam[i] = currCol;
    }

    // Ties
    if (centerE == leftE && centerE == rightE) {
      totEnergy += centerE;
      seam[i] = currCol;
    } else if (centerE == leftE && leftE < rightE) {
        totEnergy += centerE;
        seam[i] = currCol;
    } else if (centerE == rightE && rightE < leftE) {
        totEnergy += centerE;
        seam[i] = currCol;
    } else if (leftE == rightE && leftE < centerE) {
        currCol += 1;
        totEnergy += rightE;
        seam[i] = currCol;
   }
  }

  return totEnergy;
}

void findMinVerticalSeam(Pixel image[][MAX_HEIGHT], unsigned int width, unsigned int height, unsigned int seam[]) {
  // TODO: implement (part 2)
    unsigned int minEnergy = UINT32_MAX;
    unsigned int minCol = 0;

    for (unsigned int col = 0; col < width; col++) { // Iterates through first row to find lowest initial pixel energy
        unsigned int currentEnergy = loadVerticalSeam(image, col, width, height, seam);

        if (currentEnergy < minEnergy) { // Updates is currentE is smaller than minE
            minEnergy = currentEnergy;
            minCol = col;
        }
    }

    loadVerticalSeam(image, minCol, width, height, seam);
}

void removeVerticalSeam(Pixel image[][MAX_HEIGHT], unsigned int& width, unsigned int height, unsigned int verticalSeam[]) {
  // TODO: implement (part 2)
    for (unsigned int i = 0; i < height; i++) { // Iterate through each row
        for (unsigned int j = verticalSeam[i]; j < width - 1; j++) { // Shift all pixels to left, excluding the min seam pixels
            image[j][i] = image[j + 1][i];
        }
    }
    width--;
}


// BONUS /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

unsigned int loadHorizontalSeam(Pixel image[][MAX_HEIGHT], unsigned int start_row, unsigned int width, unsigned int height, unsigned int seam[]) {
    unsigned int totEnergy = energy(image, 0, start_row, width, height); // Initializes totEnergy to the E of the initial pixel
    seam[0] = start_row; // Sets the first element of seam to the initial row
    unsigned int currRow = start_row; // currRow is used throughout to track the row of the current iteration
    unsigned int upE, centerE, downE; // Initializes energy vars as unsigned ints

    for (unsigned int j = 1; j < width; j++) { // Col iteration loop

        // Conditional to avoid out of bounds issue with the 2D array
        if (currRow == 0) {
            upE = INT32_MAX;
            centerE = energy(image, j, currRow, width, height);
            downE = energy(image, j, currRow+1, width, height);
        } else if (currRow == height-1) {
            upE = energy(image, j, currRow-1, width, height);
            centerE = energy(image, j, currRow, width, height);
            downE = INT32_MAX;
        } else {
            upE = energy(image, j, currRow-1, width, height);
            centerE = energy(image, j, currRow, width, height);
            downE = energy(image, j, currRow+1, width, height);
        }

        // No ties
        if (upE < centerE && upE < downE) {
            totEnergy += upE;
            currRow -= 1;
            seam[j] = currRow;
        } else if (downE < centerE && downE < upE) {
            totEnergy += downE;
            currRow += 1;
            seam[j] = currRow;
        } else if (centerE < upE && centerE < downE) {
            totEnergy += centerE;
            seam[j] = currRow;
        }

        // Ties
        if (centerE == upE && centerE == downE) {
            totEnergy += centerE;
            seam[j] = currRow;
        } else if (centerE == upE && upE < downE) {
            totEnergy += centerE;
            seam[j] = currRow;
        } else if (centerE == downE && downE < upE) {
            totEnergy += centerE;
            seam[j] = currRow;
        } else if (upE == downE && upE < centerE) {
            currRow -= 1; // THIS IS THE ONLY RULE DIFFERENCE FROM VERTICAL SEAM TO HORIZONTAL SEAM :)))
            totEnergy += downE;
            seam[j] = currRow;
        }
    }

    return totEnergy;
}

void findMinHorizontalSeam(Pixel image[][MAX_HEIGHT], unsigned int width, unsigned int height, unsigned int seam[]) {
  // TODO: implement (part 2)
    unsigned int minEnergy = UINT32_MAX;
    unsigned int minRow = 0;

    for (unsigned int row = 0; row < height; row++) { // Iterates through first row to find lowest initial pixel energy
        unsigned int currentEnergy = loadHorizontalSeam(image, row, width, height, seam);

        if (currentEnergy < minEnergy) { // Updates is currentE is smaller than minE
            minEnergy = currentEnergy;
            minRow = row;
        }
    }

    loadHorizontalSeam(image, minRow, width, height, seam);
}

void removeHorizontalSeam(Pixel image[][MAX_HEIGHT], unsigned int width, unsigned int& height, unsigned int horizontalSeam[]) {
  // TODO: implement (part 2)
    for (unsigned int j = 0; j < width; j++) { // Iterate through each col
        for (unsigned int i = horizontalSeam[j]; i < height - 1; i++) { // Shift all pixels up, excluding the min seam pixels
            image[j][i] = image[j][i+1];
        }
    }
    height--;
}

