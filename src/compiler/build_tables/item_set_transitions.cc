#include "compiler/build_tables/item_set_transitions.h"
#include <unordered_set>
#include "compiler/build_tables/item_set_closure.h"
#include "compiler/build_tables/rule_transitions.h"
#include "compiler/build_tables/merge_transitions.h"
#include "compiler/rules/interned_symbol.h"

namespace tree_sitter {
    using std::map;
    using std::unordered_set;
    using rules::CharacterSet;
    using rules::ISymbol;

    namespace build_tables {
        template<typename T>
        static unordered_set<T> merge_sets(const unordered_set<T> &left, const unordered_set<T> &right) {
            unordered_set<T> result = left;
            result.insert(right.begin(), right.end());
            return result;
        }

        map<CharacterSet, LexItemSet>
        char_transitions(const LexItemSet &item_set, const PreparedGrammar &grammar) {
            map<CharacterSet, LexItemSet> result;
            for (const LexItem &item : item_set) {
                map<CharacterSet, LexItemSet> item_transitions;
                for (auto &transition : char_transitions(item.rule)) {
                    LexItem next_item(item.lhs, transition.second);
                    item_transitions.insert({
                        transition.first,
                        LexItemSet({ next_item })
                    });
                }
                merge_char_transitions<LexItemSet>(result, item_transitions, [](const LexItemSet &l, const LexItemSet &r) {
                    return merge_sets(l, r);
                });
            }
            return result;
        }

        map<ISymbol, ParseItemSet>
        sym_transitions(const ParseItemSet &item_set, const PreparedGrammar &grammar) {
            map<ISymbol, ParseItemSet> result;
            for (const ParseItem &item : item_set) {
                map<ISymbol, ParseItemSet> item_transitions;
                for (auto &transition : sym_transitions(item.rule)) {
                    ParseItem new_item(item.lhs, transition.second, item.consumed_symbol_count + 1, item.lookahead_sym);
                    item_transitions.insert({
                        transition.first,
                        item_set_closure(new_item, grammar)
                    });
                }
                merge_sym_transitions<ParseItemSet>(result, item_transitions, [&](const ParseItemSet &l, const ParseItemSet &r) {
                    return merge_sets(l, r);
                });
            }
            return result;
        }
    }
}