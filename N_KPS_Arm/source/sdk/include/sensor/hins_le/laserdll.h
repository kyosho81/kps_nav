#ifndef LASERDLL_H
#define LASERDLL_H

// #define uint32_t unsigned int

class LASERDLLSHARED_EXPORT
{

public:
    void MeasureDataFilterDelete(
    uint32_t *InBuf, uint32_t InSize, uint32_t Deviation, uint32_t PointNum);
};

#endif // LASERDLL_H
