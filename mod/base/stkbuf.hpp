#pragma once
#include<string_view>
#include <string>
using std::string_view;
using std::string;
template<const int sz=1024>
struct SPBuf{
    char buf[sz];
    size_t ptr;
    SPBuf():ptr(0){}
    constexpr inline std::string getstr(){
        return std::string(buf,ptr);
    }
    constexpr inline string_view get(){
        return {buf,(size_t)ptr};
    }
    void clear(){
        ptr=0;
    }
    constexpr inline void write(string_view sv){
        if(unlikely(sv.size()>sz-ptr)) return;
        memcpy(buf+ptr,sv.data(),sv.size());
        ptr+=sv.size();
    }
    constexpr inline void write(string& s){write(string_view(s));}
    constexpr inline void write(string&& s){write(string_view(s));}
    constexpr inline void write(const string& s){write(string_view(s));}
    constexpr inline void write(const char* cs){
        auto csz=strlen(cs);
        if(unlikely(csz>sz-ptr)) return;
        memcpy(buf+ptr,cs,csz);
        ptr+=csz;
    }
    template <typename... Params>
    constexpr inline void write(Params &&... params){
        ptr+=snprintf(buf+ptr,sz-ptr,std::forward<Params>(params)...);
    }
};
