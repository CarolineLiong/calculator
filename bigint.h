/**
  Caroline Liongosari
  **/

#ifndef BIGINT_H
#define BIGINT_H
#include <cstdlib>
#include <string>
#include <QString>
#include <cassert>
//WANT: integers with CAPACITY digits, positive and negative


class bigint
{
public:
    //CONSTANTS & TYPES

    typedef std::size_t size_type;
    static const size_type CAPACITY = 30;

    //CONSTRUCTORS

    //pre: none
    //post: creates a bigint with i as value (ignore digit overflow)
    bigint(int i = 0);

    //pre: none
    //post: copies bigint src (source) into "this" bigint
    bigint(const bigint &src);

    //pre: s contains only decimal digits; the first letter could be + or -
    //post: creates a bigint whose value corresponds to given string of digits
    bigint(const char *s);

    //pre: s contains only decimal digits; the first letter could be + or -
    //post: creates a bigint whose value corresponds to given string of digits
    bigint(const QString &);

    //CONSTANT MEMBER FUNCTIONS

    //pre: pos<CAPACITY
    //post: returns the digit at the position pos (0 is the least significant (units) position
    size_type operator [](size_type pos) const;

    //pre:none
    //post: returns true if negative
    bool is_negative() const;

    //pre:none
    //post: return true if the value is zero
    bool is_zero() const;

    //pre:none
    //post: returns this bigint in a form of a QString
    QString toQString() const;

    //pre: none
    //post: returns 1 if this bigint >b
    //          0 if this bigint ==b
    //          -1 if this bigint < b
    int compare(const bigint &b) const;

    //MODIFICATION MEMBER FUNCTIONS

    //pre: none
    //post: b is added to this bigint; ignore last carry bit if any
    bigint &operator += (const bigint &b);

    //pre: none
    //post: b is substracted from this bigint; ignore last carry bit if any
    bigint &operator -= (const bigint &b);

    //pre: none
    //post: b is multiplied with this bigint;
    bigint &operator *= (const bigint &b);

    //pre: 0<=digit<=9
    //post: digit is multiplied with this bigint
    bigint &operator *=(size_type digit);

    //pre: none
    //post: copy bigint "origin" into this bigint
    bigint &operator = (const bigint &origin);



private:
    size_type _data[CAPACITY];//array containing size_types
    bool      _neg;

    //INVARIANTS:
    //  _data[i] holds the i^th digit of this bigint or 0 if not used
    //  _data[0] holds the least significant (units) digit
    // _neg is true if this bigint is negative
    // 0 is not negative


    //HELPER MEMBER FUNCTIONS

    //pre:none
    //post: intializes all values in _data[] as 0 and _neg=false
    void _init_val();

    //pre: none
    //post: returns  1 if abs(this bigint) > abs(b)
    //           	 0 if abs(this bigint) == abs(b)
    //          	-1 if abs(this bigint) < abs(b)
    int _abs_compare(const bigint &b) const;

    //pre: none
    //post: add b to this bigint ignoring the _neg flag
    //this is a helper function for addition
    void _abs_add(const bigint &b, const bool result_is_neg);

    //pre: none
    //post: substract b from this bigint ignoring the _neg flag
    //this is a helper function for substraction
    void _abs_substract (const bigint &b, const bool bigger_is_neg);

    //pre: the value of 'bigger' has to be bigger or same as the value of 'smaller'
    //post: substract 'smaller' from 'bigger' and store the result to this bigint ignorning the _negflag
    //this is a helper function for substraction
    void _abs_substract_helper (const bigint &bigger, const bigint &smaller);

    //pre: number_of_shift is between 0 and CAPACITY inclusive, and fill is between 0-9 inclusive.
    //post: shift the digits to the left and fill the empty slots with 'fill'
    // this is a helper function for multiplication
    void shift_left (int number_of_shift, int fill);
};

//nonmember functions

std::ostream &operator << (std::ostream &, const bigint &);

bigint operator +(const bigint &, const bigint &);
bigint operator -(const bigint &, const bigint &);
bigint operator *(const bigint &, const bigint &);
bigint operator -(const bigint &);//unary operator


bool operator <  (const bigint &, const bigint &);
bool operator <= (const bigint &, const bigint &);
bool operator >  (const bigint &, const bigint &);
bool operator >= (const bigint &, const bigint &);
bool operator != (const bigint &, const bigint &);
bool operator == (const bigint &, const bigint &);



#endif // BIGINT_H

