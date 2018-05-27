#include"bloom_hash.h"

size_t SDBMHash(const char *str)
{
    size_t hash = 0;
    size_t ch;
    while(ch = (size_t)*str++)
    {
        hash = 65599*hash+ch;
    }
    return hash;
}
size_t BKDRHash(const char *str)
{
    size_t hash = 0;
    size_t ch;
    while(ch = (size_t)*str++)
    {
        hash = hash*131+ch;
    }
    return hash;
}
