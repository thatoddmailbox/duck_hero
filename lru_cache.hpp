#ifndef _LRU_CACHE_HPP
#define _LRU_CACHE_HPP

#include <algorithm>
#include <list>
#include <map>

namespace duckhero
{
	template<typename K, typename V>
	class LRUCache
	{
	private:
		std::map<K, V> _data;
		std::list<K> _last_access;
		void (*_evict_callback)(V *);

	public:
		int cache_size;

		LRUCache(int in_cache_size, void (*in_evict_callback)(V *));
		~LRUCache();

		void Evict();
		bool Exists(K key);
		V Get(K key);
		void Put(K key, V value);
	};
}

#include "lru_cache_impl.hpp"

#endif