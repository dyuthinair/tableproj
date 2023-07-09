/*************************************************/
/*   (C) 2023 Dyuthi Nair                        */
/*                                               */
/*                                               */
/*************************************************/
#pragma once

using namespace std;

class ITracer {
    private:
        static ITracer* globalTracer;
        static int traceLevel;

    public: 
        void virtual Trace(const char *fmt, ...) = 0;
        static ITracer* GetTracer();
};

class CTracer: public ITracer
{
    public: 
        void virtual Trace(const char *fmt, ...);    
};

class CNullTracer: public ITracer
{
    public: 
        void virtual Trace(const char *fmt, ...) {}
};