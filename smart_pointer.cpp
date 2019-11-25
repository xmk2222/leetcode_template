#include "stdafx.h"
#include "smart_pointer.h"


template<typename T>
class my_shared_ptr {
private:
	T* _ptr;
	size_t* _cnt;
public:
	my_shared_ptr(T* ptr = nullptr) : _ptr(ptr) {
		if (_ptr) _cnt = new size_t(1);
		else _cnt = new size_t(0);
	}

	my_shared_ptr(const my_shared_ptr<T> &ptr) {
		if (this != &ptr) {
			this->_ptr = ptr->_ptr;
			this->_cnt = ptr->_cnt;
			(*this->_cnt)++;
		}
	}

	my_shared_ptr(const my_weak_ptr<T> &ptr) {
		if (ptr->_ptr != nullptr) {
			this->_ptr = ptr->_ptr;
			this->_cnt = ptr->_cnt;
			(*this->_cnt)++;
		}
		else {
			throw "Empty weak_ptr exception!";
		}
	}

	my_shared_ptr<T>& operator= (const my_shared_ptr<T> &ptr) {
		if (this->_ptr == ptr._ptr) return *this;
		if (this->_ptr) {
			(*this->_cnt)--;
			if ((*this->_cnt) == 0) {
				delete this->_ptr;
				delete this->_cnt;
			}
		}
			this->_ptr = ptr._ptr;
			this->_cnt = ptr._cnt;
			(*this->_cnt)++;
			return *this;
	}

	T& operator* () {
		assert(this->_ptr != nullptr);
		return *(this->_ptr);
	}

	T* operator-> () {
		assert(this->_ptr != nullptr);
		return this->_ptr;
	}

	size_t use_count() {
		return *(this->_cnt);
	}


	~my_shared_ptr() {
		(*this->_cnt)--;
		if (*this->_cnt == 0) {
			delete this->_ptr;
			delete this->_cnt;
		}
	}
};

template<typename T>
class my_weak_ptr {
private:
	T* _ptr;
	size_t* _cnt;
public:
	my_weak_ptr(const my_shared_ptr<T> &ptr) {
		this->_ptr = ptr->_ptr;
		this->_cnt = ptr->_cnt;
	}

	my_weak_ptr(const my_weak_ptr<T> &ptr) {
		if (this != &ptr) {
			this->_ptr = ptr->_ptr;
			this->_cnt = ptr->_cnt;
		}
	}

	~my_weak_ptr() {}

	my_weak_ptr<T>& operator= (const my_shared_ptr<T> &ptr) {
		this->_ptr = ptr->_ptr;
		this->_cnt = ptr->_cnt;
		return *this;
	}

	my_weak_ptr<T>& operator= (const my_weak_ptr<T> &ptr) {
		this->_ptr = ptr->_ptr;
		this->_cnt = ptr->_cnt;
		return *this;
	}

	void reset() {
		_ptr = nullptr;
		_cnt = nullptr;
	}

	long use_count() const{
		return *_cnt;
	}

	bool expired() const{
		return *_cnt == 0;
	}

	my_shared_ptr<T> & lock() {
		my_shared_ptr<T> ptr(*this);
		return ptr;
	}
};
