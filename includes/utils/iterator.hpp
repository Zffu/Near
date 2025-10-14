#include <vector>

template <typename T> class VecIterator {
	std::vector<T>::iterator it;

public:
	VecIterator(std::vector<T>::iterator init): it(init) {}
	
	T& operator*() return *it;
	VecIterator& operator++() {
		++it;
		return *this;
	}

	bool operator!=(const VecIterator& other) const {
		return it != other.it;
	}

};