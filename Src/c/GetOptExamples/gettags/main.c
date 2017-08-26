/*
gettags
main.c
(c)2012 Kevin Boone
*/
#include <stdio.h>
#include <getopt.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
//#include <unistd.h>
//#include "types.h"
#include "tag_reader.h"
/**
Prints a short usage message
*/
void print_short_usage(const char *argv0)
{
	printf ("Usage: %s -[vhds] [-c name] [-e name] {files...}\n", argv0);
	printf ("\"%s --longhelp\" for full details\n", argv0);
}


/**
Prints a detailed usage message
*/
void print_long_usage(const char *argv0)
{
	printf ("Usage: %s [options]\n", argv0);
	printf ("-c, --common-name [name] show tag matching only this common name\n");
	printf ("-c help                  lists common names\n");
	printf ("-d, --debug              show debugging data\n");
	printf ("-e, --exact-name [name]  show tag matching only this exact name\n");
	printf ("--longhelp               show detailed usage\n");
	printf ("-h, --help               show brief usage\n");
	printf ("-s, --script             script mode\n");
	printf ("-v, --version            show version\n");
}


/**
show_tag
*/
void show_tag (const Tag *tag)
{
	printf ((char *)tag->frameId);
	printf (" ");
	if (tag->type == TAG_TYPE_TEXT)
		printf ((char*)tag->data);
	else
		printf ("(binary)");
	printf ("\n");
}


const char *make_prefix (bool ok, bool opt_script)
{
	if (!opt_script) return "";
	if(ok)return "OK ";
	else  return "ERROR ";
//	return (ok) ? OK : ERR;
}


/**
do_file
*/
void do_file (const char *argv0, const char *filename, bool opt_script,
              TagCommonID common_id, const char *exact_name)
{
	TagData *tag_data = NULL;
	TagResult r = tag_get_tags (filename, &tag_data);
	switch (r)
	{
	case TAG_READERROR:
		fprintf (stderr, "%s%s: Can't read file '%s'\n",
			make_prefix(false, opt_script), argv0, filename);
		break;
	case TAG_TRUNCATED:
		fprintf (stderr, "%s%s, Tag data is incomplete in '%s'\n",
			make_prefix(false, opt_script), argv0, filename);
		break;
	case TAG_OUTOFMEMORY:
		fprintf (stderr, "%s%s: Out of memory processing file '%s'\n",
			make_prefix(false, opt_script), argv0, filename);
		break;
	case TAG_UNSUPFORMAT:    // no break intentional
	case TAG_NOID3V2:        // no break intentional
	case TAG_NOVORBIS:
		fprintf (stderr, "%s%s: Unsupported tag format in file '%s'\n",
			make_prefix(false, opt_script), argv0, filename);
		break;
	case TAG_OK:
	{
		// Only if we get here should we proceed
		if (strlen (exact_name) > 0)
		{
			const char *s = (char *)tag_get_by_id (tag_data, exact_name);
			if (s)
				printf ("%s%s\n", make_prefix(true, opt_script), s);
			else
				printf ("%sTag not found", make_prefix(false, opt_script));
		}
		else if (common_id != -1)
		{
			const unsigned char *s = tag_get_common(tag_data, common_id);
		if (s)
			printf ("%s%s\n", make_prefix(true, opt_script), s);
		else
			printf ("%sTag not found", make_prefix(false, opt_script));
		}
		else
		{
		if (opt_script) printf ("OK\n");
			Tag *t = tag_data->tag;
		while (t)
		{
			show_tag (t);
			t = t->next;
		}
	}
	}
	break;
	}
	tag_free_tag_data (tag_data);
}

/**
common_name_to_common_id
*/
TagCommonID common_name_to_common_id (const char *common_name)
{
	if (strcmp (common_name, "title")    == 0) return TAG_COMMON_TITLE;
	if (strcmp (common_name, "album")    == 0) return TAG_COMMON_ALBUM;
	if (strcmp (common_name, "artist")   == 0) return TAG_COMMON_ARTIST;
	if (strcmp (common_name, "composer") == 0) return TAG_COMMON_COMPOSER;
	if (strcmp (common_name, "year")     == 0) return TAG_COMMON_YEAR;
	if (strcmp (common_name, "genre")    == 0) return TAG_COMMON_GENRE;
	if (strcmp (common_name, "track")    == 0) return TAG_COMMON_TRACK;
	if (strcmp (common_name, "comment")  == 0) return TAG_COMMON_COMMENT;
	return -1;
}


/**
main
*/
int main (int argc, char **argv)
{
	static bool opt_version  = false;
	static bool opt_help     = false;
	static bool opt_longhelp = false;
	static bool opt_debug    = false;
	static bool opt_script   = false;
	char opt_common_name[32];
	char opt_exact_name[32];

	static struct option long_options[] =
	{
		{"help"       , no_argument, &opt_help    ,  0 },
		{"longhelp"   , no_argument, &opt_longhelp,  0 },
		{"version"    , no_argument, &opt_version , 'v'},
		{"script"     , no_argument, &opt_script  , 's'},
		{"debug"      , no_argument, &opt_debug   , 'v'},
		{"common-name", required_argument, NULL   , 'c'},
		{"exact-name" , required_argument, NULL   , 'e'},
		{0, 0, 0, 0},
	};

	opt_common_name[0] = 0;
	opt_exact_name[0]  = 0;

	while (1)
	{
		int option_index = 0;
		int opt = getopt_long (argc, argv, "?vhdc:e:s", long_options,
                             &option_index);
		if (opt == -1) break;
		switch (opt)
		{
		case 0: // Long option
			{
			if (strcmp (long_options[option_index].name, "longhelp") == 0)
			{
			opt_longhelp = true;
			}
			else if (strcmp (long_options[option_index].name, "help") == 0)
			{
				opt_help = true;
			}
			else if (strcmp (long_options[option_index].name, "debug") == 0)
			{
				opt_debug = true;
			}
			else if (strcmp (long_options[option_index].name, "script") == 0)
			{
				opt_script = true;
			}
			else if (strcmp (long_options[option_index].name, "common-name") == 0)
			{
				strncpy (opt_common_name, optarg, sizeof (opt_common_name));
			}
			else if (strcmp (long_options[option_index].name, "exact-name") == 0)
			{
				strncpy (opt_exact_name, optarg, sizeof (opt_exact_name));
			}
	} // End of long options
			break;
		case 'v':
			opt_version = true;
			break;
		case 'd':
			opt_debug = true;
			break;
		case 's':
			opt_script = true;
			break;
		case '?':
		case 'h':
			opt_help = true;
			break;
		case 'c':
			strncpy (opt_common_name, optarg, sizeof (opt_common_name));
			break;
		case 'e':
			strncpy (opt_exact_name, optarg, sizeof (opt_exact_name));
			break;
		}
   }

	if (opt_version)
	{
		printf ("taginfo version %s\n(c)2011-2012 Kevin Boone\n", VERSION);
		exit (0);
	}

	if (opt_help)
	{
		print_short_usage(argv[0]);
		exit (0);
	}

	if (opt_longhelp)
	{
		print_long_usage(argv[0]);
		exit (0);
	}

	if (opt_debug)
		tag_debug = true;

	TagCommonID common_id = -1;
	if (strlen (opt_common_name) > 0)
	{
		if (strcmp (opt_common_name, "help") == 0)
		{
			printf ("%s: common names: title album artist composer "
						"year genre track comment\n", argv[0]);
			return 0;
		}
		common_id = common_name_to_common_id (opt_common_name);
		if (common_id == -1)
		{
			fprintf (stderr, "%s: unknown common name '%s'\n",
						argv[0], opt_common_name);
			fprintf (stderr, "'%s --common-name help' for a list\n", argv[0]);
			return -1;
		}
	}

	if (common_id != -1 && strlen (opt_exact_name) > 0)
	{
		fprintf (stderr,
					"'%s: ignoring common name because exact name was supplied\n", argv[0]);
	}

	if (optind == argc)
	{
		fprintf (stderr,
					"%s%s: No files specified\n", make_prefix (false, opt_script), argv[0]);
	}
	else
	{
		int i;
		for (i = optind; i < argc; i++)
		{
			do_file (argv[0], argv[i], opt_script, common_id, opt_exact_name);
		}
	}

	return 0;
}
