#include "PINBruteForce.hpp"
#include <cstring>

namespace MD5Utils {

std::vector<unsigned char> PINBruteForcer<DYNAMIC_PIN>::force(const MD5Array& md5, const size_t PINSize) {
    if (PINSize == 0) {
        throw std::domain_error{"PinSize must be greather than 0."};
    }

    bool pinFinded = false;
    std::vector<unsigned char> truePin(PINSize);
    const uintmax_t combinations = std::pow<uintmax_t>(10, PINSize);
#pragma omp parallel default(none) shared(md5, truePin, pinFinded)
{
    MD5Array resultMD5 = md5;
    std::vector<unsigned char> pin(PINSize);
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
                strcpy(reinterpret_cast<char*>(truePin.data()), reinterpret_cast<const char*>(pin.data()));
            }
        }
    }
}
    if (!pinFinded) {
        throw std::range_error{"PIN contains a different number of digits."};
    }

    return truePin;
}

}  // namespace MD5Utils