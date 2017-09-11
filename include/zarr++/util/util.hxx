#pragma once

#include <string>

#include "zarr++/types/types.hxx"

namespace zarr {
namespace util {

    template<typename ITER>
    void join(const ITER & begin, const ITER & end, std::string & out, const std::string & delimiter) {
        for(ITER it = begin; it != end; ++it) {
            if(!out.empty()) {
                out.append(delimiter);
            }
            out.append(std::to_string(*it));
        }
    }


    // FIXME types are ugly hardcoded...
    void split(const std::string & in, const std::string & delimiter, std::vector<size_t> & out) {
        auto start = 0U;
        auto end = in.find(delimiter);
        while(end != std::string::npos) {
            out.push_back(
                static_cast<size_t>( std::stoul(in.substr(start, end - start)) )
            );
        }
        out.push_back(
            static_cast<size_t>( std::stoul(in.substr(start, end - start)) )
        );
    }


    // FIXME this is relatively ugly...
    // would be nicer to do this in a dimension independent way
    void makeRegularGrid(const types::ShapeType & minCoords, const types::ShapeType & maxCoords, std::vector<types::ShapeType> & grid) {
        size_t nDim = minCoords.size();
        if(nDim == 1) {
            for(size_t x = minCoords[0]; x < maxCoords[0]; ++x) {
                grid.emplace_back(types::ShapeType({x}));
            }
        }

        else if(nDim == 2) {
            for(size_t x = minCoords[0]; x < maxCoords[0]; ++x) {
                for(size_t y = minCoords[1]; y < maxCoords[1]; ++y) {
                    grid.emplace_back(types::ShapeType({x, y}));
                }
            }
        }

        else if(nDim == 3) {
            for(size_t x = minCoords[0]; x < maxCoords[0]; ++x) {
                for(size_t y = minCoords[1]; y < maxCoords[1]; ++y) {
                    for(size_t z = minCoords[2]; z < maxCoords[2]; ++z) {
                        grid.emplace_back(types::ShapeType({x, y, z}));
                    }
                }
            }
        }

        else if(nDim == 4) {
            for(size_t x = minCoords[0]; x < maxCoords[0]; ++x) {
                for(size_t y = minCoords[1]; y < maxCoords[1]; ++y) {
                    for(size_t z = minCoords[2]; z < maxCoords[2]; ++z) {
                        for(size_t t = minCoords[3]; t < maxCoords[3]; ++t) {
                            grid.emplace_back(types::ShapeType({x, y, z, t}));
                        }
                    }
                }
            }
        }

        else if(nDim == 5) {
            for(size_t x = minCoords[0]; x < maxCoords[0]; ++x) {
                for(size_t y = minCoords[1]; y < maxCoords[1]; ++y) {
                    for(size_t z = minCoords[2]; z < maxCoords[2]; ++z) {
                        for(size_t t = minCoords[3]; t < maxCoords[3]; ++t) {
                            for(size_t c = minCoords[4]; t < maxCoords[4]; ++t) {
                                grid.emplace_back(types::ShapeType({x, y, z, t, c}));
                            }
                        }
                    }
                }
            }
        }

        else {
            throw std::runtime_error("More than 5D currently not supported");
        }

    }

}
}
