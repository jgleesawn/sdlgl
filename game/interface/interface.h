#ifndef INTERFACE_H
#define INTERFACE_H

#include <SDL2/SDL.h>

#include <functional>
#include <map>


struct input {
	void * state;
	int count;
	int stepsize;
};

//typedef void(T::*fptr)(void)
template <class T>
class Interface {
public:
	typedef void(T::* Tfptr_t)(void);
	Uint8 * state;
	int count;
	std::map<Tfptr_t,int,std::less<Tfptr_t const> > m;
	void Loop(T *);
};

template <class T>
void Interface<T>::Loop(T * t) {
	typename std::map<Tfptr_t,int,std::less<Tfptr_t const> >::iterator it;
	for( it = m.begin(); it != m.end(); it++ ) {
		if( it->second < 0 )
			continue;
		if( state[it->second] )
			(t->*(it->first))();
	}
}

#endif
