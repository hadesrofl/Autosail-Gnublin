#include "gcd.h"

GCD::GCD(){

}
uint32_t GCD::gcd(uint32_t a, uint32_t b){
	while (b != 0) {
		int r = a % b;
		a = b;
		b = r;
	}
	return a;
}
uint32_t GCD::gcd_vector(std::vector<uint32_t> vector, uint32_t start, uint32_t end){
	if (start < end) {
				uint32_t middle = (start + end) / 2;
				uint32_t d1 = 0;
				uint32_t d2 = 0;
				uint32_t tmp = 0;
				// Case for length 2
				if (middle == 0) {
					return gcd(vector.at(0), vector.at(1));
				}
				// Case for length 3
				else if (middle == 1) {
					d1 = gcd(vector.at(0), vector.at(1));
					return gcd(d1, vector.at(2));
				}
				// Everything else
				else if (d1 == 0 && middle >= 2) {
					d1 = gcd(vector.at(0), vector.at(1));
					for (uint32_t i = 2; i < middle; i++) {
						tmp = gcd(d1, vector.at(i));
						if (tmp < d1)
							d1 = tmp;
					}
					d2 = gcd(vector.at(middle), vector.at(middle + 1));
					for (uint32_t i = middle; i < vector.size(); i++) {
						tmp = gcd(d2, vector.at(i));
						if (tmp < d2)
							d2 = tmp;
					}
				}
				return gcd(d1, d2);
			}
			// Case for length 1
			return 0 <= start && start < vector.size() ? vector.at(start) : 0;
}
GCD::~GCD(){

}




