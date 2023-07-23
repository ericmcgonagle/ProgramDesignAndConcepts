// TODO: Implement this header file

#ifndef MYSTRING_H
#define MYSTRING_H

#include <iostream>
#include <fstream>
#include <tuple>
#include <limits>
#include <stdexcept>
//#include "Rover.h"

class MyString
{
private:
    char *nString;
    unsigned int  sizeString;
    unsigned int cap;

public:
    MyString();
    MyString(const MyString &other);
    MyString(const char *c);
    ~MyString();
    void resize(size_t n);
    size_t capacity() const;
    size_t size() const;
    size_t length() const;
    const char *data() const;
    bool empty() const;
    const char &front() const;
    const char &at(size_t pos) const;
    void clear();
    friend std::ostream &operator<<(std::ostream &os, const MyString &other);
    MyString &operator=(const MyString &other);
    MyString &operator+=(const MyString &other);
    size_t find(const MyString &other, size_t pos = 0) const;
};

#endif