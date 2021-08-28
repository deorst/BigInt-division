#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

/**
 * Next steps:
 * 
 * - Use vector<T> rem, instead of int rem;
 * - For that I need `add()` function
 */

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
T divideChunk(const vector<T> &dividend, const vector<T> &divisor)
{
  if (dividend < divisor)
    return 0;
  else
  {
    int i{(int)dividend.size() - 1}, j{(int)divisor.size() - 1}, quot{}, rem{};
    while (i >= 0)
    {
      rem *= 10;
      int currQuot{((dividend[i] + rem) / divisor[j])};
      if (currQuot)
      {
        if (quot)
        {
          if (quot > currQuot)
          {
            --quot;
            rem += divisor[j + 1];
            continue;
          }
        }
        else
          quot = currQuot;

        rem = (dividend[i] + rem) % divisor[j];
        --j;
      }
      else
      {
        if (quot)
        {
          --quot;
          rem += divisor[j + 1];
          ++j;
          continue;
        }
        else
          rem += dividend[i];
      }
      --i;
    }
    return quot;
  };
}

void testAddition()
{
  cout << "Test Addition...";
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
  cout << "OK\n";
}
void testLessThan()
{
  cout << "Test LessThan...";
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

int main()
{
  testLessThan();
  testAddition();
  testDivideChunk();
}