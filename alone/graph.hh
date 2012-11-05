#ifndef ALONE_GRAPH__
#define ALONE_GRAPH__

#include "alone/edge_words.hh"
#include "alone/vocab.hh"
#include "search/rule.hh"
#include "search/types.hh"
#include "search/vertex.hh"
#include "util/exception.hh"

#include <boost/noncopyable.hpp>
#include <boost/pool/object_pool.hpp>
#include <boost/scoped_array.hpp>

namespace alone {

template <class T> class FixedAllocator : boost::noncopyable {
  public:
    FixedAllocator() : current_(NULL), end_(NULL) {}

    void Init(std::size_t count) {
      assert(!current_);
      array_.reset(new T[count]);
      current_ = array_.get();
      end_ = current_ + count;
    }

    T &operator[](std::size_t idx) {
      return array_.get()[idx];
    }
    const T &operator[](std::size_t idx) const {
      return array_.get()[idx];
    }

    T *New() {
      T *ret = current_++;
      UTIL_THROW_IF(ret >= end_, util::Exception, "Allocating past end");
      return ret;
    }

    std::size_t Size() const {
      return end_ - array_.get();
    }

  private:
    boost::scoped_array<T> array_;
    T *current_, *end_;
};

class Graph : boost::noncopyable {
  public:
    typedef search::Vertex Vertex;

    explicit Graph(const lm::base::Vocabulary &vocab) : vocab_(vocab) {}

    void SetCounts(std::size_t vertices, std::size_t edges) {
      vertices_.Init(vertices);
      edges_.Init(edges);
    }

    Vertex *NewVertex() {
      return vertices_.New();
    }

    std::size_t VertexSize() const { return vertices_.Size(); }

    const Vertex &GetVertex(std::size_t index) const {
      return vertices_[index];
    }

    EdgeWords *NewEdgeWords() {      
      return edges_.New();
    }

    void SetRoot(Vertex *root) { root_ = root; }

    Vertex *Root() { return root_; }

    Vocab &MutableVocab() { return vocab_; }

  private:
    Vocab vocab_;

    FixedAllocator<Vertex> vertices_;
    FixedAllocator<EdgeWords> edges_;
    
    Vertex *root_;
};

} // namespace alone

#endif // ALONE_GRAPH__
