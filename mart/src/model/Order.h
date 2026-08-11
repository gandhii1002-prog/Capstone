#pragma once

struct Order {
    int id{};
    int buyer_id{};
    long long total_amount_cents{};
};
