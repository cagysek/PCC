
//==================================
//			STRUCTURES
//==================================

typedef struct EDGE edge;
typedef struct NODE node;
typedef struct PATH path;
typedef struct DATE date;

// DATE
// dd - day
// mm - month
// yy - year
//===================================
struct DATE{
	int dd;
	int mm;
	int yy;
};
//FUNCTIONS
//===================================
date *create_date(int yy, int mm, int dd);
int date_to_number(date *d);
//==================================

//EDGE
// node_from - index of source node
// node_to - index of target node
// date - pointer to date
//===================================
struct EDGE{
	int node_from;
	int node_to;
	date *date;
};
//FUNCTIONS
//===================================
void print_edge();
//===================================

//NODE
// ID - node ID
// neighbors - array that contains indexes of edges connected with node
// neighbors_count - count of neighbors stored in neighbors array
// neighbors_max_count - max size of neighbors array
// neighbors_extension_number - number to represent how many times I have to extension array for next extension
// visited - for dfs stuff, represent if node is visited or not
//===================================
struct NODE{
	int ID;
	int *neighbors;
	int neighbors_count;
	int neighbors_max_count;
	int neighbors_extension_number;
	int visited;
};
//FUNCTIONS
//===================================
int create_node(int new_ID, int order);
void print_node();
void add_edge_to_node(node *node, int edge);
int get_source_index(int source);
int get_target_index(int target);
//===================================

//PATH
// iterate_nodes - array that contains indexes of nodes, which path passes
// iterate_edges - array that contains indexes of edges, which path passes
// path_count - count of members, which path passes
// max_count - max size of iterate_nodes and iterate_edges array
// extension_number - number to represent how many times I have to extension array for next extension
// metric - difference between the smallest date and the largest date
//===================================
struct PATH{
	int *iterate_nodes;
	int *iterate_edges;
	int path_count;
	int max_count;
	int extension_number;
	int metric;
};
//FUNCTIONS
//===================================
path *create_path();
void save_path(path *p);
void remove_last(path *p);
void print_path();
void add_node_to_path(path *p, int node_index, int edge_index);
int cmp_func_path_order (const void * a,const void * b);
int count_metric(path *p);
//===================================



//FUNCTIONS - OTHER
//===================================
//reader.c
int countlines(char *filename);
void load_topology(char *filename);

//main.c
void free_all();

//dfs.c
void dfs(int start, int end, int max_lenght, path *p, int edge_index);







