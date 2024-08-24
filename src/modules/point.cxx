module;
#include <vector>
#include <limits.h>

export module point;

export class point
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

void point::reset(long dimensions)
{
    init = false;

    this->dimensions = dimensions;

    identity = 0L;

    values.resize(dimensions);
    min.resize(dimensions);
    max.resize(dimensions);

    for(long i=0L; i < dimensions; ++i)
    {
        values[i] = 0L;
        min[i] = LONG_MIN;
        max[i] = LONG_MAX;
    }

    init = true;
}

void point::clear()
{
    for(long i=0L; i < dimensions; ++i)
    {
        values[i] = 0L;
        min[i] = LONG_MIN;
        max[i] = LONG_MAX;
    }
}


void point::set(long *points, unsigned long length)
{
    long min = length;
    if(min == 0L) min = dimensions;
    if(min > dimensions) min = dimensions;

    for(long i = 0L; i < min; ++i)
    {
        values[i] = points[i];
    }
}

bool point::set(long value, unsigned long dimension)
{
    if(dimension >= dimensions) return false;
    if(dimension < 0L) return false;

    values[dimension] = value;

    return true;
}

void point::set(long value)
{
    for(long i = 0L; i < dimensions; ++i)
    {
        values[i] = 0L;
        min[i] = LONG_MIN;
        max[i] = LONG_MAX;
    }
}

long point::get(unsigned long dimension)
{
    if(dimension >= dimensions) return -1L;
    if(dimension < 0L) return -1L;

    return values[dimension];
}

bool point::dominates(const point &source)
{
    bool any = false;
    for (int i = 0; i < dimensions; ++i)
    {
        if(source.values[i] > values[i]) return false;
        any |= (source.values[i] < values[i]);
    }

    return any;
}

void point::copy(const point &source)
{
    if (dimensions <= source.dimensions)
    {
        long _min = dimensions;
        if(source.dimensions < _min) _min = source.dimensions;

        for(long i=0L; i < _min; ++i)
        {
            values[i] = source.values[i];
            min[i] = source.min[i];
            max[i] = source.max[i];
        }
    
        dimensions = source.dimensions;
        identity = source.identity;
    }
}

bool point::equals(const point &source)
{
    if (dimensions < source.dimensions) return false;
    
    long min = dimensions;
    if(source.dimensions < min) min = source.dimensions;

    for(long i=0L; i < min; ++i)
    {
        if(values[i] != source.values[i]) return false;
    }
    
    return true;
}

bool point::inside(const point &min, const point &max)
{
    if(min.dimensions != dimensions) return false;
    if(max.dimensions != dimensions) return false;

    for(long i=0L; i < dimensions; ++i)
    {
        if(values[i] < min.values[i]) return false;
        if(values[i] > max.values[i]) return false;
    }

    return true;
}

bool point::issame(long value)
{
    for(long i=0L; i < dimensions; ++i)
    {
        if(values[i] != value) return false;
    }

    return true;
}
