

typedef struct EDGE edge;
typedef struct NODE node;

struct EDGE{
	int ID;
//	node* node_from;
//	node* node_to;
	int node_from;
	int node_to;

	int dd;
	int mm;
	int yy;
};

struct NODE{
	int ID;
	edge* next;
};

void print_edge(edge *edge);