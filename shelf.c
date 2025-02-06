#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ncurses.h>
#include "lua.h"
#include "lauxlib.h"

struct node_t {
    const char* name;
    struct node_t* next;
};

struct linked_list {
    struct node_t* head;
    size_t size;
};

static struct linked_list* headers;

static int
win_init(lua_State* L)
{
    initscr();
    noecho();
    box(stdscr,0,0);

    return(0);
}

static int
addcolheads(lua_State* L)
{
    int x, right;

    headers = malloc(sizeof(struct linked_list));
    headers->head = NULL;
    headers->size = lua_tointeger(L,-1);

    /* printf("%zu\n", headers->size); */


    for(x=1;x<=headers->size;x++){
        /* printf("%s\n", lua_tostring(L, -1 -x)); */
        if(headers->head == NULL){

            headers->head = malloc(sizeof(struct node_t));
            headers->head->name = lua_tostring(L,-1-x);
            headers->head->next = NULL;

        }else{

            struct node_t* iter = headers->head->next;
            while(iter->next != NULL)
                iter = iter->next;

            iter->next = malloc(sizeof(struct node_t));
            iter->next->name = lua_tostring(L,-1-x);            
            iter->next->next = NULL;

        }
    }

    
    right = 1;
    for(x=0;x<headers->size;x++){

    }

    /* int x, right; */
    /* const char* head = lua_tostring(L,-1); */
    /* size_t len = strlen(head); */

    /* right = 1; */
    /* for(x = 0; x < len; x++) */
    /*     mvwaddch(stdscr, 1, right++, head[x] | A_REVERSE); */

    return(0);
}

static int
addrow(lua_State* L)
{
    mvwaddstr(stdscr, lua_tointeger(L,-1), 2, lua_tostring(L,-2));

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
    endwin();

    return(0);
}

static const struct luaL_Reg lib [] = {
     { "win_init"  , win_init  }
    ,{ "read_char" , read_char }
    ,{ "win_end"   , win_end   }
    ,{ "addrow"    , addrow    }
    ,{ "addcolheads"    , addcolheads    }
    ,{ NULL        , NULL      }
};

int 
luaopen_shelf(lua_State* L)
{
    luaL_newlib(L,lib);
    return(1);
}
