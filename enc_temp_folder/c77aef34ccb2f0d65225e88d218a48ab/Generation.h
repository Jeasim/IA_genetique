#ifndef GENERATION_H
#define GENERATION_H
#include "Console\Console.h"

class Generation
{
private:
public:
	Generation(size_t height, size_t width, std::string type, size_t nbPopulations, size_t nbObstacles);
	~Generation();

	enum class State { idle, generation1, fitness, stop,  elitetransfer, reproduct, substitute, pause};
	
	void start();
	void pause(State & state);

private :
	State pausedState = State::pause;
	
	void loop(State state);
	void testShortcut(State & state);
	void processInput();
	void render(State state);
	State update(State& state);
	Generation::State updateSbS(State & state);
	Generation::State nextState(State& state);

	bool Mstep_by_step;

	ConsoleKeyReader * reader_m;
	ConsoleKeyReader::KeyEvents keyEvents;
	
};
#endif //GENERATION_H