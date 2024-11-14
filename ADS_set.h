#ifndef ADS_SET_H
#define ADS_SET_H


template<typename Key, size_t N=5> class ADS_set{
public: 
	using value_type = Key;
	using key_type = Key;
	using reference = value_type &;
	using const_reference = const value_type &;
	using size_type = size_t;
	using difference_type = std::ptrdiff_t;
	//using const_iterator = /* constant ForwardIterator */
	//using iterator = const_iterator;
	using key_compare = std::less<key_type>;   // B+-Tree
	using key_equal = std::equal_to<key_type>; // Hashing
	using hasher = std::hash<key_type>;        // Hashing
		
private:
	//Instancevariables
	struct Entry{
		Key key; 
		Entry* next{nullptr}; 
		bool occupied{false}; 
		Entry& operator=(const Entry& other){
			this.key=other.key; 
			this.next=other.next; 
			this.occupied=other.occupied; 
			return *this; 
		}
	};
	Entry* table{nullptr};
	size_t current_size{0};
	size_t capacity{N};
	
	void allocate(size_t new_capacity) {
        	Entry* new_table = new Entry[new_capacity];
        	if (table!=nullptr) {
            		for (size_t i=0; i<capacity; i++) {
				new_table[i]=table[i];
            		}
            	delete[] table; 
        	}	
        	table=new_table; 
        	capacity=new_capacity;
    	}
public:
	//Constructors
	ADS_set(): current_size{0}{
		table=new Entry[N];
	};
	ADS_set(std::initializer_list<key_type> ilist):current_size{0}{
		table=new Entry[N];
		insert(ilist);
	}
	template<typename InputIt> ADS_set(InputIt first, InputIt last): current_size{0}{
		table=new Entry[N];
		while(first!=last){
			insert(*first); 
			first++;
		}
	}
	ADS_set(const ADS_set &other);
	//Destructors
	~ADS_set(){
		delete[] table;
	}

	size_t size() const{
		return current_size;
	}
	bool empty() const{
		return current_size==0;
	}
	void insert(std::initializer_list<key_type> ilist){
		for(key_type x: ilist){
			insert(x);
		}
	}
 	size_t count(const key_type &key) const {
        	size_t KeyHash = hasher()(key) % capacity;
        	Entry* current = &table[KeyHash];
        	while (current != nullptr) {
            		if (current->occupied && current->key == key){
                		return 1;
            		}
            		current = current->next; 
        	}
        	return 0;
    	} 
	void insert(Key key) {
		if(current_size>=capacity)rehash();
        	size_t KeyHash = hasher()(key) % capacity;
        	Entry* current = &table[KeyHash];
        	while (current->occupied==true) {
            		if (current->next != nullptr) {
                		current = current->next;
            		} 
            		else {
                		current->next = new Entry{key};
                		current->next->occupied = true;
				current_size++;
                		break;
            		}
        	}
        	if (current->occupied==false) {
            		current->key = key;
            		current->occupied = true;
			current_size++;
        	}
    	}
	template<typename InputIt>void insert(InputIt first, InputIt last) {
    		for(InputIt it=first; first!=last; it++){
        		insert(*it);  
    		}
	}
	void rehash() {
    		size_t new_capacity = capacity * 2;  
    		Entry* new_table = new Entry[new_capacity]; 
    		for (size_t i = 0; i < capacity; ++i) {
        		if (table[i].occupied) {
            			size_t new_index = hasher()(table[i].key) % new_capacity; 
            			Entry* current = &new_table[new_index];
            			while (current->occupied) {
                			if (current->next != nullptr) {
                    				current = current->next;
                			}
				       	else {
                    				current->next = new Entry{table[i].key};
                    				current->next->occupied = true;
                    				break;
                			}
            			}
            			if (!current->occupied) {
                			current->key = table[i].key;
                			current->occupied = true;
            			}
        		}
    		}
    		delete[] table;
    		table = new_table;
    		capacity = new_capacity;
	}
	void dump(std::ostream& o = std::cerr) const {
        	o << "Dumping ADS_set contents:" << std::endl;
        	for (size_t i = 0; i < capacity; ++i) {
            		o << "Index " << i << ": ";
            		if (table[i].occupied) {
                		Entry* current = &table[i];
               			 while (current != nullptr) {
                    			o << current->key << " -> ";
                    			current = current->next; // Move to the next entry in case of chaining
                		}
                		o << "null" << std::endl;
            		}
            		else {
                		o << "empty" << std::endl;
            		}
        	}
        	o << "End of dump." << std::endl;
    	}
};
#endif
