/*************************************************/
/*   (C) 2023 Dyuthi Nair                        */
/*                                               */
/*                                               */
/*************************************************/
#include <stdarg.h>
#include <iostream>
#include "itracer.hpp"

using namespace std;

ITracer* ITracer::globalTracer = nullptr;
int ITracer::traceLevel = 1;

void CTracer::Trace(const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);

    char buffer[256];
    vsnprintf (buffer, 255, fmt, args);
    cout << buffer;

    va_end(args);
}

ITracer* ITracer::GetTracer()
{
    if (globalTracer == nullptr)
    {
        if (traceLevel == 0)
            globalTracer = new CNullTracer();
        else
            globalTracer = new CTracer();
    }

    return globalTracer;
}