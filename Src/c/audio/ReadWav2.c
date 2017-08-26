#include <stdio.h>
#include "ReadWav2.h"
main()
{
    int16_t *samples = NULL;
    wavread("track.wav", &samples);
    printf("No. of channels: %d\n",     header->num_channels);
    printf("Sample rate:     %d\n",     header->sample_rate);
    printf("Bit rate:        %dkbps\n", header->byte_rate*8 / 1000);
    printf("Bits per sample: %d\n\n",   header->bps);
    printf("Sample 0:        %d\n",     samples[0]);
    printf("Sample 1:        %d\n",     samples[1]);
    // Modify the header values & samples before writing the new file
    free(header);
    free(samples);
}
