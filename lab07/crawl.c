// crawl.c ... build a graph of part of the web
// Written by John Shepherd, September 2015
// Uses the cURL library and functions by Vincent Sanders
// <vince@kyllikki.org>

#include <ctype.h>
#include <curl/curl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "graph.h"
#include "html.h"
#include "set.h"
#include "stack.h"
#include "queue.h"
#include "url_file.h"

#define BUFSIZE 1024

static void setFirstURL (char *, char *);

int main (int argc, char **argv)
{
	URL_FILE *handle;
	char buffer[BUFSIZE];
	char baseURL[BUFSIZE];
	char firstURL[BUFSIZE];
	char next[BUFSIZE];
	int maxURLs;

	if (argc > 2) {
		strcpy (baseURL, argv[1]);
		setFirstURL (baseURL, firstURL);
		maxURLs = atoi (argv[2]);
		if (maxURLs < 40)
			maxURLs = 40;
	} else {
		fprintf (stderr, "Usage: %s BaseURL MaxURLs\n", argv[0]);
		exit (1);
	}

	// You need to modify the code below to implement:
	//
	// add firstURL to the ToDo list
	// initialise Graph to hold up to maxURLs
	// initialise set of Seen URLs
	// while (ToDo list not empty and Graph not filled) {
	//    grab Next URL from ToDo list
	//    if (not allowed) continue
	//    foreach line in the opened URL {
	//       foreach URL on that line {
	//          if (Graph not filled or both URLs in Graph)
	//             add an edge from Next to this URL
	//          if (this URL not Seen already) {
	//             add it to the Seen set
	//             add it to the ToDo list
	//          }
	//       }
	//    }
	//    close the opened URL
	//    sleep(1)
	// }
	Queue q = newQueue();
	Graph graph1 = newGraph((size_t)maxURLs); // initialise Graph to hold up to maxURLs
	Set set1 = newSet();
	enterQueue(q, firstURL); // add firstURL to the ToDo list
	insertInto(set1, firstURL);// initialise set of Seen URLs
	
	while (!(emptyQueue(q)) && nVertices(graph1) < (size_t)maxURLs) {
	// while (ToDo list not empty and Graph not filled) 
	
	    char *url = leaveQueue(q);
	    //    grab Next URL from ToDo list
	    
	    if (!(handle = url_fopen (url, "r"))) {
		    fprintf (stderr, "Couldn't open %s\n", next);
		    exit (1);
	    }
	    while (!url_feof (handle)) {
		    url_fgets (buffer, sizeof (buffer), handle);
		    // fputs(buffer,stdout);
		    int pos = 0;
		    char result[BUFSIZE];
		    memset (result, 0, BUFSIZE);
		    while ((pos = GetNextURL (buffer, firstURL, result, pos)) > 0) {
			    printf ("Found: '%s'\n", result);
			    //memset (result, 0, BUFSIZE);
			    
			    if (nVertices(graph1)< (size_t)maxURLs || (!isConnected(graph1, result, url))){
			    //          if (Graph not filled or both URLs in Graph)
			        addEdge(graph1,url,result);
			    //             add an edge from Next to this URL
			    }
			    
			    if (!isElem(set1,result)){
			    //          if (this URL not Seen already) {
                    insertInto(set1,result);
                    //             add it to the Seen set
                    enterQueue(q,result);
                    //             add it to the ToDo list
                }
		    }
	    }
	    url_fclose (handle);
	    free(url);
	    //    close the opened URL
	    sleep (1);
	}
	showGraph(graph1,1);
    dropQueue(q);
    dropSet(set1);
    dropGraph(graph1);
	return 0;
}

// setFirstURL(Base,First)
// - sets a "normalised" version of Base as First
// - modifies Base to a "normalised" version of itself
static void setFirstURL (char *base, char *first)
{
	char *c;
	if ((c = strstr (base, "/index.html")) != NULL) {
		strcpy (first, base);
		*c = '\0';
	} else if (base[strlen (base) - 1] == '/') {
		strcpy (first, base);
		strcat (first, "index.html");
		base[strlen (base) - 1] = '\0';
	} else {
		strcpy (first, base);
		strcat (first, "/index.html");
	}
}
