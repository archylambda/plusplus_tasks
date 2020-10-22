#include <iostream>

int main(){

    uint64_t N, dens;
    std::cin >> N >> dens;

    uint64_t res = 0;
    for(int i = 0; i != N; ++i){
        uint64_t w, h, d;
        std::cin >> w >> h >> d;
        
        res += dens*w*h*d;
    }

    std::cout << res << std::endl;

    return 0;
}