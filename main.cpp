#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

/**
 * Next steps:
 * 
 * - Use vector<T> rem, instead of int rem;
 * - For that I need `add()` function
 * - For that `add()` function I need to use reversed order in vector<T> data in `add()`, `lessThan()` and `divideChunk()`;
 */

template <typename T>
bool lessThan(const vector<T> &left, const vector<T> &right)
{
  if (left.size() == right.size())
  {
    for (int i{}; i < left.size(); ++i)
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
vector<T> add(vector<T> &out, const vector<T> &left, const vector<T> &right)
{
  if (lessThan(left, right))
  {
    add(out, right, left);
  }
  else
  {
    int i{static_cast<int>(left.size())};
    int carry{};
    while (i--)
    {
      if (i < right.size())
      {
        if (out.size() <= i)
          out.push_back(0);
        out[i] = carry + left[i] + right[i];
        carry = out[i] / 10;
        out[i] %= 10;
      }
      else
      {
        out[i] = left[i] + carry;
        carry = 0;
      }
    }
    if (carry)
    {
    }
  }
  return out;
}

template <typename T>
T divideChunk(const vector<T> &dividend, const vector<T> &divisor)
{
  if (lessThan(dividend, divisor))
    return 0;
  else
  {
    int i{}, j{}, quot{}, rem{};
    while (i < dividend.size())
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
            rem += divisor[j - 1];
            continue;
          }
        }
        else
          quot = currQuot;

        rem = (dividend[i] + rem) % divisor[j];
        ++j;
      }
      else
      {
        if (quot)
        {
          --quot;
          rem += divisor[j - 1];
          --j;
          continue;
        }
        else
          rem += dividend[i];
      }
      ++i;
    }
    return quot;
  };
}

void testDivideChunk()
{
  cout << "Test DivideChunk...";
  {
    vector<int> dividend{1, 2, 4}, divisor{2, 3};
    assert((divideChunk(dividend, divisor) == 5));
  }
  {
    vector<int> dividend{1, 0, 0}, divisor{1, 1};
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
    vector<int> dividend{1, 2, 3, 4}, divisor{2, 3, 4};
    assert((divideChunk(dividend, divisor) == 5));
  }
  cout << "OK\n";
}
void testAdd()
{
  cout << "Test Add...";
  {
    vector<int> out{}, left{1}, right{2};
    add(out, left, right);
    assert(out == vector<int>{3});
  }
  cout << "OK\n";
}

int main()
{
  testDivideChunk();
  testAdd();
  vector<int> out{}, left{9}, right{2};
  add(out, left, right);
  for (auto el : out)
  {
    cout << el << ' ';
  }
  cout << '\n';
}