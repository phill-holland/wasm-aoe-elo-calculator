#include <vector>
#include <limits.h>

#ifndef _POINT
#define _POINT

class point
{
    bool init;

    std::vector<long> values;    
    std::vector<long> min, max;

    long dimensions;
    
public:
    long identity;

public:
    point(long dimensions) { reset(dimensions); }
    ~point() { }

    bool initalised() { return init; }
    void reset(long dimensions);

    void clear();
    
public:
    void set(long *points, unsigned long length = 0L);
    bool set(long value, unsigned long dimension);
    void set(long value);

    long get(unsigned long dimension);

    bool dominates(const point &source);

public:
    void copy(const point &source);
    bool equals(const point &source);
    bool inside(const point &min, const point &max);

    bool issame(long value);
};

#endif