#include <locale.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int
main(int argc, char * argv[])
{
  char *old_locale, *saved_locale;

  /* Get the name of the current locale.  */
  old_locale = setlocale(LC_ALL, NULL);

  /* Copy the name so it won’t be clobbered by setlocale. */
  saved_locale = strdup (old_locale);
  if (saved_locale == NULL)
    fprintf(stderr, "Out of memory\n");
  else
	  printf("old_locale: %s\n", old_locale);

  /* Now change the locale and do some stuff with it. */
  if (!setlocale(LC_ALL, "")) {
    fprintf(stderr, "Can't set the specified locale! "
            "Check LANG, LC_CTYPE, LC_ALL.\n");
    return 1;
  }
  else
  	 printf("new_locale: %s\n", setlocale(LC_ALL, NULL));

  /* Restore the original locale. */
  setlocale (LC_ALL, saved_locale);
  free (saved_locale);
}
