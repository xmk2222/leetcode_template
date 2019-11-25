
#include "stdafx.h"
#include <memory>
#include <mutex>
#include <iostream>
using namespace std;


class Singleton {
	// 带锁的线程安全的懒汉单例模式
private:
	static shared_ptr<Singleton> m_pInstance; // static的指针实现单例
	static mutex m_mutex;
	Singleton() { // 只能通过自己的static函数调用
		cout << "Singleton constructed." << endl;
	}
	Singleton(Singleton &) = delete; // 外部只能得到指针，因此可以不写
	Singleton& operator=(const Singleton&) = delete;

public:
	~Singleton() {
		cout << "Singleton destructed" << endl;
	}
	static shared_ptr<Singleton> getInstance() {
		if (m_pInstance == nullptr) {
			lock_guard<mutex> lk(m_mutex);
			if (m_pInstance == nullptr) {
				m_pInstance = shared_ptr<Singleton>(new Singleton);
			}
		}
		return m_pInstance;
	}
};
shared_ptr<Singleton> Singleton::m_pInstance = NULL;
mutex Singleton::m_mutex;


class Singleton2 {
	// 通过局部静态变量实现的线程安全的懒汉单例模式
public:
	Singleton2& operator=(const Singleton2& a) = delete;
	Singleton2(const Singleton2&) = delete;
	static Singleton2& getInstance() {
		static Singleton2 instance;
		return instance;
	}
	~Singleton2() {
		cout << "Singleton2 destructed" << endl;
	}
private:
	Singleton2() {
		cout << "Singleton2 constructed" << endl;
	}
};


template<typename T>
class Singleton3 {
	// 单例模式模板
public:
	static T& getInstance() {
		static T instance;
		return instance;
	}
	virtual ~Singleton3() {
		cout << "Singleton3 destructed" << endl;
	}
	Singleton3(const Singleton3&) = delete;
	Singleton3& operator=(const Singleton3&) = delete;
protected:
	Singleton3() {
		cout << "Singleton3 constructed" << endl;
	}
};

class DerivedSingle :public Singleton3<DerivedSingle> {
	friend class Singleton3<DerivedSingle>;
public:
	DerivedSingle(const DerivedSingle&) = delete;
	DerivedSingle& operator=(const DerivedSingle&) = delete;
private:
	DerivedSingle() = default;
};

void test_singleton() {
	shared_ptr<Singleton> p1 = Singleton::getInstance();
	shared_ptr<Singleton> p2 = p1;

	Singleton2 *p3 = &Singleton2::getInstance();
	Singleton2 *p4 = &Singleton2::getInstance();
	DerivedSingle &p5 = DerivedSingle::getInstance();
	DerivedSingle &p6 = DerivedSingle::getInstance();
}
