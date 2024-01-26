// CLuaProj.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
/// <summary>
/// load lua external libs
/// </summary>
extern "C"
{
#include "lua/include/lua.h"
#include "lua/include/lauxlib.h"
#include "lua/include/lualib.h"
}

///quick and dirty way to load lua libs for windows
#ifdef _WIN32
#pragma comment(lib, "lua/lua54.lib")
#endif

/// <summary>
/// check if lua is compiled and scripts can be run
/// </summary>
void luaEmbed(){
    std::cout << "Hello World!\n";
    std::string cmd = "luaLoaded = 1";
    lua_State* L = luaL_newstate();
    int r = luaL_dostring(L, cmd.c_str());
    if (r == LUA_OK){
        lua_getglobal(L, "luaLoaded");
        if (lua_isnumber(L, -1)){
            float _luaLoaded = (float)lua_tonumber(L, -1);
            std::cout << "luaLoaded = " << _luaLoaded << std::endl;
            printf("Lua compiled successfully...");
        }
    }
    else{
        std::string error_msg = lua_tostring(L, -1);
        std::cout << error_msg << std::endl;
    }
    lua_close(L);
    printf("Done! \n");
}

/// <summary>
/// Check stack elm
/// </summary>
void luaCheckStack(){
    lua_State* L = luaL_newstate();
    lua_pushnumber(L, 286); // stack[1]
    lua_pushnumber(L, 386); // stack[2]
    lua_pushnumber(L, 486); // stack[3]
    lua_Number elm;
    elm = lua_tonumber(L, -1);
    printf("The last added elm in pos 3 is %d\n", (int)elm);
    lua_close(L);
}

/// <summary>
/// call lua func from script
/// </summary>
void luaCallFunction() {
    lua_State* L = luaL_newstate();

    if (luaL_dofile(L, "funcs.lua") != LUA_OK){
        luaL_error(L, "Error: %s\n", lua_tostring(L, -1));
    }

    lua_getglobal(L, "pytha");
    if (lua_isfunction(L,-1)){
        //push params to stack so lua can retrieve them
        lua_pushnumber(L, 2); //1st param
        lua_pushnumber(L, 6); //2nd param

        const int num_args = 2;
        const int num_returns = 1;
        lua_pcall(L, num_args, num_returns, 0);

        //retrieve returned value form lua func
        lua_Number result = lua_tonumber(L, -1);

        printf("result value %d\n", (int)result);
    }
    lua_close(L);
}

/// <summary>
/// Pythagoras function to be pushed to lua stack
/// </summary>
/// <param name="L"></param>
/// <returns></returns>
int pythagoras(lua_State* L) {
    lua_Number b = lua_tonumber(L, -1); //get last param from stack
    lua_Number a = lua_tonumber(L, -2); //get fist param from 
    lua_Number result = (a * a) + (b * b);
    lua_pushnumber(L, result);
    return 1;
    //c_pytha(a,b)
}


/// <summary>
/// push naitive c function into lua stack
/// </summary>
/// <param name=""></param>
void push_C_Function(void){
    lua_State* L = luaL_newstate();

    lua_pushcfunction(L, pythagoras);
    lua_setglobal(L, "pythagoras");

    if (luaL_dofile(L, "funcs2.lua") != LUA_OK) {
        luaL_error(L, "Error: %s\n", lua_tostring(L, -1));
    }
    lua_getglobal(L,"c_pytha");
    if (lua_isfunction(L, -1)) {
        lua_pushnumber(L, 3); //1st arg
        lua_pushnumber(L, 4); //2nd arg

        const int NUM_ARGS = 2;
        const int NUM_RETURNS = 1;
        lua_pcall(L, NUM_ARGS, NUM_RETURNS, 0);
        lua_Number result = lua_tonumber(L ,-1);

        printf("pythagoras(3,4) = %f\n", result);
    }
    lua_close(L);
}


/// <summary>
/// Main 
/// </summary>
/// <returns>void</returns>
int main(){
    luaEmbed();
    /*luaCheckStack();
    luaCallFunction();*/
    push_C_Function();
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
