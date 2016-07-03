/* $NetBSD: twalk.c,v 1.2 1999/09/16 11:45:37 lukem Exp $
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

static __MINGW_ATTRIB_NONNULL(1) __MINGW_ATTRIB_NONNULL(2)
void trecurse (const node_t *, void (*)(const void *, VISIT, int), int);

static void trecurse
( const node_t *root, void (*action)(const void *, VISIT, int), int level)
{
  /* Recursively walk the nodes of a tree, performing the specified
   * action as each node is traversed, and as appropriate for each
   * phase of traversal.
   */
  if( (root->llink == NULL) && (root->rlink == NULL) )
    (*action) (root, leaf, level);

  else
  { (*action) (root, preorder, level);
    if( root->llink != NULL )
      trecurse (root->llink, action, level + 1);
    (*action) (root, postorder, level);
    if( root->rlink != NULL)
      trecurse (root->rlink, action, level + 1);
    (*action) (root, endorder, level);
  }
}

void twalk (const void *root, void (*action)(const void *, VISIT, int))
{
  /* Walk the nodes of a tree, delegating to the local recursive
   * helper function, to invoke the specified action on each node
   * in turn, as appropriate in each phase of traversal.
   */
  if( (root != NULL) && (action != NULL) )
    trecurse (root, action, 0);
}
