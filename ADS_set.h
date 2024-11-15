#ifndef ADS_SET_H
#define ADS_SET_H

#include <iostream>
#include <functional>
#include <initializer_list>

template<typename Key, size_t N=5>
class ADS_set {
public: 
    using value_type = Key;
    using key_type = Key;
    using reference = value_type &;
    using const_reference = const value_type &;
    using size_type = size_t;
    using difference_type = std::ptrdiff_t;
    using key_compare = std::less<key_type>;
    using key_equal = std::equal_to<key_type>;
    using hasher = std::hash<key_type>;

private:
    struct Entry {
        Key key;
        Entry* next{nullptr};
        bool occupied{false};
        Entry& operator=(const Entry& other) {
            this->key = other.key;
            this->next = other.next;
            this->occupied = other.occupied;
            return *this;
        }
    };
    Entry* table{nullptr};
    size_t current_size{0};
    size_t capacity{N};

    void allocate(size_t new_capacity) {
        Entry* new_table = new Entry[new_capacity];
        if (table != nullptr) {
            for (size_t i = 0; i < capacity; i++) {
                new_table[i] = table[i];
            }
            delete[] table;
        }
        table = new_table;
        capacity = new_capacity;
    }

public:
    ADS_set() : current_size{0} {
        table = new Entry[N];
    }

    ADS_set(std::initializer_list<key_type> ilist) : current_size{0} {
        table = new Entry[N];
        insert(ilist);
    }

    template<typename InputIt>
    ADS_set(InputIt first, InputIt last) : current_size{0} {
        table = new Entry[N];
        while (first != last) {
            insert(*first);
            ++first;
        }
    }

    ADS_set(const ADS_set &other) : current_size(other.current_size), capacity(other.capacity) {
        table = new Entry[capacity];
        for (size_t i = 0; i < capacity; ++i) {
            table[i] = other.table[i];
            if (other.table[i].next) {
                Entry* src = other.table[i].next;
                Entry* dst = table[i].next = new Entry{*src};
                while (src->next) {
                    src = src->next;
                    dst->next = new Entry{*src};
                    dst = dst->next;
                }
            }
        }
    }

    ~ADS_set() {
        for (size_t i = 0; i < capacity; ++i) {
            Entry* current = table[i].next;
            while (current != nullptr) {
                Entry* to_delete = current;
                current = current->next;
                delete to_delete;
            }
        }
        delete[] table;
    }

    size_t size() const {
        return current_size;
    }

    bool empty() const {
        return current_size == 0;
    }

    void insert(std::initializer_list<key_type> ilist) {
        for (key_type x : ilist) {
            insert(x);
        }
    }

    size_t count(const key_type &key) const {
        size_t KeyHash = hasher()(key) % capacity;
        Entry* current = &table[KeyHash];
        while (current != nullptr) {
            if (current->occupied && key_equal{}(current->key,key)) {
		    return 1;
            }
            current = current->next;
        }
        return 0;
    }

    void insert(Key key) {
        if (current_size >= capacity) rehash();
        size_t KeyHash = hasher()(key) % capacity;
        Entry* current = &table[KeyHash];	
	while(current!=nullptr){
		if(current->occupied&&key_equal{}(current->key, key)){
			return; 
		} 
		if(current->next==nullptr){
				break;
		}
		current=current->next; 
	}
	while (current->occupied == true) {
            if (current->next != nullptr) {
                current = current->next;
            } else {
                current->next = new Entry{key};
                current->next->occupied = true;
                current_size++;
                break;
            }
        }
        if (current->occupied == false) {
            current->key = key;
            current->occupied = true;
            current_size++;
        }
    }

    template<typename InputIt>
    void insert(InputIt first, InputIt last) {
        for (InputIt it = first; it != last; ++it) {
            insert(*it);
        }
    }

    void rehash() {
        size_t new_capacity = capacity * 2;
        Entry* new_table = new Entry[new_capacity];
        for (size_t i = 0; i < capacity; ++i) {
            if (table[i].occupied) {
                Entry* current = &table[i];
                while (current) {
                    size_t new_index = hasher()(current->key) % new_capacity;
                    Entry* new_entry = &new_table[new_index];
                    while (new_entry->occupied && new_entry->next) {
                        new_entry = new_entry->next;
                    }
                    if (new_entry->occupied) {
                        new_entry->next = new Entry{current->key};
			new_entry->next->occupied=true;
                    } else {
                        new_entry->key = current->key;
                        new_entry->occupied = true;
                    }
                    current = current->next;
                }
            }
        }
        delete[] table;
        table = new_table;
        capacity = new_capacity;
    }

    void dump(std::ostream& o = std::cerr) const {
        o << "Dumping Set contents:" << std::endl;
        for (size_t i = 0; i < capacity; ++i) {
            o << "Index " << i << ": ";
            if (table[i].occupied) {
                Entry* current = &table[i];
                while (current != nullptr) {
                    o << current->key << " -> ";
                    current = current->next;
                }
                o << "null" << std::endl;
            } else {
                o << "empty" << std::endl;
            }
        }
        o << "End of dump." << std::endl;
    }
};
#endif
