// Reference for the Math: https://www.youtube.com/watch?v=NKMHhm2Zbkw&t=613s

#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE *file = fopen("sir_data.dat", "w");

    float step_size = 0.001;
    int N = 7000;
    float S[N], I[N], R[N];

    int time[N];  

    int totalPopulation = 1;
    float S0 = 0.99;
    float I0 = 1 - 0.99;
    float R0 = 0.0;

    S[0] = S0;
    I[0] = I0;
    R[0] = R0;

    float r = 2.9; // Transmission Rate -- Hand Washing, Social Distancing etc
    float a = 1; // Moving from Infected to Recovered -- Cannot really be affected

    float basic_reproductive_no = (r * S0) / a;

    float dS1, dS2, dS3, dS4, dS;
    float dI1, dI2, dI3, dI4, dI;
    float dR1, dR2, dR3, dR4, dR;

    for (int i = 0; i <= N; i++)
    {
        time[i] = i;

        printf("%d\t%f\t%f\t%f\n", time[i], S[i], I[i], R[i]);
        fprintf(file, "%d\t%f\t%f\t%f\n", time[i], S[i], I[i], R[i]);

        dS1 = step_size * (-r * I[i] * S[i]);
        dI1 = step_size * ((r * I[i] * S[i]) - a * I[i]);
        dR1 = step_size * a * I[i];

        dS2 = step_size * (-r * (I[i] + (dI1 / 2)) * (S[i] + (dS1 / 2)));
        dI2 = step_size * ((r * (I[i] + (dI1 / 2)) * (S[i] + (dS1 / 2))) - a * (I[i] + (dI1 / 2)));
        dR2 = step_size * a * (I[i] + (dI1 / 2));

        dS3 = step_size * (-r * (I[i] + (dI2 / 2)) * (S[i] + (dS2 / 2)));
        dI3 = step_size * ((r * (I[i] + (dI2 / 2)) * (S[i] + (dS2 / 2))) - a * (I[i] + (dI2 / 2)));
        dR3 = step_size * a * (I[i] + (dI2 / 2));

        dS4 = step_size * (-r * (I[i] + dI3) * (S[i] + dS3));
        dI4 = step_size * ((r * (I[i] + dI3) * (S[i] + dS3)) - a * (I[i] + dI3));
        dR4 = step_size * a * (I[i] + dI3);

        dS = (dS1 + (2*dS2) + (2*dS3) + dS4) / 6;
        dI = (dI1 + (2*dI2) + (2*dI3) + dI4) / 6;
        dR = (dR1 + (2*dR2) + (2*dR3) + dR4) / 6;

        S[i+1] = S[i] + dS;
        I[i+1] = I[i] + dI;
        R[i+1] = R[i] + dR;

    }
    printf("Basic Reproductive Number: %f\n", basic_reproductive_no);
}