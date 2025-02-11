// struct node_t {
//     const char* name;
//     struct node_t* next;
// };

// struct linked_list {
//     struct node_t* head;
//     size_t size;
// };

typedef struct record {
    int x;
} record_t;

typedef struct field {
    const char* name;
    size_t len;
    struct field* next;
} field_t;

typedef struct linked_list {
    union {
        field_t*  field_node;
        record_t* record_node;
    } head;
    size_t len;
    size_t count;
} list_t;

static struct linked_list* headers;

static int win_init(lua_State*);
static int read_char(lua_State*);
static int win_end(lua_State*);

static int add_fields(lua_State*);
static int write_fields(void);
static int add_record(lua_State*);
static int write_record(void);

static int debug(lua_State*);
