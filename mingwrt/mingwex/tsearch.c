/* $NetBSD: tsearch.c,v 1.4 1999/09/20 04:39:43 lukem Exp $
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
#include <search.h>
#include <stdlib.h>

__CRT_ALIAS void *__tsearch
(const void *key, node_t **rootp, int (*compar)(const void *, const void *))
{
  /* Find node identified by "key", within the tree referred to by "rootp",
   * or insert such datum node, if not already present.
   *
   * NOTE: node_t is defined as a structured data type, for internal use
   * when _SEARCH_PRIVATE is enabled; for public consumption, it becomes
   * an alias for "void", (assuming _SEARCH_PRIVATE is NOT enabled).
   */
  node_t *q;

  /* Cannot search from an invalid tree reference pointer, or without a
   * valid comparator function reference.
   */
  if( (rootp == NULL) || (compar == NULL) )
    return NULL;

  while( *rootp != NULL )		/* Knuth's T1: */
  {
    int cmp;				/* T2: */
    if( (cmp = (*compar)(key, (*rootp)->key)) == 0 )
      return *rootp;			/* we found it! */

    rootp = (cmp < 0)
      ? &(*rootp)->llink		/* T3: follow left branch */
      : &(*rootp)->rlink;		/* T4: follow right branch */
  }

  q = malloc( sizeof(node_t) );		/* T5: key not found */
  if( q != NULL )			/* make new node */
  {
    *rootp = q;				/* link new node to old */
    q->key = key;			/* initialize new node */
    q->llink = q->rlink = NULL;
  }
  return q;
}

void *tsearch
(const void *key, void **rootp, int (*compar)(const void *, const void *))
{ return __tsearch (key, (node_t **)(rootp), compar); }
