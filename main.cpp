#include "engine.h"
#include "error_list.h"
#include <iostream>

class Tst : public App
{
private:
	
public:
	void init();
	void update(f32 delta_time);
	void draw();
	void shutdown();
};

void Tst::init(){}
void Tst::update(f32 delta_time){}
void Tst::draw(){}
void Tst::shutdown(){}

int main()
{
    auto engine = new NamelessEngine();
    b8 result = engine->init("JOJ Engine", 800, 600);
    if(result != OK)
    {
        std::cout << "Failed to initalize engine - " << "[" << error_names[result] << "]\n";
        return result;
    }
    
    // Main loop
    engine->run(new Tst());
    
    engine->shutdown();

    delete engine;
    
    return 0;
}