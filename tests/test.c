#include "../math/math.h"
#include <assert.h>

int main() {
  // add
  assert(add(2, 3) == 5);
  assert(add(-2, 1) == -1);
  // minus
  assert(minus(3, 2) == 1);
  assert(minus(2, 3) == -1);
  // krat
  assert(krat(2, 3) == 6);
  assert(krat(-2, 3) == -6);
  // divide
  assert(divide(6, 3) == 2);
  assert(divide(4, -2) == -2);
  // math
  // Jednoduché výrazy
  assert(math("2+3") == 5.0L);
  assert(math("10-4") == 6.0L);
  assert(math("3*4") == 12.0L);
  assert(math("8/2") == 4.0L);

  // Více operací
  assert(math("2+3*4") == 14.0L);
  assert(math("10-3-2") == 5.0L);

  // Závorky
  assert(math("(2+3)*4") == 20.0L);
  assert(math("2*(3+4)") == 14.0L);

  // Záporné výsledky
  assert(math("2-5") == -3.0L);
  assert(math("2-10") == -8.0L);

  return 0;
  // eval
}
