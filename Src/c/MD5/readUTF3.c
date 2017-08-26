#include <stdio.h>
#include <string.h>

void ReadUTF8(FILE* fp)
{
    unsigned char iobuf[255] = {0};
    while( fgets((char*)iobuf, sizeof(iobuf), fp) )
    {
            size_t len = strlen((char *)iobuf);
            if(len > 1 &&  iobuf[len-1] == '\n')
                iobuf[len-1] = 0;
            len = strlen((char *)iobuf);
            printf("(%d) \"%s\"  ", len, iobuf);
            if( iobuf[0] == '\n' )
                printf("Yes\n");
            else
                printf("No\n");
    }
}
void ReadUTF16BE(FILE* fp)
{
}
void ReadUTF16LE(FILE* fp)
{
}
int main()
{
    FILE* fp = fopen("e:\\src\\Python\\AllFiles.txt", "r");
    if( fp != NULL)
    {
        // see http://en.wikipedia.org/wiki/Byte-order_mark for explaination of the BOM
        // encoding
        unsigned char b[3] = {0};
        fread(b,1,2, fp);
        if( b[0] == 0xEF && b[1] == 0xBB)
        {
            fread(b,1,1,fp); // 0xBF
            ReadUTF8(fp);
        }
        else if( b[0] == 0xFE && b[1] == 0xFF)
        {
            ReadUTF16BE(fp);
        }
        else if( b[0] == 0 && b[1] == 0)
        {
            fread(b,1,2,fp); 
            if( b[0] == 0xFE && b[1] == 0xFF)
                ReadUTF16LE(fp);
        }
        else
        {
            // we don't know what kind of file it is, so assume its standard
            // ascii with no BOM encoding
            rewind(fp);
            ReadUTF8(fp);
        }
    }        
    fclose(fp);
}
