#ifndef HASH_HPP
#define HASH_HPP

#include <cassert>
#include <cstring>
#include <cstdint>
#include <algorithm>
#include <emmintrin.h>

constexpr uint32_t unfilled = -1;
constexpr uint32_t buff_size = sizeof(uint32_t);

class CuckooHash {
private:
	/* data */
	uint32_t capacity;
	uint32_t mask;
	uint32_t size;
	uint32_t *hashtable;

	void rehash(uint32_t **_table) {
		uint32_t oldcapacity = capacity;
		mask = mask == 0 ? 1 : ((mask << 1) | 1);
		capacity = (mask + 1) * buff_size;
		uint32_t *newhash = new uint32_t[capacity];
		memset((newhash), unfilled, sizeof(uint32_t) * capacity);
		for (uint32_t i = 0; i < oldcapacity; ++i){
			if ((*_table)[i] != unfilled) insert((*_table)[i], &newhash);
		}
		std::swap((*_table), newhash);
		delete[] newhash;
	}
    
	void insert(const uint32_t &_u, uint32_t **_table) {
		
		uint32_t hs = hash1(_u);
		for (uint32_t i = 0; i < buff_size; ++i) {
			if ((*_table)[hs * buff_size + i] == unfilled){
				(*_table)[hs * buff_size + i] = _u;
				return;
			}
		}
		hs = hash2(_u);
		for (uint32_t i = 0; i < buff_size; ++i) {
			if ((*_table)[hs * buff_size + i] == unfilled){
				(*_table)[hs * buff_size + i] = _u;
				return;
			}
		}

		bool use_hash1 = true;
		uint32_t u = _u;
		for (uint32_t i = 0; i < mask; ++i) {
			uint32_t replaced;
			if (use_hash1) hs = hash1(u);
			else hs = hash2(u);
			uint32_t j = 0;
			for (; j < buff_size; ++j) {
				if ((*_table)[hs * buff_size + j] == unfilled) break;
			}
			if (buff_size == j) {
				//replaced = std::move((*_table)[hs * buff_size]);
				replaced = (*_table)[hs * buff_size];
				j = 1;
				for (; j < buff_size; j++) {
					// (*_table)[hs * buff_size + j - 1] =
					// 	std::move((*_table)[hs * buff_size + j]);
					(*_table)[hs * buff_size + j - 1] = (*_table)[hs * buff_size + j];
				}
				(*_table)[hs * buff_size + j - 1] = u;
			}
			else {
				// replaced = std::move((*_table)[hs * buff_size + j]);
				replaced = (*_table)[hs * buff_size + j];
				(*_table)[hs * buff_size + j] = u;
			}
			use_hash1 = hs == hash2(replaced);
			//u = std::move(replaced);
			u = replaced;
			if (u == unfilled) return;
		}
		rehash(_table);
		insert(u, _table);
	}

	uint32_t hash1(const uint32_t &x) const { return x & mask;}
	uint32_t hash2(const uint32_t &x) const { return ~x & mask;}

public:
	CuckooHash(/* args */) {
		capacity = 0;
		hashtable = NULL;
		mask = 0;
		size = 0;
	}
	~CuckooHash() {
		// if (hashtable) delete[] hashtable;
	}

	void reserve(uint32_t _size) {
		if (capacity >= _size) return;
		mask = mask == 0 ? 1 : ((mask << 1) | 1);
		while (_size >= mask * buff_size) mask = (mask << 1) | 1;
		capacity = (mask + 1) * buff_size;
		if (hashtable) delete[] hashtable;
		hashtable = new uint32_t[capacity];
		memset(hashtable, unfilled, sizeof(uint32_t) * capacity);
	}

	void insert(const uint32_t &_u) {
		if (size == capacity) rehash(&hashtable);
		if (find(_u)) return;
		insert(_u, &hashtable);
		size++;
	}

	bool find(const uint32_t &_u) const {
		if (size == 0) return false;
		uint32_t hs1 = hash1(_u);
		uint32_t hs2 = hash2(_u);
	
		assert(buff_size == 4 && sizeof(uint32_t) == 4);
		__m128i cmp = _mm_set1_epi32(_u);
		__m128i b1 = _mm_load_si128((__m128i*)&hashtable[buff_size * hs1]);
		__m128i b2 = _mm_load_si128((__m128i*)&hashtable[buff_size * hs2]);
        __m128i flag = _mm_or_si128(_mm_cmpeq_epi32(cmp, b1), _mm_cmpeq_epi32(cmp, b2));

		return _mm_movemask_epi8(flag) != 0;
	}
	uint32_t getcapacity() {return capacity;}
	uint32_t getsize() {return size;}
	uint32_t getmask() {return mask;}
	uint32_t *gethashtable() {return hashtable;}

	bool operator[](const uint32_t &_u) const {
		return find(_u);
	}
};

#endif	