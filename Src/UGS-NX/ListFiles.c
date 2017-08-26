#include <io.h>
#include <stdio.h>
#include <string.h>
#include <minwindef.h>			// Def for MAX_PATH

static void process_all_files( const char *dir )
{
	char buffer[ MAX_PATH ]; /* or whatever the max length of a file */
	struct _finddata_t fd;
	long handle;

	/* show directory name */
//	printf( "processing directory %s\n", dir );

	/* find first file, add wild card to the directory */
	sprintf( buffer, "%s\\*.*", dir );
	handle = _findfirst( buffer, &fd );
	if( handle != -1 )
	{
		do
		{
			/* check if its a directory */
			if( ( fd.attrib & _A_SUBDIR ) == _A_SUBDIR )
			{
				/* yes, use recursion here, DONT do it for . and .. */
				if( strcmpi( fd.name, "." ) != 0 && strcmpi( fd.name, ".." ) != 0 )
				{
					sprintf( buffer, "%s\\%s", dir, fd.name );
					process_all_files( buffer );
				}
			}
			else
			{
				/* its a file, show its name */
				sprintf( buffer, "%s\\%s\n", dir, fd.name );
				printf( "%s", buffer );
			}
		} while( _findnext( handle, &fd ) == 0 );
		
		_findclose( handle );
	}
	else
	{
		printf("Error: _findfirst returned error, EXITING\n");
	}
}

int main(int argc, char *argv[])
{
	if(argc == 1)
	{
		process_all_files( "." );
	}
	else
	{
		process_all_files(argv[1]);
	}
	
	return 0;
}
 