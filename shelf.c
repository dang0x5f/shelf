#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ncurses.h>
#include "lua.h"
#include "lauxlib.h"

#include "shelf.h"

static int
win_init(lua_State* L)
{
    initscr();
    noecho();
    curs_set(0);
    box(stdscr,0,0);

    return(0);
}

static int 
debug(lua_State* L)
{
    list_t* tbl_head;
    /* list_t rec_data; */


    field_t* field1 = malloc(sizeof(field_t));
    field1->name = "Daniel";

    field_t* field2 = malloc(sizeof(field_t));
    field2->name = "Peter";

    field_t* field3 = malloc(sizeof(field_t));
    field3->name = "Gehrz";

    field1->next = field2;
    field2->next = field3;
    field3->next = NULL;

    tbl_head = malloc(sizeof(list_t));
    tbl_head->count = 3;

    tbl_head->head.field_node = field1;

    field_t* iter = tbl_head->head.field_node;
    while(iter != NULL){
        printf("%s\n", iter->name);
        iter = iter->next;
    }

    free(tbl_head);

    return(0);
}

/* add_fields(var1 , var2 , ... , numofvars) */
static int
add_fields(lua_State* L)
{
    int x;

    header_list = malloc(sizeof(list_t));
    header_list->len = lua_tointeger(L,-1);
    header_list->head.field_node = NULL;
    /* int x; */

    for(x = header_list->len; x>0; x--){
        if(header_list->head.field_node == NULL){
            header_list->head.field_node = malloc(sizeof(field_t));
            header_list->head.field_node->name = lua_tostring(L,-1-x);
            header_list->head.field_node->next = NULL;
        }else{
            field_t* iter = header_list->head.field_node;
            while(iter->next != NULL)
                iter = iter->next;

            iter->next = malloc(sizeof(field_t));
            iter->next->name = lua_tostring(L,-1-x);
            iter->next->next = NULL;
        }
    }

    write_fields();

    return(0);
}

static int
write_fields(void)
{
    int right = 2;
    field_t* iter = header_list->head.field_node;
    while(iter){
    
        int len = strlen(iter->name);
        for(int i = 0; i < len; i++){
            mvwaddch(stdscr, 1, right++, iter->name[i] | A_UNDERLINE);
        }
        
        right += 10;
        iter = iter->next;
    }

    return(0);
}

static int
add_record(lua_State* L)
{
    /* mvwaddstr(stdscr, lua_tointeger(L,-1), 2, lua_tostring(L,-2)); */

    return(0);
}

static int
write_record(void)
{
    return(0);
}

static int
read_char(lua_State* L)
{
    int c;

    refresh();
    c = getch();

    lua_pushinteger(L,c);

    return(1);
}

static int
win_end(lua_State* L)
{
    /* struct node_t* current = headers->head; */

    /* if(current == NULL){ */
    /*     free(headers); */
    /*     return(0); */
    /* } */

    /* struct node_t* next = current->next; */
    /* do{ */
    /*     free(current); */
    /*     current = next; */
    /*     if(current != NULL) */
    /*         next = current->next; */
    /* }while(current != NULL); */

    endwin();

    return(0);
}

static const struct luaL_Reg lib [] = {
     { "win_init"   , win_init   }
    ,{ "read_char"  , read_char  }
    ,{ "win_end"    , win_end    }
    ,{ "add_record" , add_record }
    ,{ "add_fields" , add_fields }
    ,{ "debug" , debug }
    ,{ NULL         , NULL       }
};

int 
luaopen_shelf(lua_State* L)
{
    luaL_newlib(L,lib);
    return(1);
}
