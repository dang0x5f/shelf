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
    box(stdscr,0,0);

    return(0);
}

static int
addcolheads(lua_State* L)
{
    int x, right;
    const char* head = lua_tostring(L,-1);
    size_t len = strlen(head);

    right = 1;
    for(x = 0; x < len; x++)
        mvwaddch(stdscr, 1, right++, head[x] | A_REVERSE);

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
