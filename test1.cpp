#include <pcre.h>
#include <stdio.h>
#include <string.h>
#include <gtest/gtest.h>

TEST(pcre, basics) {

  int const OVECCOUNT = 30; /* should be a multiple of 3 */

  int rc, i;
  int erroffset;
  int ovector[OVECCOUNT];
  const char* error;

  std::string pattern = "abc";
  std::string subject = "abbcabccbacca";

  int subject_length = (int)subject.size();

  pcre* re = pcre_compile(
    pattern.c_str(),              /* the pattern */
    0,                    /* default options */
    &error,               /* for error message */
    &erroffset,           /* for error offset */
    nullptr);

  rc = pcre_exec(
    re,                   /* the compiled pattern */
    nullptr,                 /* no extra data - we didn't study the pattern */
    subject.c_str(),              /* the subject string */
    subject_length,       /* the length of the subject */
    0,                    /* start at offset 0 in the subject */
    0,                    /* default options */
    ovector,              /* output vector for substring information */
    OVECCOUNT);           /* number of elements in the output vector */

  if (rc < 0) {
    switch(rc) {
      case PCRE_ERROR_NOMATCH:
        printf("No match\n");
        break;
      /*
        Handle other special cases if you like
        */
      default:
        printf("Matching error %d\n", rc);
        break;
    }
  } else {
    printf("\nMatch succeeded at offset %d\n", ovector[0]);
  }

  ASSERT_TRUE(rc >= 0);
  ASSERT_TRUE(ovector[0] == 4);

  pcre_free(re);     /* Release memory used for the compiled pattern */
}
