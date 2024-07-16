#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

int zetas[]={1, 16, 4, 64, 2, 32, 8, 128};
int bitreverse[]={0, 4, 2, 6, 1, 5, 3, 7};
int inversezeta[]={1,16,13,4,9,8,15,2};
int numinverse[]={0,1,9,6,13,7,3,5,15,2,12,14,10,4,11,8,16};

// int16_t barrett_reduce(int16_t a) {
//   int16_t t;
//   const int16_t v = ((1<<26) + 3329/2)/3329;

//   t  = ((int32_t)v*a + (1<<25)) >> 26;
//   t *= 3329;
//   return a - t;
// }

int mod(int a, int b) 
{
  int result = a % b;
  // Ensure the result is non-negative
  if (result < 0) {
      result += b;
  }
  return result;
}

// int16_t montgomery_reduce(int32_t a)
// {
//   int16_t t;

//   t = (int16_t)a*-3327;
//   t = (a - (int32_t)t*3329) >> 16;
//   return t;
// }

void cooleyturkey(int *a,int *b,int c ){
  int temp1 = *a;
  int temp2 = *b;
  temp2 = mod((c*temp2),17);
  *a = mod(temp1 + temp2,17) ; 
  *b = mod(temp1 - temp2,17);
}

void gentlemansande(int *a,int *b,int c ){
  int temp1 = *a;
  int temp2 = *b;
  *a=mod(temp1+temp2,17);
  *b=mod((temp1-temp2)*c,17);
}


int main()
{
  //     printf("%d\n",barrett_reduce(5000));
  //     printf("%d\n",montgomery_reduce(123456789));
    
    int src1[4]={8,1,7,2};
    int src2[4]={8,4,0,2};
    int dest[4];
    int zeta=2;
    for(int i = 0; i < 2; i++)
    {
        cooleyturkey(&src1[i],&src1[i+2],zetas[zeta]);
        cooleyturkey(&src2[i],&src2[i+2],zetas[zeta]);
    }
    zeta += 2;
    for(int i = 0; i < 1; i++)
    {
        cooleyturkey(&src1[i],&src1[i+1],zetas[zeta]);
        cooleyturkey(&src2[i],&src2[i+1],zetas[zeta]);
    }
    zeta+=2;
    for(int i = 0; i < 1; i++)
    {
        cooleyturkey(&src1[i+2],&src1[i+3],zetas[zeta]);
        cooleyturkey(&src2[i+2],&src2[i+3],zetas[zeta]);
    }

    int result[4]={0};


    for(int i=0;i<4;i++)
    {
      result[i]=mod(src1[i]*src2[i],17);
      printf("(%d",result[i]);
      if(i==0)
      {
        printf(")+");
      }else
      {
        printf("x^%d)",i);
        if(i!=3) printf("+");
      }
    }
    printf("\n\n\n\n");
    int count=0;
    for(int i = 0; i < 1; i++)
    {
        gentlemansande(&result[i+2],&result[i+3],inversezeta[zeta]);
    }
    zeta-=2;
    count+=2;
    for(int i = 0; i < 1; i++)
    {
        gentlemansande(&result[i],&result[i+1],inversezeta[zeta]);
    }
    zeta-=2;
    count+=2;
    for(int i = 0; i < 2; i++)
    {
        gentlemansande(&result[i],&result[i+2],inversezeta[zeta]);
    }

    for(int i=0;i<4;i++)
    {
      printf("(%d",mod(result[i]*numinverse[4],17));
      if(i==0)
      {
        printf(")+");
      }
      else{
         printf("x^%d)",i);
         if(i!=3) printf("+");
      }
    }

    printf("\n\n\n\n\n");
}