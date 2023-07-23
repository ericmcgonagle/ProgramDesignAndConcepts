#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <cmath>
#include "functions.h"

using namespace std;

int main()
{
  string filename;
  int width = 0;
  int height = 0;
  int targetWidth = 0;
  int targetHeight = 0;
  // string checkWidth;
  // string checkHeight;

  // Add code to validate input (Do in part 1)
  cout << "Input filename: ";
  cin >> filename;
  cout << "Input width and height: ";
  cin >> width;

  if (cin.fail())
  {
    cout << "Error: width is a non-integer value" << endl;
    exit(0);
  }
  else if (width <= 0)
  {
    cout << "Error: Width must be greater than 0. You entered " << width << endl;
    exit(0);
  }
  cin >> height;
  if (cin.fail())
  {
    cout << "Error: height is a non-integer value" << endl;
    exit(0);
  }
  else if (height <= 0)
  {
    cout << "Error: Height must be greater than 0. You entered " << height << endl;
    exit(0);
  }
  /*
  else if (cin.fail()) {
    cout << "Error: Height is a non-integer value" << endl;
    exit(0);
  }
  */
  cout << "Input target width and target height: ";
  cin >> targetWidth;

  // check if targetWidth and targetHeight are negative values
  if (cin.fail())
  {
    cout << "Error: target width is a non-integer value" << endl;
    exit(0);
  }
  else if (targetWidth <= 0)
  {
    cout << "Error: target width must be greater than 0. You entered " << targetWidth << endl;
    exit(0);
  }
  
  cin >> targetHeight;
  if (cin.fail())
  {
    cout << "Error: target height is a non-integer value" << endl;
    exit(0);
  }
  else if (targetHeight <= 0)
  {
    cout << "Error: target height must be greater than 0. You entered " << targetHeight << endl;
    exit(0);
  }

  int originalWidth = width; // need to delete image array at end of program

  Pixel **image = createImage(width, height); // create array of size that we need
  if (image != nullptr)
  {
    if (loadImage(filename, image, width, height))
    {
      cout << "Start carving..." << endl;

      // Add code to remove seams from image (Do in part 2)
      while (width > targetWidth) {
        int* lowest = findMinVerticalSeam(image, width, height);
        removeVerticalSeam(image, width, height, lowest);
        width -= 1;
      }
      /*
      int* seam = new int[height];
      int tot_energy = loadVerticalSeam(image,1,width,height,seam);
      cout << tot_energy << endl;
      for (int i = 0; i < height; i++) {
        cout << seam[i] << endl;


      }
      */
      // set up output filename
      stringstream ss;
      ss << "carved" << width << "X" << height << "." << filename;
      outputImage(ss.str().c_str(), image, width, height);
    }

    // call last to remove the memory from the heap
    deleteImage(image, originalWidth);
  }
  // else
}