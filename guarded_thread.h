#ifndef UTILITIES_THREAD
#define UTILITIES_THREAD

#include <thread>
#include <utility>

struct guarded_thread : std::thread{
	//guarded_thread() : thread(){}
	//guarded_thread( thread&& other) : thread(other) {}
	/*template< class Function >
	explicit guarded_thread( Function&& f) :
		thread(std::forward<Function>(f)){}      
										
	template< class Function, class obj >
	explicit guarded_thread( Function&& f, obj&& o ) :
		thread(std::forward<Function>(f), std::forward<obj>(o) ){}*/
	template<class... Args >
	explicit guarded_thread(Args&&... args) :
		thread(std::forward<Args>(args)... ){}

	~guarded_thread(){ if (this->joinable()) this->join(); }
};

#endif UTILITIES_THREAD