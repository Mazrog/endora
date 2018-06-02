//
// Created by mazrog on 12/05/18.
//

template < typename Object >
RenderGroup<Object>::RenderGroup() {}

template < typename Object >
RenderGroup<Object>::~RenderGroup() {}

template < typename Object >
void RenderGroup<Object>::add(Object * object) {
    object.push_back(object);
}

template < typename Object >
void RenderGroup<Object>::render() const {
    for (auto const& object : objects) {
        object->render();
    }
}