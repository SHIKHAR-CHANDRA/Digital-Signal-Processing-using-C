#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define SIG_LEN 320

extern double InputSignal_f32_1kHz_15kHz[SIG_LEN];
double output_signal[SIG_LEN];
void calc_running_sum(double *sig_src_arr, double *sig_dst_arr, int sig_len);

int main()
{

    FILE *input_sig_fptr, *output_sig_fptr;

    calc_running_sum((double *)&InputSignal_f32_1kHz_15kHz[0], (double *)&output_signal[0], (int) SIG_LEN);


    input_sig_fptr = fopen("input_signal.dat","w");
    output_sig_fptr = fopen("output_signal.dat","w");

    for(int i=0;i<SIG_LEN;i++)
    {
        fprintf(input_sig_fptr,"\n%f",InputSignal_f32_1kHz_15kHz[i]);
    }
    fclose(input_sig_fptr);


    for(int i=0;i<SIG_LEN;i++)
    {
        fprintf(output_sig_fptr,"\n%f",output_signal[i]);
    }
    fclose(output_sig_fptr);

    return 0;
}
void calc_running_sum(double *sig_src_arr, double *sig_dst_arr, int sig_len)
{
    for(int i=0;i<sig_len;i++)
    {
        sig_dst_arr[i] = sig_dst_arr[i-1]+sig_src_arr[i];

    }

}



