/**
 * @file tsearch.c
 * @copy 2012 MinGW.org project
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */
/*	$NetBSD: tsearch.c,v 1.4 1999/09/20 04:39:43 lukem Exp $	*/

/*
 * Tree search generalized from Knuth (6.2.2) Algorithm T just like
 * the AT&T man page says.
 *
 * The node_t structure is for internal use only, lint doesn't grok it.
 *
 * Written by reading the System V Interface Definition, not the code.
 *
 * Totally public domain.
 */

#include <assert.h>
#define _SEARCH_PRIVATE
#include <search.h>
#include <stdlib.h>


/* find or insert datum into search tree */
void *
tsearch(const void * __restrict__ vkey,		/* key to be located */
	void ** __restrict__ vrootp,		/* address of tree root */
	int (*compar) (const void *, const void *))
{
	node_t *q, **n;
	node_t **rootp = (node_t **)vrootp;

	if (rootp == NULL)
		return NULL;

	n = rootp;
	while (*n != NULL) {			/* Knuth's T1: */
		int r;

		if ((r = (*compar)(vkey, ((*n)->key))) == 0)	/* T2: */
			return *n;		/* we found it! */

		n = (r < 0) ?
		    &(*rootp)->llink :		/* T3: follow left branch */
		    &(*rootp)->rlink;		/* T4: follow right branch */
		if (*n == NULL)
			break;
		rootp = n;
	}

	q = malloc(sizeof(node_t));		/* T5: key not found */
	if (!q)
		return q;
	*n = q;					/* make new node */
	/* LINTED const castaway ok */
	q->key = (void *)vkey;			/* initialize new node */
	q->llink = q->rlink = NULL;
	return q;
}
