#include "core/AutocorrectSuggestion.h"
#include "absl/algorithm/container.h"

using namespace std;

namespace sorbet::core {

bool hasSeen(const UnorderedSet<Loc> &seen, Loc loc) {
    for (auto &seenLoc : seen) {
        if (seenLoc.beginPos() >= loc.beginPos() && seenLoc.beginPos() < loc.endPos()) {
            return true;
        }
        if (seenLoc.endPos() >= loc.beginPos() && seenLoc.endPos() < loc.endPos()) {
            return true;
        }
    }
    return false;
}

map<FileRef, string> AutocorrectSuggestion::apply(vector<AutocorrectSuggestion> autocorrects,
                                                  map<FileRef, string> sources) {
    // Sort the locs backwards
    auto compare = [](const AutocorrectSuggestion &left, const AutocorrectSuggestion &right) {
        if (left.loc.file() != right.loc.file()) {
            return left.loc.file().id() > right.loc.file().id();
        }

        auto a = left.loc.beginPos();
        auto b = right.loc.beginPos();
        if (a != b) {
            return a > b;
        }

        return false;
    };
    absl::c_sort(autocorrects, compare);

    UnorderedSet<Loc> seen; // used to make sure nothing overlaps
    map<FileRef, string> ret;
    for (auto &autocorrect : autocorrects) {
        auto &loc = autocorrect.loc;
        if (!ret.count(loc.file())) {
            ret[loc.file()] = sources[loc.file()];
        }
        auto source = ret[loc.file()];
        auto start = loc.beginPos();
        auto end = loc.endPos();

        if (hasSeen(seen, loc)) {
            continue;
        }
        seen.emplace(loc);
        ret[loc.file()] = string(source.substr(0, start)) + autocorrect.replacement + string(source.substr(end, -1));
    }
    return ret;
}

} // namespace sorbet::core
