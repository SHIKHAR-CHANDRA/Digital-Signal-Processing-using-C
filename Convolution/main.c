#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define SIG_LEN 320
#define IMP_RES_LEN 29

extern double InputSignal_f32_1kHz_15kHz[SIG_LEN];
extern  double  Impulse_response[IMP_RES_LEN];
double output_signal[SIG_LEN+IMP_RES_LEN];
void convolution(double *sig_src_arr, double *sig_dest_arr, double *imp_res_arr, int sig_src_length, int imp_res_length);

int main()
{

    FILE *input_sig_fptr, *imp_rsp_fptr, *output_sig_fptr;

    convolution((double *) &InputSignal_f32_1kHz_15kHz[0], (double *) &output_signal[0], (double *) &Impulse_response[0], (int) SIG_LEN, (int) IMP_RES_LEN);


    input_sig_fptr = fopen("input_signal.dat","w");
    imp_rsp_fptr = fopen("impulse_response.dat","w");
    output_sig_fptr = fopen("output_signal.dat","w");

    for(int i=0;i<SIG_LEN;i++)
    {
        fprintf(input_sig_fptr,"\n%f",InputSignal_f32_1kHz_15kHz[i]);
    }
    fclose(input_sig_fptr);
    for(int i=0;i<IMP_RES_LEN;i++)
    {
        fprintf(imp_rsp_fptr,"\n%f",Impulse_response[i]);
    }
    fclose(imp_rsp_fptr);

    for(int i=0;i<SIG_LEN+IMP_RES_LEN;i++)
    {
        fprintf(output_sig_fptr,"\n%f",output_signal[i]);
    }
    fclose(output_sig_fptr);

    return 0;
}

void convolution(double *sig_src_arr, double *sig_dest_arr, double *imp_res_arr, int sig_src_length, int imp_res_length)
{

    int i,j;
    for(i=0;i<sig_src_length+imp_res_length;i++)
    {
        sig_dest_arr[i] = 0;
    }

    for(i=0;i<sig_src_length;i++)
    {
        for(j=0;j<imp_res_length;j++)
        {
            sig_dest_arr[i+j]= sig_dest_arr[i+j] + sig_src_arr[i]*imp_res_arr[j];

        }
    }



}

