#pragma once

struct Adder
{
    int (__stdcall *AddInteger)(int a, int b);
    float (__stdcall *AddFloat)(float a, float b);
};