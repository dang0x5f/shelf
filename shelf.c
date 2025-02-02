#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ncurses.h>
#include "lua.h"
#include "lauxlib.h"

static int
win_init(lua_State* L)
{
    initscr();
    noecho();

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
    ,{ NULL        , NULL      }
};

int 
luaopen_shelf(lua_State* L)
{
    luaL_newlib(L,lib);
    return(1);
}
