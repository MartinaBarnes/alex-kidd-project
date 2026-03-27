#include <vector>
#include "Entity.h"

class Scene {
  public:
    std::vector<Entity*> entities = {};

    void push(Entity*);
    void pop(Entity*);
    void update(float);
    ~Scene();
};
