#include "CountMinSketch.hpp"

countMinSketch::countMinSketch() {
    b=ceil(2.71828/0.005);
    l=ceil(log(1/0.05));
    cms=new int *[l];
    for(int i=0; i<l; i++)
        cms[i]=new int[b];
    for(int i=0; i<l; i++)
        for(int j=0; j<b; j++)
            cms[i][j]=0;
}

countMinSketch::~countMinSketch() {
    for(int i=0; i<l; i++)
        delete [] cms[i];
    delete cms;
}

void countMinSketch::inc(char *x) {
    unsigned h1=hash1(x, strlen(x));
    unsigned h2=hash2(x, strlen(x));
    for (int i=0; i<l; i++)
        (cms[i][(h1+i*h2)%b])++;
}

int countMinSketch::cnt(char *x) {
    int c=INT_MAX, val;
    unsigned h1=hash1(x, strlen(x));
    unsigned h2=hash2(x, strlen(x));
    for (int i=0; i<l; i++) {
        val=cms[i][(h1+i*h2)%b];
        if(val<c)
            c=val;
    }
    return c;
}

unsigned hash1(void *str, int len) {
    unsigned char *s=(unsigned char *)str;
    unsigned h=0;
    for (int i=0; i<len; i++)
        h=33*h^s[i];
    return h;
}

unsigned hash2(void *str, int len) {
    unsigned char *s=(unsigned char *)str;
    unsigned h=0;
    for (int i=0; i<len; i++)
        h^=(h<<5)+(h>>2)+s[i];
    return h;
}
