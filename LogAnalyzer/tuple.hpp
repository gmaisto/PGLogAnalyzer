//
//  tuple.hpp
//  LogAnalyzer
//
//  Created by Luigi Maisto on 06/08/2016.
//  Copyright © 2016 Luigi Maisto. All rights reserved.
//

#ifndef tuple_hpp
#define tuple_hpp

#include "statement.hpp"
#include <vector>
#include <boost/accumulators/accumulators.hpp>
#include <boost/accumulators/statistics/stats.hpp>
#include <boost/accumulators/statistics/mean.hpp>
#include <boost/accumulators/statistics/median.hpp>
#include <boost/accumulators/statistics/variance.hpp>
#include <boost/accumulators/statistics/min.hpp>
#include <boost/accumulators/statistics/max.hpp>
#include <boost/bind.hpp>
#include <boost/ref.hpp>


using namespace boost::accumulators;

namespace Tuple {
    struct Stats {
        std::size_t samples;
        float mean;
        float median;
        float variance;
        float min;
        float max;
    };

class Tuple {

public:
    Tuple(Statement const& st = {}): statement(st), _count(0L) { }

    long getCount() {return _count;}

    std::vector<float>& getTimings() {
        std::sort(timings.begin(), timings.end(), std::greater<float>());
        return timings; }

    void addTiming(float const& runtime) {timings.push_back(runtime);}

    Statement getStatement() {return statement;}

    void addOneToCount() {
        _count += 1;
    }

    Stats getStatistics() {
        accumulator_set<float, features<tag::count, tag::min, tag::max, tag::mean, tag::variance, tag::median(with_p_square_quantile)> > acc;
        for_each(timings.begin(), timings.end(), boost::bind<void>(boost::ref(acc), _1));
        stats.samples = count(acc);
        stats.median = median(acc);
        stats.variance = variance(acc);
        stats.max = max(acc);
        stats.min = min(acc);
        stats.mean = mean(acc);
        return stats;
    }

   /* std::tuple<std::size_t, float, float, float, float, float> getStats() {
        accumulator_set<float, features<tag::count, tag::min, tag::max, tag::mean, tag::variance, tag::median(with_p_square_quantile)> > acc;
        for_each(timings.begin(), timings.end(), boost::bind<void>(boost::ref(acc), _1));
        
        return std::make_tuple(count(acc), min(acc), max(acc), mean(acc), variance(acc), median(acc));
    }*/



private:
    
    Statement statement;
    long _count;
    std::vector<float> timings;
    Stats stats;
    
};

};



#endif /* tuple_hpp */
