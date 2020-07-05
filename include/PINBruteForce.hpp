#ifndef PIN_BRUTE_FORCE_HPP
#define PIN_BRUTE_FORCE_HPP

#include "MD5Array.hpp"
#include <exception>
#include <cmath>
#include <vector>

namespace MD5Utils {

template<size_t PINSize>
struct PINBruteForcer {
    static std::array<unsigned char, PINSize> force(const MD5Array& md5) {
        bool pinFinded = false;
        std::array<unsigned char, PINSize> truePin = {};
        static constexpr uintmax_t combinations = std::pow<uintmax_t>(10, PINSize);
#pragma omp parallel default(none) shared(md5, truePin, pinFinded)
    {
        MD5Array resultMD5 = md5;
        std::array<unsigned char, PINSize> pin = {};
#pragma omp for
        for(uintmax_t i = 0; i < combinations; ++i) {
            if (!pinFinded) {
                uintmax_t temp = i;
                for(size_t j = 0; j < pin.size(); ++j) {
                    pin[j] = '0' + temp % 10;
                    temp /= 10;
                }

                resultMD5.calculate(pin);
                if (resultMD5 == md5) {
                    pinFinded = true;
                    truePin = pin;
                }
            }
        }
    }
    
        if (!pinFinded) {
            throw std::range_error{"PIN contains a different number of digits."};
        }

        return truePin;
    }
};

static constexpr size_t DYNAMIC_PIN = 0;

template<>
struct PINBruteForcer<DYNAMIC_PIN> {
    static std::vector<unsigned char> force(const MD5Array& md5, const size_t PINSize);
};

}  // namespace MD5Utils

#endif