#ifndef COMPARISON_ENGINE_H
#define COMPARISON_ENGINE_H

#include "SchedulingResult.h"

#include <vector>

class ComparisonEngine {

public:

    static void displayComparison(
        const std::vector<SchedulingResult>& results
    );
};

#endif
