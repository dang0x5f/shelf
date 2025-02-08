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

/* add_fields(var1 , var2 , ... , numofvars) */
static int
add_fields(lua_State* L)
{
    /* int x; */

    /* headers = malloc(sizeof(struct linked_list)); */
    /* headers->head = NULL; */
    /* headers->size = lua_tointeger(L,-1); */

    /* for(x=headers->size;x>0;x--){ */

    /*     if(headers->head == NULL){ */

    /*         headers->head = malloc(sizeof(struct node_t)); */
    /*         headers->head->name = lua_tostring(L,-1-x); */
    /*         headers->head->next = NULL; */

    /*     }else{ */

    /*         struct node_t* iter = headers->head; */
    /*         while(iter->next != NULL) */
    /*             iter = iter->next; */

    /*         iter->next = malloc(sizeof(struct node_t)); */
    /*         iter->next->name = lua_tostring(L,-1-x); */            
    /*         iter->next->next = NULL; */

    /*     } */
    /* } */

    /* write_fields(); */

    return(0);
}

static int
write_fields(void)
{
    /* int right = 2; */
    /* struct node_t* iter = headers->head; */
    /* while(1){ */

    /*     if(iter == NULL) */
    /*         break; */
    
    /*     int len = strlen(iter->name); */
    /*     for(int i = 0; i < len; i++){ */
    /*         mvwaddch(stdscr, 1, right++, iter->name[i] | A_UNDERLINE); */
    /*     } */
        
    /*     right += 10; */
    /*     iter = iter->next; */

    /* } */

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
    ,{ NULL         , NULL       }
};

int 
luaopen_shelf(lua_State* L)
{
    luaL_newlib(L,lib);
    return(1);
}
