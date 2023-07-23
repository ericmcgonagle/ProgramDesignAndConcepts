// TODO: Implement this source file
#include <iostream>
#include <fstream>
#include <tuple>
#include <limits>
#include <stdexcept>
#include "MyString.h"
#include "Rover.h"

using std::cout;
using std::endl;
using std::ifstream;
using std::istream;
// default constructor will have nothing but null terminating character
MyString::MyString() : nString(new char[1]{'\0'}), sizeString(0), cap(1)
{
}

// copy constructor copies all of the values in the cstring passed by reference into the new "nString"
MyString::MyString(const MyString &other) : nString(new char[other.cap]), sizeString(other.sizeString), cap(other.cap)
{

    for (unsigned int i = 0; i < cap; ++i)
    {
        this->nString[i] = other.nString[i];
    }

    nString[sizeString] = '\0';
}

// c-string constructor
MyString::MyString(const char *c) : nString(nullptr), sizeString(0), cap(0)
{
    // checks to see if the c string is null before copying all the data
    // create a new
    if (c == nullptr)
    {
        this->nString = new char[1];
        nString[0] = '\0';

        // this->cap = 1;
        // this->sizeString = 1;
    }

    // loop until null terminating character is reached and count how many characters are in the c string to then
    // use to copy the given amount of times
    else
    {
        unsigned int length = 0;
        while (c[length] != '\0')
        {
            length += 1;
        }
        this->cap = length + 1;
        this->sizeString = length;
        this->nString = nullptr;
        this->nString = new char[cap];
        for (unsigned int i = 0; i < cap; ++i)
        {
            this->nString[i] = c[i];
        }
        nString[sizeString] = '\0';
    }
}

// MyString::MyString(const MyString &other)
// {
//     // iterate through "other" until reach '\0' and add 1 to "i" each time to
//     // get the number of characters in the c string
//     unsigned int i = 0;
//     while (other.nString[i] != '\0')
//     {
//         i += 1;
//     }

//     cap = i;
//     sizeString = i - 1;

//     nString = new MyString[cap];
//     nString
// }

// deconstructor for MyString
MyString::~MyString()
{

        delete[] nString;
        sizeString = 0; // free up space that nString was originally taking up
        cap = 0;        // set the capapcity and size of the string to 0 and set nString equal to nullptr
        nString = nullptr;
}

// resize the string
// if the value passed in to resize to is less than the current capacity, remove any character after the nth index (for
// all values after the nth index, set the character equal to \0)
void MyString::resize(size_t n)
{
    if (n < sizeString)
    {
        // unsigned int length = n - 1;
        // while (length < sizeString)
        // {
        //     nString[length] = '\0';
        //     length += 1;
        // }
        for (unsigned int i = n; i < sizeString; ++i)
        {
            nString[i] = '\0';
        }
        sizeString = n;
    }

    else if (n > sizeString)
    {
        cap = n +1;

        char *resizeStringString = new char[cap];
        for (unsigned int i = 0; i < sizeString; ++i)
        {
            resizeStringString[i] = nString[i];
        }
        resizeStringString[sizeString] = '\0';
        delete[] nString;       // free up the space that was originally taken up by nString and assign nString to nullptr and then point to
        nString = nullptr;      // resized array
        nString = resizeStringString;
    }
}

// return the capacity of a MyString object
size_t MyString::capacity() const
{
    return cap;
}

// both size and length return the same value which is the current size or number of characters that are currently being used by
// a MyString object
size_t MyString::size() const
{
    return sizeString;
}

size_t MyString::length() const
{
    return sizeString;
}

const char *MyString::data() const
{
    return nString;
}

bool MyString::empty() const
{
    if (sizeString == 0)
    {
        return true;
    }
    else
        return false;
}

const char &MyString::front() const
{
    return this->nString[0];
}

const char &MyString::at(size_t pos) const
{
    if (pos > sizeString)
    {
        throw std::out_of_range("Not valid position in string");
    }
    else
        return this->nString[pos];
}

void MyString::clear()
{
    for (unsigned int i = 0; i < sizeString; ++i)
    {
        nString[i] = '\0';
    }
    // nString = nullptr;
    sizeString = 0;
    // cap = 0;
}

std::ostream &operator<<(std::ostream &os, const MyString &other)
{
    os << other.nString;
    return os;
}

// copy assignment operator
// assign new capacity and size values from the c string passed in
MyString &MyString::operator=(const MyString &other)
{
    this->cap = other.cap;
    this->sizeString = other.sizeString;
    delete[] nString;

    nString = new char[cap];
    for (unsigned int i = 0; i < cap; ++i)
    {
        // if (i == sizeString)
        // {
        //     nString[i] = '\0';
        // }
        // else
        this->nString[i] = other.nString[i];
    }

    nString[sizeString] = '\0';
    return *this;
}

MyString &MyString::operator+=(const MyString &other)
{
    char *holder;
    holder = new char[other.sizeString + (this->sizeString + 1)];
    for (unsigned int i = 0; i < this->sizeString; ++i)
    {
        holder[i] = this->nString[i];
    }

    for (unsigned int i = sizeString; i < (sizeString + other.sizeString); ++i)
    {
        holder[i] = other.nString[i - sizeString];
    }
    holder[sizeString + other.sizeString] = '\0';
    sizeString = this->sizeString + other.sizeString;
    cap = sizeString + 1;
    delete[] nString;
    nString = holder;
    return *this;
}

size_t MyString::find(const MyString &other, size_t pos) const
{
    // check bounds
    if (other.sizeString > this->sizeString || pos >= this->sizeString || this->sizeString <= 0)
    {
        return -1;
    }
    else
    {
        // go through each element in the this nString to compare with string that we are trying to find
        for (unsigned int i = pos; i < this->sizeString; ++i)
        {
            for (unsigned int k = 0; k < other.sizeString; ++k)
            {
                if (this->nString[i + k] != other.nString[k])
                    break;
                if (k == other.sizeString - 1)
                    return i;
            }
        }
        return -1;
    }
}

// int main() {
//     MyString temp = "eric";
//     MyString array1 = temp;
//     cout << "test:" << array1 << endl;

//     MyString temp2 = "mcgonagle";
//     temp += temp2;
//     cout << "Testing +=: " << temp << endl;



//     // const char array2[] = "mcgonagle";
//     // const char *arrayp2 = array2;
//     // MyString test2(arrayp2);
//     // cout << "high" << endl;
//     // test1 += test2;
//     // cout << "Test +=: " << test1;

//     return 0;
// }
