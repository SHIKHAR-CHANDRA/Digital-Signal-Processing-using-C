#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define SIG_LEN 501

extern double _501pts_20Hz_sig_rex[SIG_LEN];
extern double _501pts_20Hz_sig_imx[SIG_LEN];
double output_rex[SIG_LEN];
double output_imx[SIG_LEN];

void calc_complex_dft(double *sig_src_time_rex,
                      double *sig_src_time_imx,
                      double *sig_dest_freq_rex,
                      double *sig_dest_freq_imx,
                      int sig_length);

int main()
{
    FILE *fptr1,*fptr2,*fptr3,*fptr4;

    calc_complex_dft((double *)&_501pts_20Hz_sig_rex[0],
                      (double *)&_501pts_20Hz_sig_imx[0],
                      (double *)&output_rex[0],
                      (double *)&output_imx[0],
                      (int) SIG_LEN);

    fptr1 = fopen("input_rex.dat","w");
    fptr2 = fopen("input_imx.dat","w");
    fptr3 = fopen("output_rex.dat","w");
    fptr4 = fopen("output_imx.dat","w");

    for(int i=0;i<SIG_LEN;i++)
    {
        fprintf(fptr1,"\n%f",_501pts_20Hz_sig_rex[i]);
        fprintf(fptr2,"\n%f",_501pts_20Hz_sig_imx[i]);
        fprintf(fptr3,"\n%f",output_rex[i]);
        fprintf(fptr4,"\n%f",output_imx[i]);
    }
    fclose(fptr1);
    fclose(fptr2);
    fclose(fptr3);
    fclose(fptr4);

    return 0;
}

void calc_complex_dft(double *sig_src_time_rex,
                      double *sig_src_time_imx,
                      double *sig_dest_freq_rex,
                      double *sig_dest_freq_imx,
                      int sig_length)
{
    double PI = 3.14159265;
    double SR, SI;
    for(int k=0; k<sig_length-1;k++)
    {
        for(int i=0;i<sig_length-1;i++)
        {
            SR = cos(2*PI*k*i/sig_length);
            SI = -sin(2*PI*k*i/sig_length);
            sig_dest_freq_rex[k] = sig_dest_freq_rex[k] + sig_src_time_rex[i]*SR - sig_src_time_imx[i]*SI;
            sig_dest_freq_imx[k] = sig_dest_freq_imx[k] + sig_src_time_imx[i]*SI - sig_src_time_imx[i]*SR;

        }
    }



}

