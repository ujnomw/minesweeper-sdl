#pragma once
namespace Layout
{

template <typename T>
class HandleEventStrategy
{
   public:
    virtual ~HandleEventStrategy() = default;
    virtual void HandleEvent(T&, const SDL_Event& E) = 0;
};
}  // namespace Layout
