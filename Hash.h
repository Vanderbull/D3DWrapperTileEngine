#ifndef H_HASH
#define H_HASH
#include <cstdio>
using namespace std;

struct hash_elem_t {
   char *ident;
   struct hash_elem_t *next_elem;
};

class Hashing
{
public:

	Hashing()
	{
	};
	~Hashing(){};
};
#endif
