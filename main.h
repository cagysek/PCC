

typedef struct EDGE edge;
typedef struct NODE node;
typedef struct EDGE_INDEX edge_index;


struct EDGE_INDEX{
	int index;
	edge_index *next;
};


struct EDGE{
	int edge_id;
	int node_from;
	int node_to;
//	int node_from;
//	int node_to;
	int dd;
	int mm;
	int yy;
};

void print_edge(edge *edge);




struct NODE{
	int ID;
	int *neighbours;
	int neighbours_count;
	int neighbours_max_count;
	int neighbours_extension_number;
	int visited;
};

struct GRAPH{
	int SIZE;
	node *node_array;
	edge *edge;
};

struct PATH{
	int *iterate;
};

int create_node(node *nodes,int new_ID, int order);
void print_node(node *root);
void add_edge_to_node(node *node, int edge);


