#pragma once

#include "api.hpp"
#include <cstdint>
#include <string>
#include <atomic>
#include <random>
#include <chrono>
#include <sstream>
#include <iomanip>
#include <functional>

namespace tritium {

class TRITIUM_API Uid {
public:
    using value_type = std::uint64_t;

private:
    value_type v_{0};

public:
    constexpr Uid() noexcept = default;
    constexpr explicit Uid(value_type v) noexcept : v_(v) {}

    static constexpr Uid invalid() noexcept { return Uid(0); }
    bool is_valid() const noexcept { return v_ != 0; }
    value_type value() const noexcept { return v_; }

    std::string to_string() const {
        std::ostringstream ss;
        ss << std::hex << std::setw(16) << std::setfill('0') << v_;
        return ss.str();
    }

    static Uid from_string(const std::string& s) {
        std::istringstream ss(s);
        value_type v = 0;
        ss >> std::hex >> v;
        return Uid(v);
    }

    static Uid generate() {
        auto t = static_cast<std::uint64_t>(
            std::chrono::high_resolution_clock::now().time_since_epoch().count());

        static std::atomic<std::uint64_t> counter{1};
        std::uint64_t c = counter.fetch_add(1, std::memory_order_relaxed);

        thread_local std::mt19937_64 rng(std::random_device{}());
        std::uint64_t r = rng();

        std::uint64_t mix = t ^ (r + 0x9e3779b97f4a7c15ULL + (t << 6) + (t >> 2));
        std::uint64_t out = mix ^ (c * 0xbf58476d1ce4e5b9ULL);

        if (out == 0) out = 1; // reserve 0 as invalid
        return Uid(out);
    }

    constexpr bool operator==(const Uid& o) const noexcept { return v_ == o.v_; }
    constexpr bool operator!=(const Uid& o) const noexcept { return v_ != o.v_; }
};

} // namespace tritium

namespace std {
template<>
struct hash<tritium::Uid> {
    std::size_t operator()(const tritium::Uid& u) const noexcept {
        std::uint64_t v = u.value();
        return static_cast<std::size_t>(v ^ (v >> 32));
    }
};
}