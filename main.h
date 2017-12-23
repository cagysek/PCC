

typedef struct EDGE edge;
typedef struct NODE node;
typedef struct PATH path;
typedef struct DATE date;

struct DATE{
	int dd;
	int mm;
	int yy;

};

struct EDGE{
	int edge_id;
	int node_from;
	int node_to;
	date *date;

};



void print_edge();





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
	int *iterate_nodes;
	int *iterate_edges;
	int path_count;
	int max_count;
	int extension_number;
	int metric;
};

int create_node(node *nodes,int new_ID, int order);
void print_node();
void add_edge_to_node(node *node, int edge);


