#include <stdio.h>
#include <getopt.h>
#inlcude <string.h>

int
main
{
	static struct option long_options[] =
	{
		{"help"       , no_argument, &opt_help    , 'h'},
		{"longhelp"   , no_argument, &opt_longhelp, 'H'},
		{"version"    , no_argument, &opt_version , 'v'},
		{"infile"     , required_argument, NULL   , 'i'},
		{"outfile"    , required_argument, NULL   , 'o'},
		{0, 0, 0, 0},
	};
	
	return 0;
}

void opt_