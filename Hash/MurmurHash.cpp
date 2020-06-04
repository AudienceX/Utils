#include <iostream>
//using namespace std;
using std::cin;
using std::cout;


unsigned long long MurmurHash2A_64(const void * key, int len, unsigned int seed)
{
    const unsigned long long m = 0xc6a4a7935bd1e995;
    const int r = 47;

    unsigned long long h = seed ^ (len * m);

    const unsigned long long * data = (const unsigned long long *) key;
    const unsigned long long * end = data + (len / 8);

    while (data != end)
    {
        unsigned long long k = *data++;

        k *= m;
        k ^= k >> r;
        k *= m;

        h ^= k;
        h *= m;
    }

    const unsigned char * data2 = (const unsigned char*) data;
    switch (len & 7)
    {
    case 7:
        h ^= (unsigned long long) (data2[6]) << 48;
    case 6:
        h ^= (unsigned long long) (data2[5]) << 40;
    case 5:
        h ^= (unsigned long long) (data2[4]) << 32;
    case 4:
        h ^= (unsigned long long) (data2[3]) << 24;
    case 3:
        h ^= (unsigned long long) (data2[2]) << 16;
    case 2:
        h ^= (unsigned long long) (data2[1]) << 8;
    case 1:
        h ^= (unsigned long long) (data2[0]);
        h *= m;
    default:
        ;
    };

    h ^= h >> r;
    h *= m;
    h ^= h >> r;

    return h;
}

unsigned long long uln_sign_murmur2_64(const void *src, int len)
{
    if (src == NULL)
    {
        return 0;
    }
    unsigned int sign1 = 0;
    unsigned int sign2 = 0;
    unsigned long long ret = MurmurHash2A_64(src, len, 0UL);
    sign1 = (unsigned int) ((ret >> 32) & 0x0ffffffff);
    sign2 = (unsigned int) (ret & 0x0ffffffff);
    unsigned long long sign = (((unsigned long long) sign1) << 32ULL) + (unsigned long long) sign2;
    return sign;
}


std::string midgen(std::string key)
{
    unsigned long long sign = uln_sign_murmur2_64(key.c_str(), key.length());
    char s[100];
    snprintf(s, 100, "%llu", sign);
    return s;
}

int main()
{
    std::string ret = midgen("test");
}
