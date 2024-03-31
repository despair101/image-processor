#pragma once

#include "filters/basic.h"

#include <vector>
#include <string>
#include <unordered_map>
#include <memory>

class FilterParser {
public:
    FilterParser();
    std::vector<std::unique_ptr<BasicFilter>> Parse(int argc, char** argv) const;

private:
    struct IOption {
        virtual ~IOption() = default;
        virtual std::unique_ptr<BasicFilter> GetInstance(const std::vector<std::string>& args) const = 0;
    };

    template <class T>
    struct Option : IOption {
        ~Option() override = default;
        std::unique_ptr<BasicFilter> GetInstance(const std::vector<std::string>& args) const override {
            return std::make_unique<T>(args);
        }
    };

    std::unordered_map<std::string, std::unique_ptr<IOption>> options_;
};