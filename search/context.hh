#ifndef SEARCH_CONTEXT__
#define SEARCH_CONTEXT__

#include "search/config.hh"
#include "search/vertex.hh"

#include <boost/pool/object_pool.hpp>

namespace search {

class Weights;

class ContextBase {
  public:
    explicit ContextBase(const Config &config) : pop_limit_(config.PopLimit()), weights_(config.GetWeights()) {}

    VertexNode *NewVertexNode() {
      VertexNode *ret = vertex_node_pool_.construct();
      assert(ret);
      return ret;
    }

    void DeleteVertexNode(VertexNode *node) {
      vertex_node_pool_.destroy(node);
    }

    unsigned int PopLimit() const { return pop_limit_; }

    const Weights &GetWeights() const { return weights_; }

  private:
    boost::object_pool<VertexNode> vertex_node_pool_;

    unsigned int pop_limit_;

    const Weights &weights_;
};

template <class Model> class Context : public ContextBase {
  public:
    Context(const Config &config, const Model &model) : ContextBase(config), model_(model) {}

    const Model &LanguageModel() const { return model_; }

  private:
    const Model &model_;
};

} // namespace search

#endif // SEARCH_CONTEXT__
