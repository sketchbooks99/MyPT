#include "core/mypt.h"

using namespace mypt;

int main(int /* argc */, const char * argv[]) {
    // Change seed of randaom value
    srand((unsigned)time(NULL));

    std::string filename = argv[1];
    Scene scene(filename);
    scene.render();

    return 0;
}