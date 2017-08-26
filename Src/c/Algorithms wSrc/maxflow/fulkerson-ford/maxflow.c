/* What: Max Flow in a directed graph, fulkerson-ford
  From http://webdocs.cs.ualberta.ca/~contest/code/Old/Graph_Theory/maxflow.c
  Date: 2013-03-26
  Author: Matthew McNaughton <mcnaught@cs.ualberta.ca>
 
  Usage:

  The graph is the global head_t flowgraph[], which you must allocate, and
    initialize the elements to 0/NULL. Each graph node has a list of edge_t
    elements with the neighbour "v", the capacity "cap" along the edge, and
    "flow", which is the flow along the edge after maxflow() has finished.

  
  Add edges to the graph with graph_addedge( flowgraph, v, w, c ),
    meaning there is a directed edge
    from node v to node w with capacity c.

  Nodes are numbered by index in flowgraph[]. You must make sure
    that flowgraph[] is large enough, it is not resized automatically
    by maxflow() or support functions, in fact the graph utilities have
    no idea how large flowgraph[] is. Use graph_access(flowgraph, v, w)
    to get the edge_t* for the edge from v to w.

  maxflow(source, sink, NV) computes and returns the maxflow through
    the graph from node source to node sink. NV is the number of nodes
    in the global flowgraph[]. 

  mincut:
    As a side effect maxflow() sets the global mincut[].  
    mincut[i] == 1 if node i is on the source side of the min-cut, and
    mincut[i] == 0 if node i is on the sink side of the min-cut.
    i.e. any edge (i,j) with mincut[i] == 1 and mincut[j] == 0
    is an edge of the min-cut.

  Date: April 1999-March 2000
  Added: 9 March 2000
 */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <time.h>
#include <limits.h>

typedef struct {
  int edgev, cap, flow;
} edge_t;

typedef struct {
  int noden;
  edge_t *edgelist;
} head_t;

#define NVM 30
int edgee[NVM][NVM];

/*
  flowgraph[] is the capacity/flow graph.
  flowgraph[x] is the list of edges leaving x
  flowgraph[x].edgelist[i] holds the i-th neighbour,
    the edge capacity to it, and flow to it, from x.
*/
head_t *flowgraph=0;

/* min-cut list. mincut[i] != 0 iff i is on the source side of the min-cut. */
int *mincut=0;

int min2(int a, int b) { return a < b ? a : b; }

void
graph_free(head_t *flowgraph, int nv) {
  int i;
  for( i = 0; i < nv; i++ ) {
    free(flowgraph[i].edgelist);
  }
  free(flowgraph);
}

/* returns the edge_t* for the edge from v to w. */
edge_t *
graph_access(head_t *flowgraph, int v, int w) {
  int i;
  for( i=0; i < flowgraph[v].noden; i++ ) {
    if( flowgraph[v].edgelist[i].edgev == w )
      return &flowgraph[v].edgelist[i];
    /* if( flowgraph[v].edgelist[i].edgev > w ) return NULL; */
  }
  return NULL;
}

/* Add 0-capacity edge from v to w for neighbour information bfs in maxflow */
void
graph_add_dummy(head_t *flowgraph, int v, int w) {
  edge_t *p; int j;
  for( j = 0; j < flowgraph[v].noden; j++ ) {
    /* already have an edge */
    if( flowgraph[v].edgelist[j].edgev == w ) return;
  }

  flowgraph[v].edgelist = realloc(flowgraph[v].edgelist,
      (flowgraph[v].noden+1)*sizeof(flowgraph[v].edgelist[0]));

  p = &flowgraph[v].edgelist[ flowgraph[v].noden ];
  
  p->edgev = w;
  p->cap = 0;
  p->flow = 0;
  flowgraph[v].noden++;
  return;
}

edge_t *
graph_addedge(head_t *flowgraph, int v, int w, int cap) {
  edge_t *p; int j;

  for( j = 0; j < flowgraph[v].noden; j++ ) {
    if( flowgraph[v].edgelist[j].edgev == w ) {
      flowgraph[v].edgelist[j].cap += cap;
      /* edge in other direction has already been added. */
      return & flowgraph[v].edgelist[j];
    }
  }

  flowgraph[v].edgelist = realloc(flowgraph[v].edgelist,
      (flowgraph[v].noden+1)*sizeof(flowgraph[v].edgelist[0]));

  p = &flowgraph[v].edgelist[ flowgraph[v].noden ];

  p->edgev = w;
  p->cap = cap;
  p->flow = 0;
  flowgraph[v].noden++;
  graph_add_dummy(flowgraph, w, v);
  return p;
}

/* See usage at top of file */
int
maxflow( int source, int sink, int NV ) {
  int flow, i, j, head, tail, v=0,w, inc;
  int *queue, *pred, *maxcap;
  edge_t *p, *e, *e1, *e2;

  queue = malloc((NV+1)* sizeof(queue[0]));
  pred  = malloc(NV * sizeof(pred[0]));
  maxcap= malloc(NV * sizeof(maxcap[0]));
  if( mincut ) free(mincut);
  mincut     = malloc(NV * sizeof(mincut[0]));

  /* Initialize flows to 0 */
  for( i = 0; i < NV; i++ ) {
    for( j = 0; j < flowgraph[i].noden; j++ ) {
      flowgraph[i].edgelist[j].flow = 0;
    }
  }

  flow = 0;
  while(1) {
    head = tail = 0;
    for( i = 0; i < NV; i++ ) mincut[i] = 0;
    queue[tail++] = source; mincut[source] = 1;

    while(head != tail) {
      v = queue[head++];
      if(v ==sink ) break;
      for( j = 0; j < flowgraph[v].noden; j ++ ) { /* for each neighbour */
        p = &flowgraph[v].edgelist[j];
        i = p->edgev;
        if(mincut[i]) continue;
        e = p;
        if( e->cap && e->flow < e->cap ) {
          mincut[i] = 1;
          queue[tail++] = i; pred[i] = v;
          maxcap[i] = e->cap - e->flow;
        }
        else { /* need to look at edge going the other way. */
          e = graph_access(flowgraph,i,v);
          if( e && e->cap && e->flow > 0 ) { /* it may not exist */
            maxcap[i] = e->flow;
            mincut[i] = 1;
            queue[tail++] = i; pred[i] = v;
          }
        }
      }
    } /* bfs: while( head != tail) */

    if( v != sink) {
      break; /* return */
    } else {
      inc = INT_MAX;
      v = sink;
      while( v != source ) {
        inc = min2(inc, maxcap[v] );
        v = pred[v];
      }
      flow += inc;

      v = sink;
      while(v != source) {
        w = pred[v];
        e1 = graph_access(flowgraph, w, v);
        e2 = graph_access(flowgraph, v, w);

        if( e1 && e1->cap ) {
          e1->flow += inc;
        }
        else if( e2 && e2->cap ) {
          e2->flow -= inc;
        }
        else assert(0);

        if( e1 && e2 && e1->flow && e2->flow ) {
          if( e1->flow > e2->flow ) {
            e1->flow -= e2->flow;
            e2->flow = 0;
          } else {
            e2->flow -= e1->flow;
            e1->flow = 0;
          }
        }
        v = w;
      }
    }
  }
  free(queue); free(pred); free(maxcap);
  return flow;
}

char *edge_color(int flow, int cap) {
  char *color="black /*unused*/";
  if (flow > 0) {
    color = "green /*partial capacity*/";
    if (flow == cap)
      color = "blue /*full capacity*/";
  }
  return color;
}

void new_flowgraph(int nv) {
  int i;
  flowgraph = malloc( nv * sizeof(flowgraph[0]));
  for( i = 0; i < nv; i++ ) {
    flowgraph[i].noden = 0;
    flowgraph[i].edgelist = NULL;
  }
}

void read_graph(int *psource, int *psink, int *pnv) {
  int nv, source, sink, v, w, c;
  fprintf(stdout, "Input: nv source sink ..\n");
  fscanf(stdin, "%d %d %d", &nv, &source, &sink) ;
  nv++;

  new_flowgraph(nv);

  fprintf(stdout, "Input: v w c ..\n");
  while(fscanf(stdin, "%d %d %d", &v, &w, &c ) == 3 ) {
    printf("graph_addedge(%d,%d), capacity=%d\n",  v, w, c);
    assert(v < nv);
    assert(w < nv);
    assert(c >= 0 );
    graph_addedge(flowgraph, v, w, c);
  }
  *pnv = nv; *psource = source; *psink = sink; 
}

int randi(int a, int b) {
  int r = b-a;
  if (r==0) return a;
  if (r<0) return -randi(b,a);
  return a + rand() % r;
}

void rand_graph(int *psource, int *psink, int *pnv) {
  int nv, i, j, c;

  srand(time(0));
  *pnv = nv = 5+rand()%5;
  *psource = 1;
  *psink = nv-1;

  printf("rand_graph nv=%d\n", nv);
  new_flowgraph(nv);
  for( i = 0; i < nv; i++ ) for( j = 0; j < nv; j++ ) edgee[i][j] = 0;

  // fill the upper triangular matrix, with some blanks.
  for( i = 1; i < nv; i++ )
    for( j = i+1; j < nv; j++ ) {
      if (randi(0,1) && edgee[i][j]==0) continue;
      c = edgee[i][j] = randi(1,10);
      printf("rand_graph e(%d,%d)= capacity %d\n", i, j, c);
      graph_addedge(flowgraph, i, j, c);
    }
}

int main() {
  int nv, i, j, k, source, sink, flow;
  edge_t *e;
  FILE *mg;

  mg = fopen("maxflow.gv", "w");
  if(!mg) {
   printf("Cannot write maxflow.gv\n");
   exit(-1);
  }

  // read_graph( &source, &sink, &nv);
  rand_graph( &source, &sink, &nv);
  flow = maxflow(source, sink, nv);

  fprintf(mg, "%s",
      "// View this maxflow graph in Graphviz\n"
      "digraph G {\n"
      "  layout=dot;\n"
      "  splines=true;\n");  
  fprintf(mg,"  %d [color=pink label = \"%d (source, flow=%d)\"];\n",
      source, source, flow);
  fprintf(mg, "  %d [color=pink label = \"%d (sink)\"];\n", sink, sink);


  fprintf(stdout, "Maxflow: %d\n", flow);
  fprintf(stdout, "Min-cut edges:\n");

  assert(nv <= NVM);
  for( i = 0; i < nv; i++ ) for( j = 0; j < nv; j++ ) edgee[i][j] = 0;

  for( i = 0; i < nv; i++ ) {
    if( mincut[i] != 1 ) continue;
    for( j = 0; j < flowgraph[i].noden; j++ ) {
      k = flowgraph[i].edgelist[j].edgev;
      if( mincut[ k ] != 0 ) continue;
      fprintf(stdout, " (%d -> %d)\n", i, k );
      edgee[i][k] = 1;
    }
  }

  fprintf(stdout, "Flow values:\n");
  for( i = 0; i < nv; i++ ) {
    for( j = 0; j < nv; j++ ) {
      e = graph_access(flowgraph, i, j);
      if (!e) continue;
      if (e->flow || e->cap) {
        fprintf(mg, "  %d -> %d [label=\"%d/%d\" color=%s %s ];\n",
          i, j, e->flow, e->cap,
          edge_color(e->flow,e->cap),
          edgee[i][j]? "style=dashed /*mincut*/":""
          );
      }
      if (e->flow) {
        fprintf(stdout, " (%d -> %d) : %d\n", i, j, e->flow);
      }
    }
  }

  fprintf(mg, "%s","}\n");
  fclose(mg);

  return 0;
}
