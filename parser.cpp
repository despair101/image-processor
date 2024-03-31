#include "filters/all.h"
#include "parser.h"

#include <vector>
#include <string>
#include <unordered_map>
#include <memory>

FilterParser::FilterParser() {
    options_["-gs"] = std::make_unique<Option<GrayscaleFilter>>();
    options_["-crop"] = std::make_unique<Option<CropFilter>>();
    options_["-neg"] = std::make_unique<Option<NegativeFilter>>();
    options_["-sharp"] = std::make_unique<Option<SharpFilter>>();
    options_["-edge"] = std::make_unique<Option<EdgeFilter>>();
    options_["-spiral"] = std::make_unique<Option<SpiralFilter>>();
    options_["-blur"] = std::make_unique<Option<BlurFilter>>();
}

std::vector<std::unique_ptr<BasicFilter>> FilterParser::Parse(int argc, char** argv) const {
    std::vector<std::unique_ptr<BasicFilter>> result;

    int pos = 3;
    while (pos < argc) {
        const std::string option{argv[pos++]};
        std::vector<std::string> args;
        while (pos < argc && argv[pos][0] != '-') {
            args.push_back(std::string(argv[pos]));
            ++pos;
        }

        try {
            result.push_back(options_.at(option)->GetInstance(args));
        } catch (...) {
            throw std::invalid_argument{"No such option."};
        }
    }

    return result;
}