#include "Generation.h"
#include "Area.h"
#include "Transactions.h"

Generation::Generation():reader_m{ nullptr }
{
}


Generation::~Generation()
{
}

void Generation::start()
{
	Area::getInstance().generateArea();
	Area::getInstance().generatePoint();
	Area::getInstance().showPoint();
	shapeList_t liste;

	liste.push_back(new Cercle(Point2d(30, 30), 10));
	Area::getInstance().drawShape(liste);

	Generation::getInstance().reader_m = &(Console::getInstance().keyReader());

	loop(State::idle);
}

void Generation::loop(State state) {

	while (true)
	{
		processInput();
		state = update(state);
		render(state);
	}
}

void Generation::processInput()
{
	reader_m->read(keyEvents);

}

void Generation::render(State state)
{
}

Generation::State Generation::update(State & state)
{
	//idle, generation1, fitness, stop,  elitetransfer, reproduct, substitute
	switch (state) {
	case State::idle : 
		if(Transactions::getInstance().conditionidle(keyEvents)){
			return nextState(state);
		}
		else {
			return state;
		}
		break;
	case State::generation1:
		if (Transactions::getInstance().conditiongen1()) {
			return nextState(state);
		}
		else {
			return state;
		}
		break;
	case State::fitness:
		if (Transactions::getInstance().conditionfitness()) {
			return nextState(state);
		}
		else {
			return state;
		}
		break;
	case State::stop:
		if (Transactions::getInstance().conditionstop()) {
			//si les conditions sont vrais, arr�ter.
			return state;
		}
		else {
			//si les conditions sont fausses pour stop, continuer
			return nextState(state);
		}
		break;
	case State::elitetransfer:
		if (Transactions::getInstance().conditionelitetransfer()) {
			return nextState(state);
		}
		else {
			return state;
		}
		break;
	case State::reproduct:
		if (Transactions::getInstance().conditionreproduct()) {
			return nextState(state);
		}
		else {
			return state;
		}
		break;
	case State::substitute:
		if (Transactions::getInstance().conditionsubstitute()) {
			return State::fitness;
		}
		else {
			return state;
		}
		break;
	}
}

Generation::State Generation::nextState(State & state)
{
	return (State) ((int) state + 1);
}
