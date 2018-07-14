namespace duckhero
{
	template<typename K, typename V>
	LRUCache<K, V>::LRUCache(int in_cache_size, void (*in_evict_callback)(V *))
	{
		cache_size = in_cache_size;
		_evict_callback = in_evict_callback;
	}

	template<typename K, typename V>
	LRUCache<K, V>::~LRUCache()
	{
		if (_evict_callback)
		{
			for (K key : _last_access)
			{
				_evict_callback(&_data[key]);
			}
		}
	}

	template<typename K, typename V>
	void LRUCache<K, V>::Evict()
	{
		while (_last_access.size() > cache_size)
		{
			K key_to_remove = _last_access.front();
			if (_evict_callback)
			{
				_evict_callback(&_data[key_to_remove]);
			}
			typename std::map<K, V>::iterator it = _data.find(key_to_remove);
			_data.erase(it);
			_last_access.pop_front();
		}
	}

	template<typename K, typename V>
	bool LRUCache<K, V>::Exists(K key)
	{
		typename std::map<K, V>::iterator it = _data.find(key);
		return (it != _data.end());
	}

	template<typename K, typename V>
	V LRUCache<K, V>::Get(K key)
	{
		// move this key to the back of the list
		_last_access.splice(_last_access.end(), _last_access, std::find(_last_access.begin(), _last_access.end(), key));

		return _data[key];
	}

	template<typename K, typename V>
	void LRUCache<K, V>::Put(K key, V value)
	{
		_last_access.insert(_last_access.end(), key);
		Evict();
		_data[key] = value;
	}
}