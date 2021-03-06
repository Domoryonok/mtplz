#pragma once

#include "decode/feature.hh"

namespace util { class MutableVocab; }

namespace decode {

class Passthrough : public Feature {
  public:
    Passthrough() : Feature("passthrough") {}

    void Init(FeatureInit &feature_init) override {}

    static const StringPiece Name();

    void NewWord(const StringPiece string_rep, VocabWord *word) const override {}

    void InitPassthroughPhrase(pt::Row *passthrough, TargetPhraseType type) const override {}

    void ScoreTargetPhrase(TargetPhraseInfo target, ScoreCollector &collector) const override {
      // TODO make sparse
      collector.AddDense(0, (float)(target.type == TargetPhraseType::Passthrough));
    }

    void ScoreHypothesisWithSourcePhrase(
        const Hypothesis &hypothesis, const SourcePhrase source_phrase, ScoreCollector &collector) const override {}

    void ScoreHypothesisWithPhrasePair(
        const Hypothesis &hypothesis, PhrasePair phrase_pair, ScoreCollector &collector) const override {}

    void ScoreFinalHypothesis(
        const Hypothesis &hypothesis, ScoreCollector &collector) const override {}

    bool HypothesisEqual(const Hypothesis &first, const Hypothesis &second) const override {
      return true;
    }

    std::size_t DenseFeatureCount() const override { return 1; }

    std::string FeatureDescription(std::size_t index) const override {
      assert(index == 0);
      return "passthrough";
    }
};

} // namespace decode
