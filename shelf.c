#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ncurses.h>
#include "lua.h"
#include "lauxlib.h"

static int drawheaders(void);

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
    int x;

    headers = malloc(sizeof(struct linked_list));
    headers->head = NULL;
    headers->size = lua_tointeger(L,-1);

    /* printf("%zu\n", headers->size); */


    for(x=headers->size;x>0;x--){
        /* printf("%s\n", lua_tostring(L, -1 -x)); */
        if(headers->head == NULL){

            headers->head = malloc(sizeof(struct node_t));
            headers->head->name = lua_tostring(L,-1-x);
            headers->head->next = NULL;

        }else{

            struct node_t* iter = headers->head;
            while(iter->next != NULL)
                iter = iter->next;

            iter->next = malloc(sizeof(struct node_t));
            iter->next->name = lua_tostring(L,-1-x);            
            iter->next->next = NULL;

        }
    }

    drawheaders();

    /* int x, right; */
    /* const char* head = lua_tostring(L,-1); */
    /* size_t len = strlen(head); */

    /* right = 1; */
    /* for(x = 0; x < len; x++) */
    /*     mvwaddch(stdscr, 1, right++, head[x] | A_REVERSE); */

    return(0);
}

static int
drawheaders(void)
{
    int right = 2;
    struct node_t* iter = headers->head;
    while(1){

        if(iter == NULL)
            break;
    
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
    struct node_t* current = headers->head;

    if(current == NULL){
        free(headers);
        return(0);
    }

    struct node_t* next = current->next;
    do{
        free(current);
        current = next;
        if(current != NULL)
            next = current->next;
    }while(current != NULL);

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
