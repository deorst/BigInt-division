#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

/**
 * Next steps:
 * - Use `divideChunk` for division any numbers. 
 */

// Declarations
template <typename T>
vector<T> fromIntegralType(const T &num);
template <typename T>
T toIntegralType(const vector<T> &num);

template <typename T>
bool operator<(const vector<T> &left, const vector<T> &right);
template <typename T>
bool operator<(const vector<T> &left, const T &right);
template <typename T>
bool operator<(const T &left, const vector<T> &right);

template <typename T>
vector<T> operator+(const vector<T> &left, const vector<T> &right);
template <typename T>
vector<T> operator+(const vector<T> &left, const T &right);
template <typename T>
vector<T> operator+(const T &left, const vector<T> &right);

template <typename T>
vector<T> operator-(const vector<T> &left, const vector<T> &right);
// template <typename T>
// vector<T> operator-(const vector<T> &left, const T &right);
// template <typename T>
// vector<T> operator-(const T &left, const vector<T> &right);

template <typename T>
vector<T> operator*(const vector<T> &left, const vector<T> &right);

template <typename T>
vector<T> divideBySingleNumber(const vector<T> &dividend, const T &divisor);

template <typename T>
T divideChunk(const vector<T> &dividend, const vector<T> &divisor);

template <typename T>
void trim(vector<T> &x);

// Definitions
template <typename T>
vector<T> fromIntegralType(const T &num)
{
  int _num{num};
  vector<T> res{};
  while (_num)
  {
    res.push_back(_num % 10);
    _num /= 10;
  }
  return res;
}

template <typename T>
T toIntegralType(const vector<T> &num)
{
  T res{};
  for (auto i{num.rbegin()}; i != num.rend(); ++i)
  {
    res *= 10;
    res += *i;
  }
  return res;
}

template <typename T>
bool operator<(const vector<T> &left, const vector<T> &right)
{
  if (left.size() == right.size())
  {
    int i{(int)left.size()};
    while (i--)
    {
      if (left[i] != right[i])
        return left[i] < right[i];
    }
    return false;
  }
  else
    return (left.size() < right.size());
}

template <typename T>
bool operator<(const vector<T> &left, const T &right)
{
  return left < fromIntegralType(right);
}

template <typename T>
bool operator<(const T &left, const vector<T> &right)
{
  return fromIntegralType(left) < right;
}

template <typename T>
vector<T> operator+(const vector<T> &left, const vector<T> &right)
{
  if (left < right)
  {
    return (right + left);
  }
  else
  {
    vector<T> out{};
    int carry{};
    for (int i{}; i < left.size(); ++i)
    {
      if (out.size() <= i)
        out.push_back(0);
      if (i < right.size())
      {
        out[i] = carry + left[i] + right[i];
        carry = out[i] / 10;
        out[i] %= 10;
      }
      else
      {
        out[i] = left[i] + carry;
        carry = out[i] / 10;
        out[i] %= 10;
      }
    }
    if (carry)
    {
      out.push_back(carry);
    }
    return out;
  }
}

template <typename T>
vector<T> operator+(const vector<T> &left, const T &right)
{
  return left + fromIntegralType(right);
}

template <typename T>
vector<T> operator+(const T &left, const vector<T> &right)
{
  return right + left;
}

template <typename T>
vector<T> operator-(const vector<T> &left, const vector<T> &right)
{
  // We assume left >= right
  vector<T> out{};
  int borrow{};
  for (int i{}; i < right.size(); ++i)
  {
    out.push_back(0);
    if ((left[i] - borrow) >= right[i])
    {
      out[i] = left[i] - borrow - right[i];
      borrow = 0;
    }
    else
    {
      out[i] = left[i] - borrow + 10 - right[i];
      borrow = 1;
    }
  }

  for (int i{(int)right.size()}; i < left.size(); ++i)
  {
    if (left[i] - borrow)
    {
      out.push_back(0);
      out[i] = left[i] - borrow;
      borrow = 0;
    }
  }
  return out;
}
template <typename T>
vector<T> operator*(const vector<T> &left, const vector<T> &right)
{
  vector<T> out{};
  for (int i{}; i < right.size(); ++i)
  {
    int carry{};
    for (int j{}; j < left.size(); ++j)
    {
      if (out.size() <= i + j)
        out.push_back(0);
      out[i + j] += right[i] * left[j] + carry;
      carry = out[i + j] / 10;
      out[i + j] %= 10;
    }
    if (carry)
      out.push_back(carry);
  }
  return out;
}
template <typename T>
vector<T> divideBySingleNumber(const vector<T> &dividend, const T &divisor)
{
  vector<T> quot{};
  T rem{};
  for (int i{(int)dividend.size() - 1}; i >= 0; --i)
  {
    int currQuot{(dividend[i] + rem) / divisor};
    if (currQuot)
    {
      rem = (dividend[i] + rem) % divisor;
    }
    else
    {
      rem += dividend[i];
    }
    quot.push_back(currQuot);
    rem *= 10;
  }
  reverse(quot.begin(), quot.end());
  trim(quot);
  return quot;
}

template <typename T>
void trim(vector<T> &x)
{
  int size{(int)x.size()};
  while (size--)
  {
    if (x[size])
      break;
  }
  x.resize(size + 1);
}

template <typename T>
T divideChunk(const vector<T> &dividend, const vector<T> &divisor)
{
  if (dividend < divisor)
    return 0;
  else
  {
    int i{(int)dividend.size() - 1}, j{(int)divisor.size() - 1}, quot{};
    vector<int> rem{};
    while (i >= 0)
    {
      rem = rem * vector<int>{0, 1};
      trim(rem);
      int currQuot{toIntegralType(divideBySingleNumber((rem + dividend[i]), divisor[j]))};
      if (currQuot)
      {
        if (quot)
        {
          if (quot > currQuot)
          {
            --quot;
            rem = rem + divisor[j + 1];
            continue;
          }
        }
        else
          quot = currQuot;

        rem = dividend[i] + rem - fromIntegralType(divisor[j] * quot);
        --j;
      }
      else
      {
        if (quot)
        {
          --quot;
          rem = rem + divisor[j + 1];
          ++j;
          continue;
        }
        else
          rem = rem + dividend[i];
      }
      --i;
    }
    return quot;
  };
}

void testLessThan()
{
  cout << "Test LessThan...";
  // vector<T> < vector<T>
  {
    vector<int> left{0}, right{1};
    assert(left < right);
    assert(!(right < left));
    assert(!(left < left));
    assert(!(right < right));
  }
  {
    vector<int> left{9}, right{1, 1};
    assert(left < right);
    assert(!(right < left));
    assert(!(left < left));
    assert(!(right < right));
  }
  {
    vector<int> left{2, 1}, right{1, 2};
    assert(left < right);
    assert(!(right < left));
    assert(!(left < left));
    assert(!(right < right));
  }
  {
    vector<int> left{2, 1}, right{2, 1};
    assert(!(left < right));
    assert(!(right < left));
  }
  // vector<T> < T
  {
    vector<int> left{0};
    int right{1};
    assert(left < right);
    assert(!(right < left));
    assert(!(left < left));
    assert(!(right < right));
  }
  {
    vector<int> left{9};
    int right{11};
    assert(left < right);
    assert(!(right < left));
    assert(!(left < left));
    assert(!(right < right));
  }
  {
    vector<int> left{2, 1};
    int right{21};
    assert(left < right);
    assert(!(right < left));
    assert(!(left < left));
    assert(!(right < right));
  }
  {
    vector<int> left{2, 1};
    int right{12};
    assert(!(left < right));
    assert(!(right < left));
  }
  // T < vector<T>
  {
    int left{0};
    vector<int> right{1};
    assert(left < right);
    assert(!(right < left));
    assert(!(left < left));
    assert(!(right < right));
  }
  {
    int left{9};
    vector<int> right{1, 1};
    assert(left < right);
    assert(!(right < left));
    assert(!(left < left));
    assert(!(right < right));
  }
  {
    int left{12};
    vector<int> right{1, 2};
    assert(left < right);
    assert(!(right < left));
    assert(!(left < left));
    assert(!(right < right));
  }
  {
    int left{12};
    vector<int> right{2, 1};
    assert(!(left < right));
    assert(!(right < left));
  }
  cout << "OK\n";
}
void testAddition()
{
  cout << "Test Addition...";
  // vector<T> + vector<T>
  {
    vector<int> left{1}, right{2};
    assert((left + right) == vector<int>{3});
    assert((right + left) == vector<int>{3});
  }
  {
    vector<int> left{9}, right{1};
    assert(((left + right) == vector<int>{0, 1}));
    assert(((right + left) == vector<int>{0, 1}));
  }
  {
    vector<int> left{4, 8}, right{5, 0, 1};
    assert(((left + right) == vector<int>{9, 8, 1}));
    assert(((right + left) == vector<int>{9, 8, 1}));
  }
  {
    vector<int> left{6}, right{7, 9, 9};
    assert(((left + right) == vector<int>{3, 0, 0, 1}));
    assert(((right + left) == vector<int>{3, 0, 0, 1}));
  }

  // vector<T> + T
  {
    vector<int> left{6};
    int right{997};
    assert(((left + right) == vector<int>{3, 0, 0, 1}));
    assert(((right + left) == vector<int>{3, 0, 0, 1}));
  }
  cout << "OK\n";
}
void testSubtraction()
{
  cout << "Test Subtraction...";
  {
    vector<int> left{2}, right{1};
    assert((left - right) == vector<int>{1});
  }
  {
    vector<int> left{0, 1}, right{1};
    assert((left - right) == vector<int>{9});
  }
  {
    vector<int> left{3, 2, 1}, right{2, 4};
    assert(((left - right) == vector<int>{1, 8}));
  }
  cout << "OK\n";
}
void testMultiplication()
{
  cout << "Test Multiplication...";
  {
    vector<int> left{1}, right{2};
    assert(left * right == vector<int>{2});
    assert(right * left == vector<int>{2});
  }
  {
    vector<int> left{1, 1}, right{5, 4, 2};
    assert((left * right == vector<int>{5, 9, 6, 2}));
    assert((right * left == vector<int>{5, 9, 6, 2}));
  }
  {
    vector<int> left{2, 1}, right{7, 5, 4};
    assert((left * right == vector<int>{4, 8, 4, 5}));
  }
  cout << "OK\n";
}
void testDivideChunk()
{
  cout << "Test DivideChunk...";
  {
    vector<int> dividend{4, 2, 1}, divisor{3, 2};
    assert((divideChunk(dividend, divisor) == 5));
  }
  {
    vector<int> dividend{0, 0, 1}, divisor{1, 1};
    assert((divideChunk(dividend, divisor) == 9));
  }
  {
    vector<int> dividend{5}, divisor{2};
    assert((divideChunk(dividend, divisor) == 2));
  }
  {
    vector<int> dividend{1}, divisor{1};
    assert((divideChunk(dividend, divisor) == 1));
  }
  {
    vector<int> dividend{1}, divisor{2};
    assert((divideChunk(dividend, divisor) == 0));
  }
  {
    vector<int> dividend{4, 3, 2, 1}, divisor{4, 3, 2};
    assert((divideChunk(dividend, divisor) == 5));
  }
  cout << "OK\n";
}
void testDivideBySingleNumber()
{
  cout << "Test Divide by Single Number...";
  {
    vector<int> dividend{7};
    int divisor{3};
    assert(divideBySingleNumber(dividend, divisor) == vector<int>{2});
  }
  {
    vector<int> dividend{0, 1, 1};
    int divisor{9};
    assert((divideBySingleNumber(dividend, divisor) == vector<int>{2, 1}));
  }
  {
    vector<int> dividend{8};
    int divisor{9};
    assert((divideBySingleNumber(dividend, divisor) == vector<int>{}));
  }
  {
    vector<int> dividend{0, 1};
    int divisor{1};
    assert((divideBySingleNumber(dividend, divisor) == vector<int>{0, 1}));
  }
  cout << "OK\n";
}
void testFromIntegralType()
{
  cout << "From Integral type...";
  assert((fromIntegralType(1) == vector<int>{1}));
  assert((fromIntegralType(12) == vector<int>{2, 1}));
  assert((fromIntegralType(1200) == vector<int>{0, 0, 2, 1}));
  cout << "OK\n";
}
void testToIntegralType()
{
  cout << "Test To Integral type...";
  {
    vector<int> num{1};
    assert(toIntegralType(num) == 1);
  }
  {
    vector<int> num{2, 3, 1};
    assert(toIntegralType(num) == 132);
  }
  {
    vector<int> num{0, 0, 0, 1};
    assert(toIntegralType(num) == 1000);
  }
  cout << "OK\n";
}
void testTrim()
{
  cout << "Test Trim...";
  {
    vector<int> x{0, 0, 1, 0};
    trim(x);
    assert((x == vector<int>{0, 0, 1}));
  }
  cout << "OK\n";
}

int main()
{
  testLessThan();
  testAddition();
  testSubtraction();
  testMultiplication();
  testDivideBySingleNumber();
  testDivideChunk();
  testFromIntegralType();
  testToIntegralType();
  testTrim();
}