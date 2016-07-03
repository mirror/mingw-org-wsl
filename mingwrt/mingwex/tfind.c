/* $NetBSD: tfind.c,v 1.3.18.2 2005/03/23 11:12:21 tron Exp $
 *
 *
 * Tree search generalized from Knuth (6.2.2) Algorithm T just like
 * the AT&T man page says.
 *
 * Written by reading the System V Interface Definition, not the code.
 *
 * Totally public domain.
 *
 */
#define _SEARCH_PRIVATE
#include <stdlib.h>
#include <search.h>

__CRT_ALIAS void *__tfind
(const void *key, node_t *const *rootp, int (*compar)(const void *, const void *))
{
  /* Find node with specified "key", within tree referred to by "rootp";
   * return NULL if not found, (or if either "rootp" or "compar" is not
   * a valid pointer).
   *
   * NOTE: node_t is defined as a structured data type, for internal use
   * when _SEARCH_PRIVATE is enabled; for public consumption, it becomes
   * an alias for "void", (assuming _SEARCH_PRIVATE is NOT enabled).
   */
  if( (rootp == NULL) || (compar == NULL) )
    return NULL;

  while (*rootp != NULL)	/* Knuth's T1: */
  {
    int cmp;			/* T2: */
    if( (cmp = (*compar)(key, (*rootp)->key)) == 0 )
      return *rootp;		/* key found */

    rootp = (cmp < 0)
      ? &(*rootp)->llink	/* T3: follow left branch */
      : &(*rootp)->rlink; 	/* T4: follow right branch */
  }
  return NULL;			/* key not found */
}

void *tfind
(const void *key, void *const *rootp, int (*compar)(const void *, const void *))
{ return __tfind (key, (node_t *const *)(rootp), compar); }
