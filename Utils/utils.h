#ifndef _ASSERT_H_
#define _ASSERT_H_

#include <functional>
#include <stdexcept>
#include <string>
#include <vector>

namespace utils {
	class NotImplementedException : public std::logic_error {
	public:
		NotImplementedException(std::string method_name) : std::logic_error("Method " + method_name + " not implemented.") {}
	};

	extern int assert(std::function<int()> predicate);
	extern int runtest(std::string label, std::vector<std::function<int()>> tests);
}

#endif