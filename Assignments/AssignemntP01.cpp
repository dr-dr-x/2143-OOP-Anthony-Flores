/*****************************************************************************
*
*  Author:           Anthony Flores
*  Email:            trainaf04@gmail.com
*  Label:            P01
*  Title:            Fraction Class
*  Course:           OOP 2143
*  Semester:         Fall 2024
*
*  Description:
*        This program implements a Fraction class to perform basic arithmetic
*        operations on fractions. The fraction class encapsulates the numerator
*        and denominator, ensuring that fractions are always stored in their
*        simplest form. The program reads arithmetic expressions involving
*        fractions from an input file, evaluates them, and outputs the results.
*
*  Usage:
*        1. Access the text file named 'input.txt'. An example format is already
*           provided(one of each fraction operation). You can add new lines of
*           different numerator and denominator values with any of the 4 arithmetic
*           operations allowed (addition, subtraction, multiplication, and division).
*        2. Compile and run the program
*        3. The program will read the operations from the file, compute the results,
*           and print them to the console.
*
*  Files:
         - 06-P01.cpp (this source file containing the main program and Fraction class implementation)
         - input.txt (the input file containing fraction operations )
*****************************************************************************/


#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

class Fraction
{
private:
    int numerator;
    int denominator;
    /**
     * Private: gcd
     *
     * Description:
     *      Calculates the greatest common divisor (GCD) of two integers.
     *      (This function was obtained from google)
     *
     * Params:
     *      int a   :  First integer.
     *      int b   :  Second integer.
     *
     * Returns:
     *      int     : The GCD of the two integers.
     */
    int gcd(int a, int b) const
    {
        while (b != 0)
        {
            int temp = b;
            b = a % b;
            a = temp;
        }
        return a;
    }

    /**
     * Private: reduce
     *
     * Description:
     *      Simplifies the fraction by dividing the numerator and denominator by their GCD.
     *      Ensures that the denominator is positive.
     *
     * Params:
     *      None
     *
     * Returns:
     *      None
     */
    void reduce()
    {
        int gcdValue = gcd(numerator, denominator);
        numerator /= gcdValue;
        denominator /= gcdValue;
        if (denominator < 0)        // Ensure the denominator is positive
        {
            numerator = -numerator;
            denominator = -denominator;
        }
    }

public:
    /**
     * Public: Fraction (Constructor)
     *
     * Description:
     *      Initializes a Fraction object with a numerator and denominator, and simplifies
     *      the fraction if valid.
     *
     * Params:
     *      int num :  The numerator of the fraction.
     *      int den :  The denominator of the fraction.
     *
     * Returns:
     *      None
     */
    Fraction(int num, int den) : numerator(num), denominator(den)
    {
        // Consider validating that denominator is not 0
        if (den == 0)
        {
            cout << "Error: Denominator cannot be zero." << endl;
            numerator = 0;  // Invalid state
            denominator = 1;
        }
        else
        {
            reduce();
        }
    }

    /**
     * Public: operator+
     *
     * Description:
     *      Overloads the addition operator to add two Fraction objects and returns the result
     *      as a new simplified Fraction.
     *
     * Params:
     *      const Fraction& other :  The fraction to add.
     *
     * Returns:
     *      Fraction : A new Fraction representing the sum.
     */
    Fraction operator+(const Fraction& other) const
    {
        // 1. Find the least common multiple (LCM) of the denominators
        int commonDenominator = lcm(denominator, other.denominator);
        // 2. Adjust the numerators to the common denominator
        int adjustedNumerator1 = numerator * (commonDenominator / denominator);
        int adjustedNumerator2 = other.numerator * (commonDenominator / other.denominator);
        // 3. Add the numerators
        int resultNumerator = adjustedNumerator1 + adjustedNumerator2;
        // 4. Return the result as a new fraction, simplified
        return Fraction(resultNumerator, commonDenominator);
    }

    // Additional overloaded operators (students should implement these)
    /**
     * Public: operator-
     *
     * Description:
     *      Overloads the subtraction operator to subtract another Fraction from this Fraction
     *      and returns the result as a new simplified Fraction.
     *
     * Params:
     *      const Fraction& other :  The fraction to subtract.
     *
     * Returns:
     *      Fraction : A new Fraction representing the difference.
     */
    Fraction operator-(const Fraction& other) const
    {
        // Find the least common multiple (LCM) of the denominators
        int commonDenominator = lcm(denominator, other.denominator);
        // Adjust the numerators to the common denominator
        int adjustedNumerator1 = numerator * (commonDenominator / denominator);
        int adjustedNumerator2 = other.numerator * (commonDenominator / other.denominator);
        // Subtract the numerators
        int resultNumerator = adjustedNumerator1 - adjustedNumerator2;
        // Return the result as a new fraction, simplified
        return Fraction(resultNumerator, commonDenominator);
    }

    /**
     * Public: operator*
     *
     * Description:
     *      Overloads the multiplication operator to multiply two Fraction objects and returns
     *      the result as a new simplified Fraction.
     *
     * Params:
     *      const Fraction& other :  The fraction to multiply.
     *
     * Returns:
     *      Fraction : A new Fraction representing the product.
     */
    Fraction operator*(const Fraction& other) const
    {
        int resultNumerator = numerator * other.numerator;
        int resultDenominator = denominator * other.denominator;
        // Return the result as a new fraction, simplified
        return Fraction(resultNumerator, resultDenominator);
    }

    /**
     * Public: operator/
     *
     * Description:
     *      Overloads the division operator to divide this Fraction by another Fraction and
     *      returns the result as a new simplified Fraction. Handles division by zero.
     *
     * Params:
     *      const Fraction& other :  The fraction to divide by.
     *
     * Returns:
     *      Fraction : A new Fraction representing the quotient. Returns 0/1 if dividing by zero.
     */
    Fraction operator/(const Fraction& other) const
    {
        if (other.numerator == 0)
        {
            cout << "Error: Division by zero." << endl;
            return Fraction(0, 1);   // Return an invalid result
        }
        int resultNumerator = numerator * other.denominator;
        int resultDenominator = denominator * other.numerator;
        // Return the result as a new fraction, simplified
        return Fraction(resultNumerator, resultDenominator);
    }

    /**
     * Public: operator==
     *
     * Description:
     *      Overloads the equality operator to compare two Fraction objects for equality.
     *
     * Params:
     *      const Fraction& other :  The fraction to compare against.
     *
     * Returns:
     *      bool : True if the fractions are equal, false otherwise.
     */
    bool operator==(const Fraction& other) const
    {
        return (numerator == other.numerator && denominator == other.denominator);
    }

    /**
     * Public: lcm
     *
     * Description:
     *      Helper function to calculate the Least Common Multiple (LCM) of two integers.
     *
     * Params:
     *      int a   :  First integer.
     *      int b   :  Second integer.
     *
     * Returns:
     *      int     : The LCM of the two integers.
     */
    int lcm(int a, int b) const
    {
        return (a * b) / gcd(a, b);  // LCM can be calculated as (a * b) / GCD(a, b)
    }

    // Overload output operator (<<) for printing fractions
    friend ostream& operator<<(ostream& os, const Fraction& frac)
    {
        os << frac.numerator << "/" << frac.denominator;
        return os;
    }
};

/**
 * Public: parseFraction
 *
 * Description:
 *      Parses a string representing a fraction and returns a Fraction object.
 *      The expected format is "numerator/denominator". If the format is invalid,
 *      it returns a default fraction of 0/1.
 *
 * Params:
 *      const string& fracStr : The string representation of the fraction.
 *
 * Returns:
 *      Fraction : A Fraction object parsed from the string.
 */
 // Wasn't quite sure how to implement a Parse fraction so chatGPT assisted with this part of the program
Fraction parseFraction(const string& fracStr)
{
    size_t slashPos = fracStr.find('/');
    if (slashPos == string::npos)
    {
        cout << "Error: Invalid fraction format." << endl;
        return Fraction(0, 1);
    }

    int numerator = 0;
    int denominator = 1;

    numerator = stoi(fracStr.substr(0, slashPos));
    denominator = stoi(fracStr.substr(slashPos + 1));

    return Fraction(numerator, denominator);
}

int main()
{
    ifstream inputFile("input.txt");

    if (!inputFile.is_open())
    {
        cout << "Error: Could not open input file." << endl;
        return 1;
    }

    string line;

    while (getline(inputFile, line))
    {
        stringstream ss(line);
        string frac1Str, frac2Str, operation;

        ss >> frac1Str >> operation >> frac2Str;

        Fraction frac1 = parseFraction(frac1Str);
        Fraction frac2 = parseFraction(frac2Str);
        Fraction result(0, 1);

        if (operation == "+")
        {
            result = frac1 + frac2;
        }
        else if (operation == "-")
        {
            result = frac1 - frac2;
        }
        else if (operation == "*")
        {
            result = frac1 * frac2;
        }
        else if (operation == "/")
        {
            result = frac1 / frac2;
        }
        else
        {
            cout << "Error: Unknown operator." << endl;
            continue;
        }

        cout << frac1Str << " " << operation << " " << frac2Str << " = " << result << endl;
    }

    inputFile.close();
    return 0;
}