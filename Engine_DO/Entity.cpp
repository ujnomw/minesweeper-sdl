#include "Entity.h"

namespace Entity
{

Entity::Entity(EntityId i_id) : d_id(i_id) {}
Entity::~Entity()
{
    printf("Entity destructor: %s, id: %d \n", d_type.c_str(), d_id);
    if (TextSurface)
    {
        SDL_FreeSurface(TextSurface);
        TextSurface = nullptr;
    }
    if (Font)
    {
        TTF_CloseFont(Font);
        Font = nullptr;
    }
}
Entity::Entity(const Entity& rhs)
    : d_id(rhs.d_id),
      d_type(rhs.d_type),
      d_backgroundColor(rhs.d_backgroundColor),
      TextSurface(rhs.TextSurface),
      Font(rhs.Font),
      Color(rhs.Color),
      ImageSurface(rhs.ImageSurface)
{
}

Entity& Entity::operator=(const Entity& rhs)
{
    d_id = rhs.d_id;
    d_type = rhs.d_type;
    d_backgroundColor = rhs.d_backgroundColor;
    TextSurface = rhs.TextSurface;
    Font = rhs.Font;
    Color = rhs.Color;
    ImageSurface = rhs.ImageSurface;
    return *this;
}
Entity& Entity::operator=(Entity&& rhs) noexcept
{
    if (this != &rhs)
    {
        d_id = rhs.d_id;
        d_type = rhs.d_type;
        d_backgroundColor = rhs.d_backgroundColor;
        TextSurface = rhs.TextSurface;
        Font = rhs.Font;
        Color = rhs.Color;
        ImageSurface = rhs.ImageSurface;
    }
    return *this;
}
}  // namespace Entity