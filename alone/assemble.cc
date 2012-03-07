#include "alone/assemble.hh"

#include "alone/final.hh"
#include "alone/rule.hh"

namespace alone {

std::ostream &operator<<(std::ostream &o, const Final &final) {
  const Rule::ItemsRet &words = final.From().Items();
  const Final *const *child = final.Children().data();
  for (Rule::ItemsRet::const_iterator i(words.begin()); i != words.end(); ++i) {
    if (i->Terminal()) {
      o << i->String() << ' ';
    } else {
      o << **child;
      ++child;
    }
  }
  return o;
}

} // namespace alone
