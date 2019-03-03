
#include <pub\config.hpp>#include <pub\config.hpp>
#include <cnt\array.hpp>
#include <array.tem>

int cnt;

struct S
{
   int val;

   S() { val=cnt++; }
   ~S() { val=-1; }
};

void main()
{
   array<S> A(5);

   A.remove(3);
}


