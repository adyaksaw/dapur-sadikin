#include "jam.c"
#include "boolean.h"

int main()
{
    Second S;

    SetTime(&S,0);
    TulisSecond(S);

    while(SLT(S,10))
    {
        UpdateTime(&S);
        TulisSecond(S);
    }

    if (SEQ(S,10))
    {
        printf("%d Equal 9.\n",S);
    }
    if (SNEQ(S,9))
    {
        printf("%d Not Equal 10.\n",S);
    }


    while (SGT(S,0))
    {
        S = PrevSecond(S);
        TulisSecond(S);
    }

    SetTime(&S,10);
    TulisSecond(S);

    return 0;
}
