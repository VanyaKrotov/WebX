//
// Created by Ivan on 18.11.2020.
//

#ifndef WEBX_ALGORITHM_H
#define WEBX_ALGORITHM_H

#include "list.h"
#include <functional>

namespace algorithm {
    template<class TInput, class TOutput>
    static list<TOutput> map(list<TInput> &items, const std::function<TOutput(const TInput &, const int &)> &fn) {
            list<TOutput> result;

            int index = 0;
            for (auto &item: items) {
                result.push_back(fn(item, index));

                index++;
            }

            return result;
        }
}

#endif //WEBX_ALGORITHM_H
