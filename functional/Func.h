#ifndef FUNC_H
#define FUNC_H

#include <functional>
#include <algorithm>
#include <vector>

namespace func {
	
template <typename collection, typename callback>
void forEach(collection col, callback cb) {
	std::for_each(col.begin(), col.end(), cb);
}

template <typename collection, typename callback>
collection map(collection col, callback cb) {
	std::transform(col.begin(), col.end(), col.begin(), cb);
	return col;
}

template <typename collection, typename predicate>
collection filterNot(collection col, predicate pr) {   
    auto returnIterator = std::remove_if(col.begin(), col.end(), pr);
    col.erase(returnIterator, std::end(col));    
    return col;
}

template <typename collection, typename predicate>
collection filter(collection col, predicate pr) {
	auto fnCol = filterNot(col, [pr](typename collection::value_type i) { return !pr(i);});
	return fnCol; 
}

template <typename collection, typename reducer>
typename collection::value_type reduce(collection col, reducer rd, typename collection::value_type acc) {
	for(auto it: col) {
		acc = rd(acc, it);
	}
	return acc;
}

template <typename col1, typename col2, typename with>
std::vector<typename with::result_of::type> zipWith(col1 a, col2 b, with cb) {
	std::vector <typename with::result_of::type> result;
	for (auto it : a) {
		result.push_back(cb(a, b));
	}
	return result;
}

template <typename collection, typename predicate>
bool any(collection col, predicate pr) {
	return std::any_of(col.begin(), col.end(), pr);
}

template <typename collection, typename predicate>
bool all(collection col, predicate pr) {
	return std::all_of(col.begin(), col.end(), pr);
}

}

#endif