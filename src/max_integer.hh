#ifndef MAX_INTEGER_HH
#define MAX_INTEGER_HH
/*
 * Compile time maximum integer
 */

template <size_t N1, size_t N2>
struct Max {
  enum { val = N1 > N2 ? N1 : N2 };
};


#endif
