#include "TSMap.h"

/*
template<class _Key, class _Value>
TSMap<_Key, _Value>::TSMap(): map()
{

}


// 拷贝构造函数
template<class _Key, class _Value>
TSMap<_Key, _Value>::TSMap(const map<_Key, _Value>& _map) : map(_map)
{

}

template<class _Key, class _Value>
TSMap<_Key, _Value>::TSMap(const TSMap& _map): map(_map.GetMap())
{

}

// 移动构造函数
template<class _Key, class _Value>
TSMap<_Key, _Value>::TSMap(const map<_Key, _Value>&& _map) : map(std::move(_map))
{

}

// 移动构造函数
template<class _Key, class _Value>
TSMap<_Key, _Value>::TSMap(const TSMap&& _map) : map(std::move(_map.GetMap()))
{

}
/*
template<class _Key, class _Value>
map<_Key, _Value>&  TSMap<_Key, _Value>::GetMap()
{
	return m_map;
}

template<class _Key, class _Value>
pair<iterator, bool>  TSMap<_Key, _Value>::insert(pair<_Key, _Value> _pair)
{
	m_xlock.lock();
	m_slock.lock();

	m_map.insert(_pair);

	m_slock.unlock();
	m_xlock.unlock();
}
*/

int main()
{
	map<int, int> _map2;
	_map2[2] = 2;
	_map2[1] = 2;
	_map2[3] = 5;
	_map2[0] = 0;
	_map2[4] = 9;
	// _map2.swap();
	auto x = _map2.erase(1);
	cout << x << endl;
	_map2.emplace();
	
	// _map2.upper_bound()
	//_map2.emplace();
	// _map2.erase();
	// _map2.erase();
	TSMap<int, int> _map;
	TSMap<int, int> _map1;
	_map.insert(pair<int, int>(1, 1));
	
	_map.find(1);
	TSMap<int, int>::iterator iter;
	for (iter = _map.begin(); iter != _map.end(); iter++)
	{
		cout << iter->first ;
	}

	cout << _map[1] << endl;
	// _map = _map1;

	cout << _map.size();

	_map.swap(_map1);
	// _map.swap(_map2);
	TSMap<int, int> map3(_map1);

	auto it = map3.upper_bound(3);
	
}