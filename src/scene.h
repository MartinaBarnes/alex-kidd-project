#include <vector>
#include "Entity.h"

class Scene {
  public:
    std::vector<Entity*> entities = {};

    void update(float);
};
