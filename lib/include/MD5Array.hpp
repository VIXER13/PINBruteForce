#ifndef MD5_ARRAY_HPP
#define MD5_ARRAY_HPP

#include <array>
#include <iostream>
#include <openssl/md5.h>

namespace MD5Utils {

template<class Container>
bool isMD5(const Container& md) noexcept {
    static_assert(std::is_integral<typename Container::value_type>{}, "The Container::value_type must be integral type");

    if (md.size() != 2 * MD5_DIGEST_LENGTH) {
        return false;
    }

    for(auto it = md.cbegin(); it != md.cend(); ++it) {
        const char temp = std::tolower(*it);
        if ((temp < '0' || temp > '9') && (temp < 'a' || temp > 'f')) {
            return false;
        }
    }

    return true;
}

class MD5Array {
    std::array<unsigned char, MD5_DIGEST_LENGTH> _md = {};

public:
    enum initType : uint8_t {COMPRESS, CALCULATE};

    template<class Container>
    MD5Array(const Container& md, const initType init) {
        if (init == initType::COMPRESS) {
            compress(md);
        } else {
            calculate(md);
        }
    }

    template<class Container>
    void compress(const Container& md) {
        if (!isMD5(md)) {
            throw std::domain_error{"This is not MD5."};
        }

        static constexpr auto toHex = [](const auto c) noexcept {
            return c >= '0' && c <= '9' ? c - '0' : std::tolower(c) - 'a' + 10;
        };

        auto it = md.cbegin();
        for(size_t i = 0; i < MD5_DIGEST_LENGTH; ++i) {
            _md[i] = static_cast<unsigned char>(toHex(*it) << 4 | toHex(*std::next(it)));
            it = std::next(it, 2);
        }
    }

    // Важное требование: подаваемый контейнер должен содержать в себе непрерывный кусок памяти.
    template<class Container>
    void calculate(const Container& md) noexcept {
        MD5(reinterpret_cast<const unsigned char*>(md.data()), md.size(), _md.data());
    }
    
    friend bool operator==(const MD5Array& lhs, const MD5Array& rhs) noexcept;
    friend std::ostream& operator<<(std::ostream& os, const MD5Array& md);
};

template<>
constexpr bool isMD5<MD5Array>(const MD5Array&) noexcept;

}  // namespace MD5Utils

#endif