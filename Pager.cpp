
#include "Pager.hpp"

#include "mixr/base/Pair.hpp"
#include "mixr/base/PairStream.hpp"

IMPLEMENT_EMPTY_SLOTTABLE_SUBCLASS(Pager, "Pager")
EMPTY_COPYDATA(Pager)
EMPTY_DELETEDATA(Pager)

Pager::Pager()
{
    STANDARD_CONSTRUCTOR()
}


bool Pager::onEntry()
{
    mixr::base::PairStream* components{getComponents()};
    if (components != nullptr) {
        mixr::base::List::Item* item{components->getFirstItem()};
        while (item != nullptr) {
            const auto pair = static_cast<mixr::base::Pair*>(item->getValue());
            const auto cp = static_cast<mixr::base::Component*>(pair->object());
            if (cp != nullptr)
                cp->event(RESET_EVENT);
            item = item->getNext();
        }
    }
    return true;
}
