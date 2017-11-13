#include "bigint.h"
#include <assert.h>
#include <iostream>
#include <QString>
#include <QChar>
#include <cstring>
#include <cctype>

bigint::bigint(int i)
{
     _init_val();//initialize bigint with 0s

    if (i == 0)
    {
        return;
    }
    else if (i < 0)
    {
        _neg = true;
        i = 0 - i; // make i positive
    }
    else
    {
        _neg = false;
    }

    for (int j = 0; j <(int)CAPACITY && i != 0; j--)
    {
        _data[j] = i % 10; // get the digit
        i = i / 10;        // move to the next digit
    }  // we terminate when i becomes 0 or we just run out of space to store the digits
}


bigint::bigint(const bigint &src)
{
    _neg = src._neg;

    for (int i = 0; i < (int)CAPACITY; i++)
    {
        _data[i] = src._data[i];
    }

}


bigint::bigint(const char *s)
{
    _init_val();
    int len = (int) std::strlen(s);

    if (len == 0)
    {
        return;
    }

    int start = 0;
    char c = s[0];
    assert (c == '+' || c == '-' || isdigit(c));

    if (c == '-')
    {
        _neg = true;
        start = 1;
    }
    else if (c == '+')
    {
        _neg = false;
        start = 1;
    }

    int j(0);
    bool non_zero_found = false;

    for (int i = len-1;j<(int)CAPACITY && i>=start; --i)
    {
        assert (isdigit(s[i]));
        _data[j] = s[i] - '0';
        if (_data[j] != 0) //check that there's a non-zero value in _data[]
            non_zero_found = true;
        j++;
    }

    // making sure that -0 turns into +0
    if (_neg && !non_zero_found)
    {
        _neg = false;
    }
}


bigint::bigint(const QString &s)
{
    _init_val();

    if (s.length() == 0)
    {
        return;
    }

    int start(0);
    char c = s.at(0).toLatin1();
    assert (c== '+' || c == '-' || isdigit(c));

    if (c == '-')
    {
        _neg = true;
        start = 1;
    }
    else if (c == '+')
    {
        _neg = false;
        start =1;
    }

    int j(0);
    bool non_zero_found = false;

    for (int i = s.size()-1;j<(int)CAPACITY && i>=start; --i)
    {
        assert (s.at(i).isDigit());
        _data[j] = s.at(i).toLatin1() - '0';
        if (_data[j] != 0) //check that there's a non-zero value in _data[]
            non_zero_found = true;
        j++;
    }

    // making sure that -0 turns into +0
    if (_neg && !non_zero_found)
    {
        _neg = false;
    }
}


bigint::size_type bigint::operator [] (size_type pos) const
{
    assert(pos < CAPACITY);
    return _data[pos];
}


bigint &bigint::operator += (const bigint &b)
{
    if (!_neg && !b._neg)          // both are pos: a + b
    {
        _abs_add(b, false);        // result is always pos
    }

    else if (!_neg && b._neg)      // a is pos, b is neg: a + (-b)  -> Example: 50 + (-30) = 20
    {
        _abs_substract (b, false); // result is pos if |a| > |b|
    }

    else if (_neg && !b._neg)      // a is neg, b is pos: (-a) + b  -> Example: -50 + 30 = -20
    {
        _abs_substract (b, true);  // result is neg if |a| > |b|
    }
    else 						   // both are neg: (-a) + (-b) = -(a+b)
    {
        _abs_add(b, true);		   // result is always neg
    }
    return *this;
}


bigint &bigint::operator -= (const bigint &b)
{
    if (!_neg && !b._neg) 		   // both are pos: a - b -> Example: 50 - 30 = 20
    {
        _abs_substract (b, false); // result is positive if |a| > |b|
    }
    else if (!_neg && b._neg) 	   // a is pos, b is neg: a - (-b) = a + b -> Example: 50 - (-30) = 80
    {
        _abs_add(b, false);   	   // result is always positive
    }
    else if (_neg && !b._neg) 	   // a is neg, b is pos: -a - b = -(a+b) -> Example: -50 - 30 = -80
    {
        _abs_add(b, true);         // result is always negative
    }
    else 						   // both are neg: -a - (-b) = -a + b
    {
        _abs_substract (b, true);  // result is neg if |a| > |b|
    }
    return *this;
}

/* THE LONG METHOD: A*B = adding A B number of times
void bigint::operator *= (const bigint &b)
{
    if (is_zero()) // if 'this' bigint is already 0, then result is zero; this bigint stays the same
    {
       return;
    }
    else if (b.is_zero()) // if b is zero, then set 'this' bigint to zero
    {
       _init_val();
       return;
    }
    // add 'this' to itself b times
    bool _neg_result (false);
    if (_neg != b._neg) // if the signs of both bigints are not the same, then result is negative, otherwise it is positive
    {
      _neg_result = true;
    }
    // add 'this' to itself b times
    _neg = false;    // make 'this' positive
    bigint result;   // the result of the multiplication here
    bigint one(1);   // make a bigint of value 1

    while (!is_zero())  // repeats until 'this' bigint becomes 0
    {
       result += b;    // add b to result
       *this -= one;   // substract one from 'this' so it functions as a count
    }

    *this = result;      // copy the result back to this
     _neg = _neg_result;  // restore the sign
}
*/


bigint &bigint::operator *= (const bigint &b)
{
    bigint one(1);
    bigint neg_one(-1);

    if (is_zero()) // if 'this' bigint is already 0, then result is zero; this bigint stays the same
    {
        return *this;
    }
    else if (b.is_zero()) // if b is zero, then set 'this' bigint to zero
    {
       _init_val();
       return *this;
    }
    else if (*this == one)
    {
        *this = b;  // 1 * anything is anything
        return *this;
    }
    else if (b == one)
    {
        return *this; // anything * 1 is anything
    }
    else if (*this == neg_one)
    {
        *this = b;
        _neg = !_neg;  // multiplication by -1 means flipping the sign
        return *this;
    }
    else if (b == neg_one)
    {
        _neg = !_neg;  // multiplication by -1 means flipping the sign
        return *this;
    }

    // No shortcut. Find resulting sign for the product
    bool _neg_result (false);
    if (_neg != b._neg) // if the signs of both bigints are not the same, then result is negative, otherwise it is positive
    {
      _neg_result = true;
    }


    bigint a(*this);  // keep the original value of this. We need to use 'this' to store the multiplication result
    _init_val();      // since we are resetting 'this' to zero

    // For each digit of b, multiply with a
    for (int i = 0; i < CAPACITY; i++)
    {
        bigint temp(a);
        temp *= b[i];  // single digit multiplication
        temp.shift_left(i,0);
        *this += temp; // add the results to this
    }

     _neg = _neg_result;  // restore the sign
     return *this;
}


// multiply a (which is a single digit) with 'this'
bigint &bigint::operator *= (size_type a)
{
    assert (a >= 0 && a <= 9); // a has to be a single digit

    int carry(0);
    bigint b(*this); // copy 'this' to b so we can store multiplication result to this
    _init_val();     // reset this to zero to start clean

    // multiply a with each digit of b
    int i;
    for (i = 0; i < (int) CAPACITY; i++)
    {
        int digit = b[i] * a + carry;
        carry = digit / 10;
        _data[i] = digit % 10;
    }

    // Store the final carry (if necessary)
    if (carry > 0 && i < (int) CAPACITY)
    {
        _data[i] = carry;
    }

    return *this;
}

// shift the digits x number of times, where x = number_of_shift
// and fill those digits not shifted with value of 'fill' (which is 0 for multiplication)
void bigint::shift_left(int number_of_shift, int fill)
{
    assert (number_of_shift >= 0);
    assert (fill >= 0 && fill <= 9); // fill has to be a single digit

    // shift the digits x number of times, where x = number_of_shift
    for (int i = 0; i < number_of_shift; i++)
    {
        for (int j = CAPACITY-1; j > 0; j--) // shift all digits once
        {
            _data[j] = _data[j-1];
        }
        _data[0] = fill;
    }
}



// assignment operator which is the same as copy
bigint &bigint::operator = (const bigint &origin)
{
    _neg = origin._neg;

    for (int i = 0; i < (int)CAPACITY; i++)
    {
        _data[i] = origin._data[i];
    }
    return *this;
}



bool bigint::is_negative() const
{
    return _neg;
}


bool bigint::is_zero() const
{
    for (int i = CAPACITY - 1; i >= 0; --i)
    {
        if (_data[i] != 0)
        {
          return false;
        }

    }
    return true;
}



QString bigint::toQString() const
{
   QString s;

   if (_neg)
   {
       s.append("-");
   }

   //find the location for the non-zero most significant digit;
   int j(0);
   for (int i = bigint::CAPACITY-1; i>=0; --i)
   {
       if (_data[i]!=0)
       {
           j=i;
           break;
       }
   }

   // found the location and now start printing
   for (; j >= 0; --j)
   {
       s.append(QChar((char)_data[j] + '0')); //convert _data[i] to ASCII so its char can be added to Qstring s
   }

   return s;
}


std::ostream &operator << (std::ostream & os, const bigint &b)
{
    if (b.is_negative())
    {
        os << "-";
    }

    //find the location for the non-zero most significant digit;
    int j(0);
    for (int i = bigint::CAPACITY-1; i>=0; --i)
    {
        if (b[i]!=0)
        {
            j=i;
            break;
        }
    }

    // found the location and now start printing
    for (int i = j; i>= 0; --i )
    {
        os << b[i];
    }
    return os;
}


void bigint::_init_val()
{
    for (int i = 0; i < (int) CAPACITY ; ++i)
    {
        _data[i] = 0; //initialize array
    }
    _neg = false;
}


int bigint::_abs_compare(const bigint &b) const
{
    for (int i = CAPACITY - 1; i >= 0; --i)
    {
        if (_data[i] > b._data[i])
        {
          return 1;
        }
        else if (_data[i] < b._data[i])
        {
          return -1;
        }
    }
    return 0;
}



void bigint::_abs_add(const bigint &b, const bool result_is_neg)
{
    int carrybit(0);
    for (int i = 0; i <= CAPACITY; ++i)
    {
        int a = _data[i];
        _data[i] = (a + b._data[i] + carrybit) % 10;
        carrybit = (a + b._data[i] + carrybit) / 10;
    }
    _neg = result_is_neg;
}


void bigint::_abs_substract (const bigint &b, const bool bigger_is_neg)
{
    int compare_val = _abs_compare(b);

    if (compare_val == 0)      // |this| == |b| -> Example: 50 + (-50) = 0 or -50 + 50 = 0
    {
        _init_val();
    }
    else if (compare_val > 0 ) // |this| > |b| -> Example: 50 + (-30) = 20 or 50 - 30 = 20
    {
        _abs_substract_helper(*this,b);
        _neg = bigger_is_neg;
    }
    else                       // |this| < |b| -> Example: 30 + (-50) = -20 or 30 - 50 = -20
    {
        _abs_substract_helper(b,*this);
        _neg = !bigger_is_neg;
    }
}



void bigint::_abs_substract_helper (const bigint &bigger, const bigint &smaller)
{
    int borrowed(0);
    for (int i = 0; i <= CAPACITY; ++i)
    {
        int c = bigger._data[i] - smaller._data[i] - borrowed ;
        if (c < 0)
        {
            c += 10;
            borrowed = 1;
        }
        else
        {
            borrowed = 0;
        }
        _data[i] = c;
    }
}

int bigint::compare(const bigint &b) const
{
    if (_neg &&!b._neg)
    {
        return -1;
    }
    if (!_neg && b._neg)
    {
        return 1;
    }

    for (int i = CAPACITY-1; i>=0; --i)
    {
        if (_data[i] >b._data[i])
        {
            if (!_neg)
            {
                return 1;
            }
            else
            {
                return -1;
            }
        }
        else if (_data[i] < b._data[i])
        {
            if (!_neg)
            {
                return -1;
            }
            else
            {
                return 1;
            }
        }

    }
    return 0;
}


bigint operator + (const bigint & a, const bigint &b)
{
       bigint ans(a);
       ans += b;
       return ans;
}


bigint operator - (const bigint &a, const bigint &b)
{
    bigint ans(a);
    ans -= b;
    return ans;
}


bigint operator * (const bigint &a, const bigint &b)
{
    bigint ans(a);
    ans *= b;
    return ans;
}


bigint operator -(const bigint &a)
{
    bigint ans(0);
    ans -= a;
    return ans;
}


bool operator < (const bigint &b1, const bigint &b2)
{
    return (b1.compare(b2) < 0);
}


bool operator <= (const bigint &b1, const bigint &b2)
{
    return (b1.compare(b2) <= 0);
}


bool operator == (const bigint &b1, const bigint &b2)
{
    return (b1.compare(b2) == 0);
}


bool operator != (const bigint &b1, const bigint &b2)
{
    return (b1.compare(b2) !=0 );
}


bool operator >= (const bigint &b1, const bigint &b2)
{
    return (b1.compare(b2) >= 0);
}


bool operator > (const bigint &b1, const bigint &b2)
{
    return (b1.compare(b2) > 0);
}


