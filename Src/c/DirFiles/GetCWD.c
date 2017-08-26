/* GetCWD.c 
 * This program places the name of the current directory in the 
 * buffer array, then displays the name of the current directory 
 * on the screen. Specifying a length of _MAX_PATH leaves room 
 * for the longest legal path name. 
 */ 

#include <direct.h> 
#include <stdlib.h> 
#include <stdio.h> 
 
int main( void ) 
{ 
  char buffer[_MAX_PATH];  
  printf("\n\nGetCWD: Places the current working directory into a Buffer array.\n\n");
  
  /* Get the current working directory: */ 
  if( _getcwd( buffer, _MAX_PATH ) == NULL ) 
    perror( "_getcwd error" ); 
  else 
    printf( "%s\n", buffer );
  return 0;
}
