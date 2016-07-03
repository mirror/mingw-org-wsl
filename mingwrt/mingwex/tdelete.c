/* $NetBSD: tdelete.c,v 1.3 1999/09/20 04:39:43 lukem Exp $
 *
 *
 * Tree search generalized from Knuth (6.2.2) Algorithm T just like
 * the AT&T man page says; tdelete based on Knuth's Algorithm D.
 *
 * Written by reading the System V Interface Definition, not the code.
 *
 * Totally public domain.
 *
 */
#define _SEARCH_PRIVATE
#include <search.h>
#include <stdlib.h>

__CRT_ALIAS void *__tdelete
(const void *key, node_t **rootp, int (*compar)(const void *, const void *))
{
  /* Delete node with specified "key", from tree referred to by "rootp".
   *
   * NOTE: node_t is defined as a structured data type, for internal use
   * when _SEARCH_PRIVATE is enabled; for public consumption, it becomes
   * an alias for "void", (assuming _SEARCH_PRIVATE is NOT enabled).
   */
  int cmp;
  node_t *p, *q, *r;

  if( (rootp == NULL) || ((p = *rootp) == NULL) || (compar == NULL) )
    return NULL;

  while( (cmp = (*compar)(key, (*rootp)->key)) != 0 )
  {
    rootp = (cmp < 0)
      ? &(p = *rootp)->llink		/* follow llink branch */
      : &(p = *rootp)->rlink;		/* follow rlink branch */

    if (*rootp == NULL)
      return NULL;			/* key not found */
  }
  r = (*rootp)->rlink;			/* D1: */
  if( (q = (*rootp)->llink) == NULL )	/* Left NULL? */
    q = r;
  else if( r != NULL ) 			/* Right link is NULL? */
  { if( r->llink == NULL ) 		/* D2: Find successor */
    { r->llink = q;
      q = r;
    }
    else				/* D3: Find NULL link */
    {
      for( q = r->llink; q->llink != NULL; q = r->llink )
	r = q;
      r->llink = q->rlink;
      q->llink = (*rootp)->llink;
      q->rlink = (*rootp)->rlink;
    }
  }
  free(*rootp);				/* D4: Free node */
  *rootp = q;				/* link parent to new node */
  return p;
}

void *tdelete
(const void *key, void **rootp, int (*compar)(const void *, const void *))
{ return __tdelete (key, (node_t **)(rootp), compar); }
