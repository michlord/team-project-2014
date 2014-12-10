#ifndef ENGINE_SYSTEM_PHYSICS_LINEAR_FUNCTION_H_INCLUDED
#define ENGINE_SYSTEM_PHYSICS_LINEAR_FUNCTION_H_INCLUDED

namespace Physics
{
    class LinearFunction
    {
    public:
        LinearFunction(float a_, float b_, float c_);

        float getA();
        float getB();
        float getC();

    private:
        // ax + by + c = 0
        float a;
        float b;
        float c;
    };

}

#endif
