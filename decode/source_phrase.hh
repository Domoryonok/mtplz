#pragma once

#include "util/murmur_hash.hh"

#include <vector>
#include <utility> // for std::pair
#include <assert.h>

namespace decode {

struct VocabWord;

typedef std::pair<std::size_t,std::size_t> SourceSpan;

class SourcePhrase {
  public:
    SourcePhrase(const std::vector<VocabWord*> &base, std::size_t begin, std::size_t end)
      : base_(base), span_(begin, end) {
      assert(begin <= end);
      assert(end <= base.size());
    }

    std::vector<VocabWord*>::const_iterator begin() const {
      return base_.cbegin() + span_.first;
    }

    std::vector<VocabWord*>::const_iterator end() const {
      return base_.cbegin() + span_.second;
    }

    const SourceSpan Span() const {
      return span_;
    }

    const std::size_t Length() const {
      return span_.second - span_.first;
    }
  private:
    const std::vector<VocabWord*> &base_;
    const SourceSpan span_;
};

struct SourcePhraseHasher {
  std::size_t operator()(const SourcePhrase &source) const {
    return util::MurmurHashNative(&*source.begin(), source.Length() * sizeof(VocabWord*));
  }
};

struct SourcePhraseEqual {
  bool operator()(const SourcePhrase &first, const SourcePhrase &second) const {
    if (first.Length() != second.Length()) { return false; }
    for (auto a = first.begin(), b = second.begin(); a != first.end(); ++a, ++b) {
      if (*a != *b) { return false; }
    }
    return true;
  }
};

} // namespace decode
