#pragma once

#include "decode/feature.hh"

#include <assert.h>
#include <vector>

namespace decode {

class Weights;

class Objective {
  public:
    std::vector<float> weights = std::vector<float>();

    explicit Objective();

    void AddFeature(Feature &feature);

    // cannot be const because it contains layouts,
    // which are modified on alloc
    FeatureInit &GetFeatureInit() { return feature_init_; }

    void LoadWeights(Weights &weights);

    // storage can be null
    float ScorePhrase(PhrasePair phrase_pair, FeatureStore *storage) const;

    // storage can be null
    float ScoreHypothesisWithSourcePhrase(
        HypothesisAndSourcePhrase combination, FeatureStore *storage) const;

    // storage can be null
    float ScoreHypothesisWithPhrasePair(
        HypothesisAndPhrasePair combination, FeatureStore *storage) const;

    // storage can be null
    float RescoreHypothesis(
        const Hypothesis &hypothesis, FeatureStore *storage) const;

    std::size_t DenseFeatureCount() const;

    std::string FeatureDescription(std::size_t index) const;

    const lm::ngram::State *lm_begin_sentence_state = NULL;
  private:
    std::vector<Feature*> features_;
    std::vector<std::size_t> feature_offsets_;
    FeatureInit feature_init_;

    ScoreCollector GetCollector(FeatureStore *storage) const;
};

} // namespace decode