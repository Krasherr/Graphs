#ifndef MAXIMUMINDEPENDENTSET_H
#define MAXIMUMINDEPENDENTSET_H

#include <vector>

class MaximumIndependentSet
{
public:
    MaximumIndependentSet();
    bool removable(std::vector<int> neighbor, std::vector<int> cover);
    int max_removable(std::vector<std::vector<int> > neighbors, std::vector<int> cover);
    std::vector<int> procedure_1(std::vector<std::vector<int> > neighbors, std::vector<int> cover);
    std::vector<int> procedure_2(std::vector<std::vector<int> > neighbors, std::vector<int> cover, int k);
    int cover_size(std::vector<int> cover);
    std::vector<int> process(std::vector<std::vector<int> > graph, int V, int k);

};

#endif // MAXIMUMINDEPENDENTSET_H
