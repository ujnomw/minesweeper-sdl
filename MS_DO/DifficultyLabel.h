#pragma once
#include "Engine_DO/Entity.h"

namespace DifficultyLabel
{
using namespace Entity;
struct InitParams
{
    EntityId id;
    EntityManager& em;
    std::string i_level;
};

extern void init(InitParams&);
}  // namespace DifficultyLabel