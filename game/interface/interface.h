#ifndef INTERFACE_H
#define INTERFACE_H

#include <SDL2/SDL.h>

#include <functional>
#include <map>


namespace std {
template<class T, typename Return, typename ...Params>
struct less<Return(T::* const)(Params...)> {
	typedef Return(T::*first_arg_type)(Params...);
	typedef Return(T::*second_arg_type)(Params...);
	typedef bool result_type;
	result_type operator()(first_arg_type const lhs, second_arg_type const rhs) const {
		static_assert(
			sizeof(first_arg_type) == sizeof(second_arg_type),
			"Types must have the same size for binary comparison!"
		);
		const char
			*lhs_ = reinterpret_cast<const char *>(&lhs),
			*rhs_ = reinterpret_cast<const char *>(&rhs);
		if( lhs != rhs )
			for(size_t N=sizeof(first_arg_type); N-->0; ++lhs_, ++rhs_) {
				if( *lhs_ != *rhs_ )
					return *lhs_ < *rhs_;
			}
		return false;
	}
};
}


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



