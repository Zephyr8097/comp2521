// crawl.c ... build a graph of part of the web
// Written by John Shepherd, September 2015
// Uses the cURL library and functions by Vincent Sanders <vince@kyllikki.org>

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <ctype.h>
#include <curl/curl.h>
#include "stack.h"
#include "graph.h"
#include "html.h"
#include "url_file.h"
#include "queue.h"
#include "set.h"

#define BUFSIZE 1024

void setFirstURL(char *, char *);
void normalise(char *, char *, char *, char *, int);

int main(int argc, char **argv)
{
	URL_FILE *handle;
	char buffer[BUFSIZE];
	char baseURL[BUFSIZE];
	char firstURL[BUFSIZE];
	//char next[BUFSIZE];
	int  maxURLs;

	if (argc > 2) {
		strcpy(baseURL,argv[1]);
		setFirstURL(baseURL,firstURL);
		maxURLs = atoi(argv[2]);
		if (maxURLs < 40) maxURLs = 40;
	}
	else {
		fprintf(stderr, "Usage: %s BaseURL MaxURLs\n",argv[0]);
		exit(1);
	}
		
	// You need to modify the code below to implement:
	//
	// add firstURL to the ToDo list
	Queue Todo = newQueue();
	enterQueue(Todo, firstURL);
	
	// initialise Graph to hold up to maxURLs
	Graph G = newGraph((size_t)maxURLs);
	
	// initialise set of Seen URLs
	Set seen = newSet();
	
	// while (ToDo list not empty and Graph not filled) {
	while(!emptyQueue(Todo) && nVertices(G) <(size_t)maxURLs){
	
	//    grab Next URL from ToDo list
	    char *nextURL = leaveQueue(Todo); // current url
	    
	//    if (not allowed) continue
	    if (!(handle = url_fopen(nextURL, "r"))){
	        fprintf(stderr,"Couldn't open %s\n", nextURL);
	        continue;
	    }
	    
	//    for each line in the opened URL {
	    while(!url_feof(handle)){ //until the end
	        url_fgets(buffer,sizeof(buffer),handle);//for the whole line, obtain the html
	        int pos = 0;
		    char result[BUFSIZE];
		    memset(result,0,BUFSIZE);//??
		    
	//       for each URL on that line {
	        while ((pos = GetNextURL(buffer, nextURL, result, pos)) > 0) {//get URL
			    printf("Found: '%s'\n",result);
		    }
		    
	//          if (Graph not filled or both URLs in Graph)
	
	        if(nVertices(G)<= (size_t)maxURLs || (isElem(seen,nextURL) && isElem(seen,result))){
	        
	//          add an edge from Next to this URL
	            addEdge(G, nextURL,result);
	        }
	
	//          if (this URL not Seen already) {
	        if (!isElem(seen, result)){
	            
	//         add it to the Seen set
	            enterQueue(Todo, result);
	                
	//         add it to the ToDo list
	            insertInto(seen, result);
	
	        }
	        memset(result, 0, BUFSIZE);
    
        }
        
	//    close the opened URL
	    url_fclose(handle);
	    
	//    sleep(1)
	    sleep(1);
	}
	printf("Show ");
	showGraph(G,0);
	showGraph(G,1);
	
	dropQueue(Todo);
	dropGraph(G);
	dropSet(seen);
	return 0;
}
