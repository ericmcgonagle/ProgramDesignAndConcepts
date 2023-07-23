#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <cmath>
#include "functions.h"

using namespace std;

Pixel **createImage(int width, int height)
{
  cout << "Start createImage... " << endl;

  // Create a one dimensional array on the heap of pointers to Pixels
  //    that has width elements (i.e. the number of columns)
  Pixel **image = new Pixel *[width];

  bool fail = false;

  for (int i = 0; i < width; ++i)
  { // loop through each column
    // assign that column to a one dimensional array on the heap of Pixels
    //  that has height elements (i.e. the number of rows)
    image[i] = new Pixel[height];

    if (image[i] == nullptr)
    { // failed to allocate
      fail = true;
    }
  }

  if (fail)
  { // if any allocation fails, clean up and avoid memory leak
    // deallocate any arrays created in for loop
    for (int i = 0; i < width; ++i)
    {
      delete[] image[i]; // deleting nullptr is not a problem
    }
    delete[] image; // delete array of pointers
    return nullptr;
  }

  // initialize cells
  // cout << "Initializing cells..." << endl;
  for (int row = 0; row < height; ++row)
  {
    for (int col = 0; col < width; ++col)
    {
      // cout << "(" << col << ", " << row << ")" << endl;
      image[col][row] = {0, 0, 0};
    }
  }
  cout << "End createImage... " << endl;
  return image;
}

void deleteImage(Pixel **image, int width)
{
  cout << "Start deleteImage..." << endl;
  // avoid memory leak by deleting the array
  for (int i = 0; i < width; ++i)
  {
    delete[] image[i]; // delete each individual array placed on the heap
  }
  delete[] image;
  image = nullptr;
}

// implement for part 1

int *createSeam(int length)
{

  int *newSeam = new int[length];

  return newSeam;

  // return nullptr;
}

void deleteSeam(int *seam)
{
  delete[] seam;
}

bool loadImage(string filename, Pixel **image, int width, int height)
{
  ifstream inputFile;
  inputFile.open(filename);
  // ifstream inFS;
  int checkWidth;
  int checkHeight;
  int maxColor;
  int readValue;
  int count;
  string fileType;

  /*
  string updatedWidth;
  string updatedHeight;
  int posX;
  int currDigit;
  */
  // check if opening file fails
  if (!inputFile.is_open())
  {
    cout << "Error: failed to open input file - " << filename << endl;
    return false;
  }
  // checks the file type
  inputFile >> fileType;
  if (fileType != "P3")
  {
    cout << "Error: type is " << fileType << " instead of P3" << endl;
    return false;
  }

  // check if the input width and height corresponds to the width and height of the file
  inputFile >> checkWidth;
  if (inputFile.fail())
  {
    cout << "Error: read non-integer value" << endl;
    return false;
  }
  else if (checkWidth != width)
  {
    cout << "Error: input width (" << width << ") does not match value in file (" << checkWidth << ")" << endl;
    return false;
  }
  inputFile >> checkHeight;
  if (inputFile.fail())
  {
    cout << "Error: read non-integer value" << endl;
  }
  else if (checkHeight != height)
  {
    cout << "Error: input height (" << height << ") does not match value in file (" << checkHeight << ")" << endl;
    return false;
  }

  inputFile >> maxColor;
  if (inputFile.fail())
  {
    cout << "Error: read non-integer value" << endl;
    return false;
  }
  // check if input is a valid integer
  count = 0;
  for (int row = 0; row < height; row++)
  {
    for (int col = 0; col < width; col++)
    {
      inputFile >> readValue;
      if (inputFile.eof())
      {
        cout << "Error: not enough color values" << endl;
        return false;
      }
      if (inputFile.fail())
      {
        cout << "Error: read non-integer value: " << endl;
        return false;
      }
      if ((readValue < 0) || (readValue > maxColor))
      {
        cout << "Error: invalid color value " << readValue << endl;
        return false;
      }

      Pixel tempPixel;
      if (count == 0)
      {
        tempPixel.r = readValue;
        count += 1;
        col -= 1;
      }
      else if (count == 1)
      {
        tempPixel.g = readValue;
        count += 1;
        col -= 1;
      }
      else if (count == 2)
      {
        tempPixel.b = readValue;
        image[col][row] = tempPixel;
        count = 0;
      }
    }
  }

  if (!inputFile.eof())
  {
    if (inputFile >> readValue)
    {
      cout << "Error: too many color values" << endl;
      return false;
    }
  }

  // checking color value

  // reading in integers and checking if int or not
  // also checking if width and height input matches the corresponding width and height for the file

  /*
   posX = filename.find('X');
   index = 1;


   while (true)
   {
     if (isdigit(filename.at(posX - index)))
       index += 1;
     updatedWidth.insert(0, filename.substr(posX - index, posX));
     break;
   }
   index = 1;
   while (true)
   {
     if (isdigit(filename.at(posX + 1)))
       index += 1;
     updatedHeight.insert(0, filename.substr(posX + 1, posX + index + 1));
     break;
   }
   if (filename.find(width) == string::npos)
   {
     cout << "Error: input width (" << width << ") does not match the value in file" << updatedWidth << endl;
   }
   if (filename.find(height) == string::npos)
   {
     cout << "Error: input width(" << height << ") does not match the value in file" << updatedHeight << endl;
   }
   */

  inputFile.close();
  return true;
}

bool outputImage(string filename, const Pixel *const *image, int width, int height)
{
  ofstream outFS;
  outFS.open(filename);
  if (!outFS.is_open())
  {
    cout << "Error: failed to open output file  - " << filename << endl;
    return false;
  }
  outFS << "P3" << endl;
  outFS << width << " " << height << endl;
  outFS << "255" << endl;
  // outFS << image << " ";
  for (int row = 0; row < height; row++)
  {
    for (int col = 0; col < width; col++)
    {
      outFS << &image[col][row] << endl;
    }
  }

  outFS.close();
  return true;
}

int energy(const Pixel *const *image, int x, int y, int width, int height)
{
  // declare the necessary variables
  int deltaRX;
  int deltaGX;
  int deltaBX;
  int deltaX;
  int deltaRY;
  int deltaGY;
  int deltaBY;
  int deltaY;
  int energy;
  /*
  order pixels
  if (border pixels) {
    calculate the energy for the border pixels
  }
  */

  // corner pieces
  // top left corner
  if ((x == 0) && (y == 0))
  {
    deltaRX = image[width - 1][y].r - image[x + 1][y].r;
    deltaGX = image[width - 1][y].g - image[x + 1][y].g;
    deltaBX = image[width - 1][y].b - image[x + 1][y].b;
    deltaX = (deltaRX * deltaRX) + (deltaGX * deltaGX) + (deltaBX * deltaBX);

    deltaRY = image[x][height - 1].r - image[x][y + 1].r;
    deltaGY = image[x][height - 1].g - image[x][y + 1].g;
    deltaBY = image[x][height - 1].b - image[x][y + 1].b;
    deltaY = (deltaRY * deltaRY) + (deltaGY * deltaGY) + (deltaBY * deltaBY);

    energy = deltaX + deltaY;
  }

  // bottom left corner
  else if ((x == 0) && (y == height - 1))
  {
    deltaRX = image[width - 1][y].r - image[x + 1][y].r;
    deltaGX = image[width - 1][y].g - image[x + 1][y].g;
    deltaBX = image[width - 1][y].b - image[x + 1][y].b;
    deltaX = (deltaRX * deltaRX) + (deltaGX * deltaGX) + (deltaBX * deltaBX);

    deltaRY = image[x][y - 1].r - image[x][0].r;
    deltaGY = image[x][y - 1].g - image[x][0].g;
    deltaBY = image[x][y - 1].b - image[x][0].b;
    deltaY = (deltaRY * deltaRY) + (deltaGY * deltaGY) + (deltaBY * deltaBY);

    energy = deltaX + deltaY;
  }

  // top right corner
  else if ((x == width - 1) && (y == 0))
  {
    deltaRX = image[0][y].r - image[x - 1][y].r;
    deltaGX = image[0][y].g - image[x - 1][y].g;
    deltaBX = image[0][y].b - image[x - 1][y].b;
    deltaX = (deltaRX * deltaRX) + (deltaGX * deltaGX) + (deltaBX * deltaBX);

    deltaRY = image[x][height - 1].r - image[x][y + 1].r;
    deltaGY = image[x][height - 1].g - image[x][y + 1].g;
    deltaBY = image[x][height - 1].b - image[x][y + 1].b;
    deltaY = (deltaRY * deltaRY) + (deltaGY * deltaGY) + (deltaBY * deltaBY);

    energy = deltaX + deltaY;
  }

  // bottom right corner
  else if ((x == width - 1) && (y == height - 1))
  {
    deltaRX = image[0][y].r - image[x - 1][y].r;
    deltaGX = image[0][y].g - image[x - 1][y].g;
    deltaBX = image[0][y].b - image[x - 1][y].b;
    deltaX = (deltaRX * deltaRX) + (deltaGX * deltaGX) + (deltaBX * deltaBX);

    deltaRY = image[x][y - 1].r - image[x][0].r;
    deltaGY = image[x][y - 1].g - image[x][0].g;
    deltaBY = image[x][y - 1].b - image[x][0].b;
    deltaY = (deltaRY * deltaRY) + (deltaGY * deltaGY) + (deltaBY * deltaBY);

    energy = deltaX + deltaY;
  }

  // left border
  else if (x == 0)
  {
    deltaRX = image[width - 1][y].r - image[x + 1][y].r;
    deltaGX = image[width - 1][y].g - image[x + 1][y].g;
    deltaBX = image[width - 1][y].b - image[x + 1][y].b;
    deltaX = (deltaRX * deltaRX) + (deltaGX * deltaGX) + (deltaBX * deltaBX);

    deltaRY = image[x][y - 1].r - image[x][y + 1].r;
    deltaGY = image[x][y - 1].g - image[x][y + 1].g;
    deltaBY = image[x][y - 1].b - image[x][y + 1].b;
    deltaY = (deltaRY * deltaRY) + (deltaGY * deltaGY) + (deltaBY * deltaBY);

    energy = deltaX + deltaY;
  }

  // right border
  else if (x == width - 1)
  {
    deltaRX = image[0][y].r - image[x - 1][y].r;
    deltaGX = image[0][y].g - image[x - 1][y].g;
    deltaBX = image[0][y].b - image[x - 1][y].b;
    deltaX = (deltaRX * deltaRX) + (deltaGX * deltaGX) + (deltaBX * deltaBX);

    deltaRY = image[x][y - 1].r - image[x][y + 1].r;
    deltaGY = image[x][y - 1].g - image[x][y + 1].g;
    deltaBY = image[x][y - 1].b - image[x][y + 1].b;
    deltaY = (deltaRY * deltaRY) + (deltaGY * deltaGY) + (deltaBY * deltaBY);

    energy = deltaX + deltaY;
  }

  // top border
  else if (y == 0)
  {
    deltaRX = image[x - 1][y].r - image[x + 1][y].r;
    deltaGX = image[x - 1][y].g - image[x + 1][y].g;
    deltaBX = image[x - 1][y].b - image[x + 1][y].b;
    deltaX = (deltaRX * deltaRX) + (deltaGX * deltaGX) + (deltaBX * deltaBX);

    deltaRY = image[x][height - 1].r - image[x][y + 1].r;
    deltaGY = image[x][height - 1].g - image[x][y + 1].g;
    deltaBY = image[x][height - 1].b - image[x][y + 1].b;
    deltaY = (deltaRY * deltaRY) + (deltaGY * deltaGY) + (deltaBY * deltaBY);

    energy = deltaX + deltaY;
  }

  // bottom border
  else if (y == height - 1)
  {
    deltaRX = image[x - 1][y].r - image[x + 1][y].r;
    deltaGX = image[x - 1][y].g - image[x + 1][y].g;
    deltaBX = image[x - 1][y].b - image[x + 1][y].b;
    deltaX = (deltaRX * deltaRX) + (deltaGX * deltaGX) + (deltaBX * deltaBX);

    deltaRY = image[x][y - 1].r - image[x][0].r;
    deltaGY = image[x][y - 1].g - image[x][0].g;
    deltaBY = image[x][y - 1].b - image[x][0].b;
    deltaY = (deltaRY * deltaRY) + (deltaGY * deltaGY) + (deltaBY * deltaBY);

    energy = deltaX + deltaY;
  }
  // interior pixels
  // interior x pixels
  else
  {
    deltaRX = image[x - 1][y].r - image[x + 1][y].r;
    deltaGX = image[x - 1][y].g - image[x + 1][y].g;
    deltaBX = image[x - 1][y].b - image[x + 1][y].b;
    deltaX = (deltaRX * deltaRX) + (deltaGX * deltaGX) + (deltaBX * deltaBX);

    // interior y pixels
    deltaRY = image[x][y - 1].r - image[x][y + 1].r;
    deltaGY = image[x][y - 1].g - image[x][y + 1].g;
    deltaBY = image[x][y - 1].b - image[x][y + 1].b;
    deltaY = (deltaRY * deltaRY) + (deltaGY * deltaGY) + (deltaBY * deltaBY);

    energy = deltaX + deltaY;
  }

  return energy;
}

// implement for part 2

// uncomment for part 2

int loadVerticalSeam(Pixel **image, int start_col, int width, int height, int *seam)
{
  int totalEnergy;
  int index;
  int curr_col;
  int downRightEnergy;
  int downMiddleEnergy;
  int downLeftEnergy;

  seam[0] = start_col;
  totalEnergy = energy(image, start_col, 0, width, height);
  curr_col = start_col;

  // right border case

  // left border case

  // normal case (three possibilities: down-right, down-middle, down-left)
  for (index = 1; index < height; index++)
  {
    if (width == 1)
    {
      downMiddleEnergy = energy(image, curr_col, index, width, height);
      totalEnergy += downMiddleEnergy;
    }
    else
    {
      if (curr_col == 0)
      {
        downLeftEnergy = energy(image, curr_col + 1, index, width, height);
        downMiddleEnergy = energy(image, curr_col, index, width, height);
        if (downLeftEnergy < downMiddleEnergy)
        {
          totalEnergy += downLeftEnergy;
          curr_col += 1;
        }
        else
        {
          totalEnergy += downMiddleEnergy;
        }
      }
      else if (curr_col == width - 1)
      {
        downMiddleEnergy = energy(image, curr_col, index, width, height);
        downRightEnergy = energy(image, curr_col - 1, index, width, height);
        if (downRightEnergy < downMiddleEnergy)
        {
          totalEnergy += downRightEnergy;
          curr_col -= 1;
        }
        else
        {
          totalEnergy += downMiddleEnergy;
        }
      }
      else
      {
        downLeftEnergy = energy(image, curr_col + 1, index, width, height);
        downMiddleEnergy = energy(image, curr_col, index, width, height);
        downRightEnergy = energy(image, curr_col - 1, index, width, height);
        if ((downRightEnergy < downMiddleEnergy) && (downRightEnergy < downLeftEnergy))
        {
          totalEnergy += downRightEnergy;
          curr_col -= 1;
        }
        else if ((downLeftEnergy < downMiddleEnergy) && (downLeftEnergy < downRightEnergy))
        {
          totalEnergy += downLeftEnergy;
          curr_col += 1;
        }
        else if ((downMiddleEnergy < downLeftEnergy) && (downMiddleEnergy < downRightEnergy))
        {
          totalEnergy += downMiddleEnergy;
        }
        else
        {
          if (downMiddleEnergy == downLeftEnergy)
          {
            totalEnergy += downMiddleEnergy;
          }
          else if (downMiddleEnergy == downRightEnergy)
          {
            totalEnergy += downMiddleEnergy;
          }
          else
          {
            totalEnergy += downLeftEnergy;
            curr_col += 1;
          }
        }
      }
    }
    seam[index] = curr_col;
  }

  return totalEnergy;
}
/*
int loadHorizontalSeam(Pixel **image, int start_row, int width, int height, int *seam)
{
  return 0;
}
*/
int *findMinVerticalSeam(Pixel **image, int width, int height)
{
  int tempEnergy;
  int *tempSeam = new int[height];
  int *lowestSeam = new int[height];
  int minEnergy = loadVerticalSeam(image, 0, width, height, tempSeam);
  delete[] tempSeam;
  for (int i = 1; i < width; i++)
  {
    int *tempSeam = new int[height];
    tempEnergy = loadVerticalSeam(image, i, width, height, tempSeam);
    if (tempEnergy < minEnergy)
    {
      minEnergy = tempEnergy;
      lowestSeam = tempSeam;
    }
    delete[] tempSeam;
  }

  return lowestSeam;
}
/*
int *findMinHorizontalSeam(Pixel **image, int width, int height)
{
  return nullptr;
}
*/
void removeVerticalSeam(Pixel **image, int width, int height, int *verticalSeam)
{
  Pixel holder;
  for (int i = 0; i < height; i++)
  {
    holder = image[verticalSeam[i]][i];
    for (int j = verticalSeam[i]; j < width - 1; j++)
    {
      image[j][i] = image[j + 1][i];
    }
    image[width - 1][i] = holder;
  }
}

/*
void removeHorizontalSeam(Pixel **image, int width, int height, int *horizontalSeam)
{
}
*/
