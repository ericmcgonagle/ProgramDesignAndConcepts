#include <iostream>
#include <string>
#include "./string_calculator.h"

using std::cout;
using std::endl;
using std::string;

unsigned int digit_to_decimal(char digit)
{
    // TODO(student): implement
    int newDigit = (int)(digit - '0');
    if (newDigit < 0 || newDigit > 9)
        throw std::invalid_argument("");
    return newDigit;
}

char decimal_to_digit(unsigned int decimal)
{
    // TODO(student): implement
    if (decimal > 9)
        throw std::invalid_argument("");
    else
        return (char)(decimal + '0');
}

string trim_leading_zeros(string num)
{
    // TODO(student): implement
    int numLength = num.size();
    bool allZero = true;
    int i = 0;
    for (i = 0; i < numLength; i++)
    {
        if (num.at(i) == '-')
            continue;
        if (num.at(i) != '0')
        {
            allZero = false;
            break;
        }
    }
    // return 0 if the string is all zeros
    if (allZero)
        return "0";

    // check index 1 if there is a negative at the front
    // else check index 0 if the number is positive
    if (num.at(0) == '-')
    {
        i = 1;
        while (true)
        {
            if (num.at(i) == '0')
                num.erase(i, 1);
            if (num.at(i) != '0')
                break;
        }
    }
    else
    {
        i = 0;
        while (true)
        {
            if (num.at(i) == '0')
                num.erase(i, 1);
            if (num.at(i) != '0')
                break;
        }
    }
    return num;
}

string add(string lhs, string rhs)
{
    // TODO(student): implement
    // going to need temporary variables to hold current values as ints when going
    // through specific chars in the string

    int lhsNum;
    int rhsNum;
    int holder;
    int sum;
    string final;
    string sumDigit;
    string holderDigit;
    // start by reading through the string digit by digit
    // make sure the lenghts are the same

    lhs = trim_leading_zeros(lhs);
    rhs = trim_leading_zeros(rhs);

    // negative numbers
    if (lhs.at(0) == '-')
    {
        if (lhs.size() != rhs.size())
        {
            if (lhs.size() > rhs.size())
            {
                while (rhs.size() != lhs.size())
                {
                    rhs.insert(1, "0");
                }
            }
            else if (lhs.size() < rhs.size())
            {
                while (lhs.size() != rhs.size())
                {
                    lhs.insert(1, "0");
                }
            }
        }
        holder = 0; // start off by carring "0"
        for (int i = lhs.size() - 1; i > 0; i--)
        {
            lhsNum = digit_to_decimal(lhs.at(i));
            rhsNum = digit_to_decimal(rhs.at(i));
            sum = lhsNum + rhsNum + holder;
            if (sum > 9)
            {
                sum = sum % 10;
                holder = 1;
            }
            else
            {
                holder = 0;
            }
            sumDigit = decimal_to_digit(sum);
            final.insert(0, sumDigit);
        }

        // if holder = 1 then add to final
        if (holder == 1)
        {
            holderDigit = decimal_to_digit(holder);
            final.insert(0, holderDigit);
        }

        final.insert(0, "-");
    }
    else
    {
        // positive numbers
        if (lhs.size() != rhs.size())
        {
            if (lhs.size() > rhs.size())
            {
                while (rhs.size() != lhs.size())
                {
                    rhs.insert(0, "0");
                }
            }
            else if (lhs.size() < rhs.size())
            {
                while (lhs.size() != rhs.size())
                {
                    lhs.insert(0, "0");
                }
            }
        }

        // start adding individual digits now that lenghts are same for positive values
        holder = 0; // start off by carring "0"
        for (int i = lhs.size() - 1; i >= 0; i--)
        {
            lhsNum = digit_to_decimal(lhs.at(i));
            rhsNum = digit_to_decimal(rhs.at(i));
            sum = lhsNum + rhsNum + holder;
            if (sum > 9)
            {
                sum = sum % 10;
                holder = 1;
            }
            else
            {
                holder = 0;
            }
            sumDigit = decimal_to_digit(sum);
            final.insert(0, sumDigit);
        }

        // if holder = 1 then add to final
        if (holder == 1)
        {
            holderDigit = decimal_to_digit(holder);
            final.insert(0, holderDigit);
        }
    }

    return final;
}

string multiply(string lhs, string rhs)
{
    // TODO(student): implement
    int rhsNum;
    int lhsNum;
    int product;
    int holder;
    string productDigit;
    string holderDigit;
    string sum1;
    string sum2;

    // first trim leading zeros
    lhs = trim_leading_zeros(lhs);
    rhs = trim_leading_zeros(rhs);

    sum1 = "0";
    // if both negative
    if ((lhs.at(0) == '-') && (rhs.at(0) == '-'))
    {
        lhs.erase(0, 1);
        rhs.erase(0, 1);
    }
    // if either is negative
    else if ((lhs.at(0) == '-') && (rhs.at(0) != '-'))
    {
        lhs.erase(0, 1);
        for (int i = rhs.size() - 1; i >= 0; i--)
        {
            rhsNum = digit_to_decimal(rhs.at(i));
            sum2.append((rhs.size() - i) - 1, '0');
            holder = 0;
            for (int k = lhs.size() - 1; k >= 0; k--)
            {
                lhsNum = digit_to_decimal(lhs.at(k));
                product = lhsNum * rhsNum + holder;
                if (product > 9)
                {
                    holder = product / 10;
                    product = product % 10;
                }
                else
                {
                    holder = 0;
                }
                productDigit = decimal_to_digit(product);
                sum2.insert(0, productDigit);
            }
            if (holder != 0)
            {
                holderDigit = decimal_to_digit(holder);
                sum2.insert(0, holderDigit);
            }

            sum1 = add(sum2, sum1);
            sum2.clear();
        }

        sum1.insert(0, "-");
        return sum1;
    }
    else if ((lhs.at(0) != '-') && (rhs.at(0) == '-'))
    {
        rhs.erase(0, 1);
        for (int i = rhs.size() - 1; i >= 0; i--)
        {
            rhsNum = digit_to_decimal(rhs.at(i));
            sum2.append((rhs.size() - i) - 1, '0');
            holder = 0;
            for (int k = lhs.size() - 1; k >= 0; k--)
            {
                lhsNum = digit_to_decimal(lhs.at(k));
                product = lhsNum * rhsNum + holder;
                if (product > 9)
                {
                    holder = product / 10;
                    product = product % 10;
                }
                else
                {
                    holder = 0;
                }
                productDigit = decimal_to_digit(product);
                sum2.insert(0, productDigit);
            }
            if (holder != 0)
            {
                holderDigit = decimal_to_digit(holder);
                sum2.insert(0, holderDigit);
            }

            sum1 = add(sum2, sum1);
            sum2.clear();
        }

        sum1.insert(0, "-");
        return sum1;
    }

    for (int i = rhs.size() - 1; i >= 0; i--)
    {
        rhsNum = digit_to_decimal(rhs.at(i));
        sum2.append((rhs.size() - i) - 1, '0');
        holder = 0;
        for (int k = lhs.size() - 1; k >= 0; k--)
        {
            lhsNum = digit_to_decimal(lhs.at(k));
            product = lhsNum * rhsNum + holder;
            if (product > 9)
            {
                holder = product / 10;
                product = product % 10;
            }
            else
            {
                holder = 0;
            }
            productDigit = decimal_to_digit(product);
            sum2.insert(0, productDigit);
        }
        if (holder != 0)
        {
            holderDigit = decimal_to_digit(holder);
            sum2.insert(0, holderDigit);
        }

        sum1 = add(sum2, sum1);
        sum2.clear();
    }

    return sum1;
}
