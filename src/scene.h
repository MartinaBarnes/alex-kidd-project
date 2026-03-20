#include <vector>
#include "entity.h"

class Scene {
  public:
    std::vector<Entity*> entities = {};

    void update(float);
};
