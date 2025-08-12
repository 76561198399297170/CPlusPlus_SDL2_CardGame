#ifndef _SINGLETON_H_
#define _SINGLETON_H_

#include <mutex>

template <typename T>
class Singleton
{
protected:
	Singleton() = default;
	~Singleton() = default;

	Singleton(const Singleton<T>&) = delete;
	Singleton& operator=(const Singleton<T>& st) = delete;

	static T* _manager;

public:
	static T* getInstance()
	{
		static std::once_flag s_flag;
		std::call_once(s_flag, [&]()
			{
				_manager = new T();
			});

		return _manager;
	}

};

template<typename T>
T* Singleton<T>::_manager = nullptr;

#endif