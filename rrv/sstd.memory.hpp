#ifndef _0x00_____SSTD_MEMORY
#define _0x00_____SSTD_MEMORY

#include <stdlib.h>
inline void * c$malloc(size_t n) { return malloc(n); }
inline void * c$calloc(size_t num, size_t size) { return calloc(num, size); }
inline void * c$realloc(void* ptr, size_t new_size) { return realloc(ptr, new_size); }
inline void   c$free(void* ptr) { return free(ptr); }

#if !defined(__cplusplus)
/*add c function here*/
#ifndef SSTD_MEMOEY_OPERATOR
#define SSTD_MEMOEY_OPERATOR(...)
#endif

#else

#include <memory>
#include <cstddef>
#include <cstdlib>

namespace sstd {

	inline void * $malloc(std::size_t n) { return ::c$malloc(n); }
	inline void * $calloc(std::size_t num, std::size_t size) { return ::c$calloc(num, size); }
	inline void * $realloc(void* ptr, std::size_t new_size) { return  ::c$realloc(ptr, new_size); }
	inline void   $free(void* ptr) { return ::c$free(ptr); }
	//inline void * cpp$aligned_alloc(std::size_t alignment, std::size_t size) { return _aligned_malloc(size, alignment); }

}/*namesapce sstd*/

namespace sstd {
	//https://en.cppreference.com/w/cpp/memory/new/operator_delete 
	//https://en.cppreference.com/w/cpp/memory/new/operator_new
	/*at least c++ 17*/
	class MemroyBasic {
	public:
		/*non-allocating placement allocation functions*/
		inline static void * operator new  (std::size_t n, void * a) { return a; (void)n; }
		inline static void * operator new[](std::size_t n, void * a) { return a; (void)n; }
		/*non-allocating placement deallocation functions*/
		inline static void operator delete  (void * a, void * b) { (void)a; (void)b; }
		inline static void operator delete[](void * a, void * b) { (void)a; (void)b; }
		/*class-specific usual deallocation functions*/
		inline static void operator delete  (void * a, std::size_t n) { return sstd::$free(a); (void)n; }
		inline static void operator delete[](void * a, std::size_t n) { return sstd::$free(a); (void)n; }
		inline static void operator delete  (void * p, std::size_t n, std::align_val_t a) { return ::operator delete  (p, n, a); }
		inline static void operator delete[](void * p, std::size_t n, std::align_val_t a) { return ::operator delete[](p, n, a); }
		/*class-specific allocation functions*/
		inline static void * operator new  (std::size_t n) { return sstd::$malloc(n); }
		inline static void * operator new  (std::size_t c, std::align_val_t a) { return ::operator new  (c, a); }
		inline static void * operator new[](std::size_t n) { return sstd::$malloc(n); }
		inline static void * operator new[](std::size_t c, std::align_val_t a) { return ::operator new[](c, a); }
	};

}/*namespace sstd*/

#ifndef SSTD_MEMOEY_OPERATOR
#define SSTD_MEMOEY_OPERATOR(...) public : inline static void * operator new  (std::size_t n, void * a) { return sstd::MemroyBasic::operator new  (n, a); } \
inline static void * operator new[](std::size_t n, void * a) { return sstd::MemroyBasic::operator new[](n, a); } \
inline static void operator delete  (void * a, void * b) { return sstd::MemroyBasic::operator delete  (a,b); } \
inline static void operator delete[](void * a, void * b) { return sstd::MemroyBasic::operator delete[](a, b); } \
inline static void operator delete  (void * a, std::size_t n) { return sstd::MemroyBasic::operator delete  (a, n); } \
inline static void operator delete[](void * a, std::size_t n) { return sstd::MemroyBasic::operator delete[](a, n); } \
inline static void operator delete  (void * p, std::size_t n, std::align_val_t a) { return sstd::MemroyBasic::operator delete  (p, n, a); } \
inline static void operator delete[](void * p, std::size_t n, std::align_val_t a) { return sstd::MemroyBasic::operator delete[](p, n, a); } \
inline static void * operator new  (std::size_t n) { return sstd::MemroyBasic::operator new(n); } \
inline static void * operator new  (std::size_t c, std::align_val_t a) { return sstd::MemroyBasic::operator new  (c, a); } \
inline static void * operator new[](std::size_t n) { return sstd::MemroyBasic::operator new[](n); } \
inline static void * operator new[](std::size_t c, std::align_val_t a) { return sstd::MemroyBasic::operator new[](c, a); } 
#endif

#endif

#endif

