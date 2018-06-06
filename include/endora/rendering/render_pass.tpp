//
// Created by mazrog on 12/05/18.
//

template < typename Object >
RenderPass<Object>::RenderPass(RenderGroup<Object> * renderGroup, VoidFunc && prepareFunction)
        : prepareFunction(std::move(prepareFunction)), renderGroup(renderGroup) {}


template < typename Object >
RenderPass<Object>::~RenderPass() {}


template < typename Object >
void RenderPass<Object>::render() const {
    prepareFunction();
    renderGroup->render();
}