#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define SIG_LEN 320

extern double _320_pts_ecg_IMX[SIG_LEN];
extern double _320_pts_ecg_REX[SIG_LEN];
double output_mag[SIG_LEN];
double output_phase[SIG_LEN];

void rect_to_polar(double *sig_src_rex_arr,double *sig_src_imx_arr,double *sig_out_mag_arr, double *sig_out_phase_arr, int sig_length);

int main()
{
    FILE *fptr1,*fptr2,*fptr3,*fptr4;

    rect_to_polar((double *)&_320_pts_ecg_REX[0],(double *)&_320_pts_ecg_IMX[0], (double *)&output_mag[0], (double *)&output_phase[0], (int) SIG_LEN);

    fptr1 = fopen("input_rex.dat","w");
    fptr2 = fopen("input_imx.dat","w");
    fptr3 = fopen("output_mag.dat","w");
    fptr4 = fopen("output_phase.dat","w");

    for(int i=0;i<SIG_LEN;i++)
    {
        fprintf(fptr1,"\n%f",_320_pts_ecg_REX[i]);
        fprintf(fptr2,"\n%f",_320_pts_ecg_IMX[i]);
        fprintf(fptr3,"\n%f",output_mag[i]);
        fprintf(fptr4,"\n%f",output_phase[i]);
    }
    fclose(fptr1);
    fclose(fptr2);
    fclose(fptr3);
    fclose(fptr4);

    return 0;
}

void rect_to_polar(double *sig_src_rex_arr,double *sig_src_imx_arr,double *sig_out_mag_arr, double *sig_out_phase_arr, int sig_length)
{
    double PI = 3.14159265358979f;
    int k;
    for(k=0;k<sig_length;k++)
    {
        sig_out_mag_arr[k] = sqrt(powf(sig_src_rex_arr[k],2)+powf(sig_src_imx_arr[k],2));
        if (sig_src_rex_arr[k] == 0)
        {
            sig_src_rex_arr[k] = pow(10,-20);
            sig_out_phase_arr[k] = atan(sig_src_imx_arr[k]/sig_src_rex_arr[k]);
        }
        if ((sig_src_rex_arr[k]<0)&&(sig_src_imx_arr[k]<0))
        {
            sig_out_phase_arr[k] = sig_out_phase_arr[k] - PI;
        }
        if ((sig_src_rex_arr[k]<0)&&(sig_src_imx_arr[k]>=0))
        {
            sig_out_phase_arr[k] = sig_out_phase_arr[k] + PI;
        }
    }
}
