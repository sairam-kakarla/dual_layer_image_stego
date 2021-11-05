#include "PGM.h"

int get_bit(int number, int index)
{
    /*
    Function to get the indexed bit of a six bit number.
    Arguments: number[int](atleast 6 bit representation).
                index[int](range 1-6)
    indexing order:
    (b1)(b2)(b3)(b4)(b5)(b6)
    */
    int bit = -1;
    switch (index)
    {
    case 1:
        // (10 0000)2=(32)10
        bit = number & 32;
        bit = bit >> 5;
        break;
    case 2:
        // (01 0000)2=(16)10
        bit = number & 16;
        bit = bit >> 4;
        break;
    case 3:
        //  (00 1000)2=(8)10
        bit = number & 8;
        bit = bit >> 3;
        break;
    case 4:
        // (00 0100)2=(4)10
        bit = number & 4;
        bit = bit >> 2;
        break;
    case 5:
        // (00 0010)2=(2)10
        bit = number & 2;
        bit = bit >> 1;
        break;
    case 6:
        // (00 0001)2=(1)10
        bit = number & 1;
        break;
    default:
        printf("Index out of bound for bit extraction\n");
        break;
    }
    return bit;
}

int get_lsb(int number)
{
    return number & 1;
}

int *generate_random_secret(int length)
{
    int *random_secret = (int *)malloc(length * sizeof(int));
    if (!random_secret)
    {
        printf("ERROR: Memory Allocation for random secret data failed");
        exit(1);
    }
    for (int i = 0; i < length; i++)
    {
        //(11 1111)2=(63)10;
        random_secret[i] = rand() & 63;
    }
    return random_secret;
}