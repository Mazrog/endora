//
// Created by mazrog on 12/05/18.
//

#ifndef ENDORA_RENDER_PASS_HPP
#define ENDORA_RENDER_PASS_HPP

#include <functional>

using VoidFunc = std::function<void()>;

template < typename Object >
class RenderPass {
public:
    using Group = std::vector<Object>;

public:
    RenderPass(Group * renderGroup, VoidFunc && prepareFunction);
    ~RenderPass();

    void render() const;

    Group const& get_render_group() const;

private:
    VoidFunc    prepareFunction;
    Group     * renderGroup;
};


#include <endora/rendering/render_pass.tpp>

#endif
