#ifndef _UNUQVECTOR_hpp
#define _UNUQVECTOR_hpp

#include <memory>
#include <exception>
#include <stdexcept>
#include <memory_resource>

template<typename __T, typename __A = std::allocator<__T/**/>/**/>
class UniqueVector {
	__T * _data_;
	__A _alc_;

	static inline __T * __construct(__T * data) {
		return ::new (data) __T{};
	}

	template<typename ... Args>
	static inline __T * __construct(__T * data, Args && ...args) {
		if constexpr(std::is_constructible_v<__T, Args && ...>) {
			return ::new (data) __T(std::forward<Args>(args)...);
		}
		else {
			return ::new (data) __T{ std::forward<Args>(args)... };
		}
	}

	static inline void __destory(__T * arg) {
		std::destroy_at(arg);
	}

	static inline __T * __malloc_one(__A * a) {
		return a->allocate(1);
	}

	static inline void __free_one(__T * arg, __A * a) {
		a->deallocate(arg, 1);
	}

	inline void _this_destruct() {
		if (_data_) { __destory(_data_); __free_one(_data_, &_alc_); }
	}
	
public:
	inline UniqueVector() :_data_(nullptr) {}
	inline UniqueVector(const __A & alc) : _data_(nullptr), _alc_(alc) {}
	inline UniqueVector(__T * a, const __A & alc) : _data_(a), _alc_(alc) {}
	class construct_direct {};
	template<typename ... Args>
	inline UniqueVector(const construct_direct &, const __A & alc, Args && ... args) : UniqueVector(alc) {
		construct<false>(std::forward<Args>(args)...);
	}

	UniqueVector(const UniqueVector&) = delete;
	UniqueVector&operator=(const UniqueVector&) = delete;
	UniqueVector(UniqueVector&&) = default;
	UniqueVector&operator=(UniqueVector&&) = default;

	template<bool NeedDestruct = true, typename ... Args>
	inline __T & construct(Args && ...args) {
		if constexpr(NeedDestruct) {
			_this_destruct();
		}

		try {
			_data_ = __malloc_one(&_alc_);
		}
		catch (...) {
			_data_ = nullptr;
			throw;
		}

		if (_data_) {
			try {
				__construct(_data_, std::forward<Args>(args)...);
			}
			catch (...) {
				__free_one(_data_, &_alc_);
				_data_ = nullptr;
				throw;
			}
		}
		else {
			throw std::bad_alloc{};
		}

		return *_data_;
	}

	__T * operator->() { return _data_; }
	const __T * operator->() const { return _data_; }

	__T & operator*() { return *_data_; }
	const __T & operator*() const { return *_data_; }

	operator bool() const { return _data_; }
	__T * data() { return _data_; }
	const __T * data() const { return _data_; }

	inline ~UniqueVector() { _this_destruct(); }

	std::shared_ptr<__T> to_std_shared_ptr() {
		std::shared_ptr<__T> varAns;
		try {
			varAns = std::shared_ptr<__T>(_data_, [_alc_ = this->_alc_](__T * _data_) mutable {
				if (_data_) {
					__destory(_data_);
					__free_one(_data_, &_alc_);
				}
			}, this->_alc_);
		}
		catch (...) { throw; }
		_data_ = nullptr;
		return std::move(varAns);
	}
};

template<typename T, typename Alc, typename ... Args>
inline UniqueVector<T, Alc> allocate_unique(const Alc&arg, Args && ... args) {
	using Tx = UniqueVector<T, Alc>;
	return Tx{ typename Tx::construct_direct{} ,arg,std::forward<Args>(args)... };
}

template<typename T, typename Alc = std::pmr::polymorphic_allocator<T>, typename ... Args>
inline UniqueVector<T, Alc> make_unique(Args && ... args) {
	return allocate_unique<T>(Alc{}, std::forward<Args>(args)...);
}

#endif


