#pragma

#include <vector>

template <typename T>
concept Renderable = requires(T&& t) {
    { t.Render() } -> std::same_as<void>;
};

template <Renderable R>
class Column
{
   public:
    Column(std::vector<&R>& i_children) {};
    void Render();

   private:
    std::vector<&R> children;
    int padding;
    int gap;
};