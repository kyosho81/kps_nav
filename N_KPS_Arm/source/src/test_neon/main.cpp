 
#include <stdio.h>
#include <string.h>
#include <arm_neon.h>
 
#include<sys/time.h>
#define TIME_START(num) struct timeval tv_start##num,tv_end##num;gettimeofday(&tv_start##num,NULL);
#define TIME_END(num,tag) gettimeofday(&tv_end##num,NULL);\
    printf("[%s-%d]:%s Cost=%fms\n",__func__,__LINE__,#tag,((tv_end##num.tv_sec-tv_start##num.tv_sec)*1e6+(tv_end##num.tv_usec-tv_start##num.tv_usec))/1000.0f);\
    gettimeofday(&tv_start##num,NULL);
 
class Mat{
public:
    Mat(int wh,int hh){
        w=wh;
        h=hh;
        size=w*h;
        data=new unsigned char [w*h];
    }
    ~Mat(){
        delete [] data;
    }
    void clear(unsigned char val){
        memset(data,val,size);
    }
    int w;
    int h;
    int size;
    unsigned char *data;
};
 
int matCmp(Mat &mat0,Mat &mat1)
{
    if(mat0.w!=mat1.w||mat0.h!=mat1.h){
        return 0;
    }
    int w=mat0.w;
    int h=mat0.h;
    for(int j=0;j<h;j++){
        for(int i=0;i<w;i++){
            int idx=j*w+i;
            if(mat0.data[idx]!=mat1.data[idx]){
                return 0;
            }
        }
    }
    return 1;
}
 
void matAdd(Mat &mat0,Mat &mat1,Mat &dst)
{
    if(mat0.w!=mat1.w||mat0.h!=mat1.h){
        return;
    }
    int w=mat0.w;
    int h=mat0.h;
    for(int j=0;j<h;j++){
        for(int i=0;i<w;i++){
            int idx=j*w+i;
            dst.data[idx]=mat0.data[idx]+mat1.data[idx];
        }
    }
}
 
//uint8x8_t vld1_u8 (const uint8_t * __a);
//uint8x8_t vadd_u8 (uint8x8_t __a, uint8x8_t __b);
//void vst1_u8 (uint8_t * __a, uint8x8_t __b);
void vmatAdd(Mat &mat0,Mat &mat1,Mat &dst)
{
    if(mat0.w!=mat1.w||mat0.h!=mat1.h){
        return;
    }
    int w=mat0.w;
    int h=mat0.h;
    uint8x8_t vmat0,vmat1,vdst;
    for(int j=0;j<h;j++){
        int jdx=j*w;
        for(int i=0;i<w;i+=8){
            int idx=jdx+i;
            vmat0=vld1_u8(mat0.data+idx);
            vmat1=vld1_u8(mat1.data+idx);
            vdst=vadd_u8(vmat0,vmat1);
            vst1_u8(dst.data+idx,vdst);
        }
    }
}
 
//uint8x16_t vld1q_u8 (const uint8_t * __a);
//uint8x16_t vaddq_u8 (uint8x16_t __a, uint8x16_t __b);
//void vst1q_u8 (uint8_t * __a, uint8x16_t __b);
void vmatAddq(Mat &mat0,Mat &mat1,Mat &dst)
{
    if(mat0.w!=mat1.w||mat0.h!=mat1.h){
        return;
    }
    int w=mat0.w;
    int h=mat0.h;
    uint8x16_t vmat0,vmat1,vdst;
    for(int j=0;j<h;j++){
        int jdx=j*w;
        for(int i=0;i<w;i+=16){
            int idx=jdx+i;
            vmat0=vld1q_u8(mat0.data+idx);
            vmat1=vld1q_u8(mat1.data+idx);
            vdst=vaddq_u8(vmat0,vmat1);
            vst1q_u8(dst.data+idx,vdst);
        }
    }
}
 
int main(int argc,char **argv)
{
#if __arm__
	int i = 1;
#endif
    Mat mat0(3840,2160);
    Mat mat1(3840,2160);
    mat0.clear(100);
    mat1.clear(50);
    Mat dst(3840,2160);
    Mat dst1(3840,2160);
    Mat dst2(3840,2160);
 
    TIME_START(0);
    matAdd(mat0,mat1,dst);
    TIME_END(0,matAdd);
    vmatAdd(mat0,mat1,dst1);
    TIME_END(0,vmatAdd);
    vmatAddq(mat0,mat1,dst2);
    TIME_END(0,vmatAddq);
 
    if(matCmp(dst,dst1)){
        printf("dst=dst1\n");
    }
    else{
        printf("dst!=dst1\n");
    }
 
    if(matCmp(dst,dst2)){
        printf("dst=dst2\n");
    }
    else{
        printf("dst!=dst2\n");
    }
 
    return 0;
}

