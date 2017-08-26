#include <stdio.h>
#include <stdlib.h>

typedef struct  WAV_HEADER
{
char                RIFF[4];
int                 ChunkSize;
char                WAVE[4];
char                fmt[4];
int                 Subchunk1Size;
short int           AudioFormat;
short int           NumOfChan;
int                 SamplesPerSec;
int                 bytesPerSec;
short int           blockAlign;
short int           bitsPerSample;
int                 Subchunk2Size;
char                Subchunk2ID[4];
}wav_hdr;

int getFileSize(FILE *inFile);
int main(int argc,char *argv[])
{
//check startup conditions
if(argc >= 2); //we have enough arguments -- continue
else { printf("\nUSAGE: program requires a filename as an argument -- please try again\n"); exit(0);}

wav_hdr wavHeader;
FILE *wavFile;
int headerSize = sizeof(wav_hdr),filelength = 0;
wavFile = fopen(argv[1],"r");
if(wavFile == NULL)
{
    printf("Unable to open wave file\n");
    exit(EXIT_FAILURE);
}
fread(&wavHeader,headerSize,1,wavFile);
filelength = getFileSize(wavFile);
fclose(wavFile);
printf("\nWav file header information:\n");
printf("Filesize\t\t\t%d bytes\n",filelength);
printf("RIFF header\t\t\t%c%c%c%c\n",wavHeader.RIFF[0],wavHeader.RIFF[1],wavHeader.RIFF[2],wavHeader.RIFF[3]);
printf("WAVE     header\t\t\t%c%c%c%c\n",wavHeader.WAVE[0],wavHeader.WAVE[1],wavHeader.WAVE[2],wavHeader.WAVE[3]);
     printf("Subchunk1ID\t\t\t%c%c%c%c\n",wavHeader.fmt[0],wavHeader.fmt[1],wavHeader.fmt[2],wavHeader.fmt[3]);
printf("Chunk Size (based on bits used)\t%d\n",wavHeader.ChunkSize);
printf("Subchunk1Size\t\t\t%d\n",wavHeader.Subchunk1Size);
printf("Sampling Rate\t\t\t%d\n",wavHeader.SamplesPerSec); //Sampling frequency of the wav file
printf("Bits Per Sample\t\t\t%d\n",wavHeader.bitsPerSample); //Number of bits used per sample
printf("AudioFormat\t\t\t%d\n",wavHeader.AudioFormat);
printf("Number of channels\t\t%d\n",wavHeader.bitsPerSample);     //Number of channels (mono=1/sterio=2)
printf("Byte Rate\t\t\t%d\n",wavHeader.bytesPerSec);   //Number of bytes per second
printf("Subchunk2ID\t\t\t%c%c%c%c\n",wavHeader.Subchunk2ID[0],wavHeader.Subchunk2ID[1],wavHeader.Subchunk2ID[2],wavHeader.Subchunk2ID[3]);
printf("Subchunk2Size\t\t\t%d\n",wavHeader.Subchunk2Size);
printf("\n");
return 0;
}

int getFileSize(FILE *inFile)
{
int fileSize = 0;
fseek(inFile,0,SEEK_END);
fileSize=ftell(inFile);
fseek(inFile,0,SEEK_SET);
return fileSize;
}
