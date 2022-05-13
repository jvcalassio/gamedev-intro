#ifndef __TIMER__
#define __TIMER__

class Timer {
    private:
        float time;
    
    public:
        Timer();
        void Update(float dt);
        void Restart();
        float Get();
};

#endif