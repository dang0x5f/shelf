#ifndef SHELF_LIFE
#define SHELF_LIFE

typedef struct rowcelldata {
    const char* value;
    struct rowcelldata* next;
} rowcelldata_t;

typedef struct record {
    WINDOW* row;    
    rowcelldata_t* cells;
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

static list_t* header_list;
static list_t* records_list;

static int win_init(lua_State*);
static int read_char(lua_State*);
static int win_end(lua_State*);

static int add_fields(lua_State*);
static int add_field(lua_State*);
static int add_field_lens(lua_State*);
static int write_fields(void);
static int add_record(lua_State*);
static int write_record(void);
static int draw(lua_State*);

static int debug(lua_State*);

#endif
