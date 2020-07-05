#include "MD5Array.hpp"
#include <cstring>
#include <boost/format.hpp>

namespace MD5Utils {

bool operator==(const MD5Array& lhs, const MD5Array& rhs) noexcept {
    return !strncmp(reinterpret_cast<const char*>(lhs._md.data()), 
                    reinterpret_cast<const char*>(rhs._md.data()), MD5_DIGEST_LENGTH);
}

std::ostream& operator<<(std::ostream& os, const MD5Array& md) {
    for(size_t i = 0; i < md._md.size(); ++i) {
        os << boost::format("%02x") % +md._md[i];
    }
    return os;
}

template<>
constexpr bool isMD5<MD5Array>(const MD5Array&) noexcept {
    return true;
}

}  // namespace MD5Utils