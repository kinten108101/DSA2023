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

	class NullPointerException : public std::logic_error {
	protected:
	    std::string msg = "";
	public:
	    NullPointerException(std::string ptr_name): std::logic_error("Pointer \"" + ptr_name + "\" is null.") {}
	};

	extern int assert(std::function<int()> predicate);
	extern int runtest(std::string label, std::vector<std::function<int()>> tests);
}

#endif