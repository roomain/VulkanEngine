#pragma once
/***********************************************
* @headerfile enumerates.h
* @date 25 / 08 / 2024
* @author Roomain
************************************************/
#include <vector>

template<typename ...Arg, typename Fun, typename Type>
void enumerate(const Fun& a_fun, std::vector<Type>& a_list, Arg... a_arg)
{
    uint32_t num = 0;
    a_fun(a_arg..., &num, nullptr);
    a_list.resize(num);
    a_fun(a_arg..., &num, a_list.data());
}

