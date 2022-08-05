/// Thread Safe Map (packaged by c++ map)
/// @author Folivora Li
/// @email 1015553652@qq.com
/// worked at windows
/// 

#pragma once
#ifndef __TSMAP
#define __TSMAP


#include <iostream>
#include <map>
using namespace std;


#if _WIN32
#include <mutex>

#define UPPER_BOUND m_slock.lock();auto res = _Mybase::upper_bound(_Keyval);m_slock.unlock();return res;

#define LOWER_BOUND m_slock.lock();auto res = _Mybase::lower_bound(_Keyval);m_slock.unlock();return res;


/// <summary>
/// 封装插入，插入时不能读写
/// </summary>
/// <typeparam name="_Key"></typeparam>
/// <typeparam name="_Value"></typeparam>
template<class _Key, class _Value>
class TSMap : protected map<_Key, _Value>
{
protected:
	// map<_Key, _Value> m_map;
	
	mutex m_xlock;
	mutex m_slock;

public:

	// typename 用来告诉编译器 这个玩意是个类型名而不是变量名，因为这里的类作用域分辨符不能代表后面的东西是变量还是类型

	using _Mybase = map<_Key, _Value>;
	using _Nodeptr = typename _Mybase::_Nodeptr;
	using mapped_type = _Value;
	using key_type = _Key;

	using iterator = typename _Mybase::iterator;
	using const_iterator = typename _Mybase::const_iterator;
	using reverse_iterator = typename _Mybase::reverse_iterator;
	using const_reverse_iterator = typename _Mybase::const_reverse_iterator;


	// 子类不能拿父类来构造。。。因为没有显式定义父类对象
	TSMap():_Mybase()
	{

	}

	TSMap(const TSMap<_Key, _Value>& _map) :_Mybase(_map)
	{

	}

	TSMap(const TSMap<_Key, _Value>&& _map) :_Mybase(_map)
	{

	}



	// 除构造函数外，不要调用
	// public map<_Key, _Value>& GetMap();
	pair<iterator, bool> insert(pair<_Key, _Value> _pair)
	{
		m_xlock.lock();
		m_slock.lock();
		pair<iterator, bool> res = _Mybase::insert(_pair);
		m_slock.unlock();
		m_xlock.unlock();
		return res;
	}

	TSMap& operator=(const TSMap&& _Right) {
		m_xlock.lock();
		m_slock.lock();
		_Mybase::operator=(std::move(_Right));
		m_slock.unlock();
		m_xlock.unlock();
		return *this;
	}


	TSMap& operator=(const TSMap& _Right) {
		m_xlock.lock();
		m_slock.lock();
		_Mybase::operator=(_Right);
		m_slock.unlock();
		m_xlock.unlock();
		return *this;
	}

	mapped_type& operator[](key_type&& _Keyval) { // find element matching _Keyval or insert value-initialized value
		m_xlock.lock();
		m_slock.lock();
		mapped_type& res = _Mybase::operator[](_Keyval);

		m_slock.unlock();
		m_xlock.unlock();
		return res;
	}

	iterator find(key_type _Keyval)
	{
		m_slock.lock();

		iterator res = _Mybase::find(_Keyval);

		m_slock.unlock();
		
		return res;
	}
	

	_NODISCARD iterator begin() noexcept {
		return _Mybase::begin();
	}


	
	_NODISCARD iterator end() noexcept {
		return _Mybase::end();
	}

	_NODISCARD reverse_iterator rbegin() noexcept {
		return _Mybase::rbegin();
	}

	_NODISCARD const_reverse_iterator rbegin() const noexcept {
		return _Mybase::rbegin();
	}

	_NODISCARD reverse_iterator rend() noexcept {
		return _Mybase::rend();
	}

	_NODISCARD const_reverse_iterator rend() const noexcept {
		return _Mybase::rend();
	}

	int size()
	{
		return _Mybase::size();
	}

	void clear()
	{
		m_xlock.lock();
		m_slock.lock();
		_Mybase::clear();
		m_slock.unlock();
		m_xlock.unlock();
	}

	int count(key_type _Keyval)
	{
		return _Mybase::count(_Keyval);
	}


	template <class... _Valtys>
	pair<iterator, bool> emplace(_Valtys&&... _Vals) {

		m_xlock.lock();
		m_slock.lock();
		pair<iterator, bool> res = _Mybase::emplace(_Vals);
		m_slock.unlock();
		m_xlock.unlock();
		return res;
	}

	// 返回值是擦除的元素的下一个位置
	iterator erase(const_iterator _Where) noexcept
	{
		m_xlock.lock();
		m_slock.lock();
		auto res = _Mybase::erase(_Where);
		m_slock.unlock();
		m_xlock.unlock();
		return res;
	}

	iterator erase(const_iterator _First, const_iterator _Last) noexcept
	{
		m_xlock.lock();
		m_slock.lock();
		auto res = _Mybase::erase(_First, _Last);
		m_slock.unlock();
		m_xlock.unlock();
		return res;
	}


	// 返回值是擦除的元素个数，multimap中可能会 > 1，但在map中就只有0和1
	int erase(const key_type& _Keyval) noexcept
	{
		m_xlock.lock();
		m_slock.lock();
		int res = _Mybase::erase(_Keyval);
		m_slock.unlock();
		m_xlock.unlock();
		return res;
	}

	_NODISCARD iterator upper_bound(const key_type& _Keyval)
	{
		UPPER_BOUND
	}

	_NODISCARD const_iterator upper_bound(const key_type& _Keyval) const
	{
		UPPER_BOUND
	}

	_NODISCARD iterator lower_bound(const key_type& _Keyval)
	{
		LOWER_BOUND
	}

	_NODISCARD const_iterator lower_bound(const key_type& _Keyval) const
	{
		LOWER_BOUND
	}

	bool empty()
	{
		return _Mybase::empty();
	}

	void swap(TSMap& _map) noexcept
	{
		_Mybase::swap(_map);
	}
	

	
};



#endif // __cplusplus



#endif // __TSMAP