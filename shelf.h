struct node_t {
    const char* name;
    struct node_t* next;
};

struct linked_list {
    struct node_t* head;
    size_t size;
};

static struct linked_list* headers;

static int win_init(lua_State*);
static int read_char(lua_State*);
static int win_end(lua_State*);

static int add_fields(lua_State*);
static int write_fields(void);
static int add_record(lua_State*);
static int write_record(void);
