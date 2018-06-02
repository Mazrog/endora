//
// Created by mazrog on 12/05/18.
//

#ifndef ENDORA_RENDER_PASS_HPP
#define ENDORA_RENDER_PASS_HPP

#include <functional>

#include <rendering/render_group.hpp>

using VoidFunc = std::function<void()>;

template < typename Object >
class RenderPass {
public:
    using Group = RenderGroup<Object>;

public:
    RenderPass(Group * renderGroup, VoidFunc && prepareFunction);
    ~RenderPass();

    void render() const;

private:
    VoidFunc    prepareFunction;
    Group     * renderGroup;
};

#include <rendering/render_pass.tpp>

#endif
