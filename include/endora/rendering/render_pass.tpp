//
// Created by mazrog on 12/05/18.
//

template < typename Object >
RenderPass<Object>::RenderPass(std::vector<Object> renderGroup, VoidFunc && prepareFunction)
        : prepareFunction(std::move(prepareFunction)), renderGroup(renderGroup) {}


template < typename Object >
RenderPass<Object>::~RenderPass() {}


template < typename Object >
void RenderPass<Object>::render() const {
    prepareFunction();

    for(auto const& object: renderGroup) {
        object->draw();
    }
}