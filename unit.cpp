#include <iostream>
#include <cstdlib>

#define dEndl endl<<endl

using namespace std;

void fillinc(int start, int step, int n, int a[])
{
    for(int i=0;i<n;++i)
    {
        a[i]=start + step*i;
    }
}

void filldec(int start, int step, int n, int a[])
{
    for(int i=0;i<n;++i)
    {
        a[i]=start - step*i;
    }
}

void fillrand(int n, int range, int a[])
{
    for(int i=0;i<n;++i)
    {
        a[i]=rand()%range;
    }
}

int checksum(int n, int a[])
{
    int sum = 0;
    for(int i=0;i<n;++i)
    {
        sum += a[i];
    }
    return sum;
}

int runnumber(int n, int a[])
{
    int numb = 1;
    for(int i=0;i<n-1;++i)
    {
        if (a[i+1]<a[i]) (numb++, cout << "Error " << a[i] << " " << a[i+1] << endl);
    }
    return numb;
}

void printmas(int n, int a[])
{
    for(int i=0;i<n;++i)
    {
        cout<<a[i]<<" ";
    }
    cout << dEndl;
}
