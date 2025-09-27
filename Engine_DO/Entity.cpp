#include "Entity.h"

namespace Entity
{

Entity::Entity(EntityId i_id) : d_id(i_id) {}
Entity::~Entity() { deleteResources(); }
void Entity::deleteResources(Entity* entityPtr)
{
    if (!entityPtr) entityPtr = this;
    printf("Entity resources deleted: %s, id: %d \n", entityPtr->d_type.c_str(),
           entityPtr->d_id);
    if (entityPtr->TextSurface)
    {
        SDL_FreeSurface(entityPtr->TextSurface);
        entityPtr->TextSurface = nullptr;
    }
    if (entityPtr->Font)
    {
        TTF_CloseFont(entityPtr->Font);
        entityPtr->Font = nullptr;
    }
    if (entityPtr->ImageSurface)
    {
        SDL_FreeSurface(entityPtr->ImageSurface);
        entityPtr->ImageSurface = nullptr;
    }
}

void Entity::clone(const Entity& rhs)
{
    d_id = rhs.d_id;
    Color = rhs.Color;
    d_type = rhs.d_type;
    d_backgroundColor = rhs.d_backgroundColor;
    if (rhs.ImageSurface)
    {
        ImageSurface = SDL_ConvertSurface(rhs.ImageSurface, rhs.ImageSurface->format, 0);
    }
    if (rhs.TextSurface)
    {
        TextSurface = SDL_ConvertSurface(rhs.TextSurface, rhs.TextSurface->format, 0);
    }
    if (rhs.Font)
    {
        std::string path = "assets/";
        path.append(TTF_FontFaceFamilyName(rhs.Font));
        int height = TTF_FontHeight(rhs.Font);
        Font = TTF_OpenFont(path.c_str(), height);
    }
}

Entity::Entity(const Entity& rhs) { clone(rhs); }

Entity::Entity(Entity&& rhs)
{
    clone(rhs);
    deleteResources(&rhs);
}

Entity& Entity::operator=(const Entity& rhs)
{
    if (this != &rhs)
    {
        deleteResources();
        clone(rhs);
    }
    return *this;
}
Entity& Entity::operator=(Entity&& rhs) noexcept
{
    if (this != &rhs)
    {
        deleteResources();
        d_id = rhs.d_id;
        d_type = rhs.d_type;
        d_backgroundColor = rhs.d_backgroundColor;
        Color = rhs.Color;

        TextSurface = rhs.TextSurface;
        ImageSurface = rhs.ImageSurface;
        Font = rhs.Font;

        rhs.TextSurface = nullptr;
        rhs.ImageSurface = nullptr;
        rhs.Font = nullptr;
    }
    return *this;
}
}  // namespace Entity