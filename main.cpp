#include <iostream>
#include <cmath>

const short MAX_DOT_COUNT = 20;
const short MAX_PRICE = 32767;

short dot_count = 0;
short distance[MAX_DOT_COUNT][MAX_DOT_COUNT] = {0};
short min_price = MAX_PRICE;

class Dot {
public:
    short x = 0;
    short y = 0;
};

Dot dots_coodinates[MAX_DOT_COUNT];
short best_path[MAX_DOT_COUNT + 1] = {0};
short current_path[MAX_DOT_COUNT + 1] = {0};

short get_distance(Dot a, Dot b) {
    return std::round(std::sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y)));
}

void smth(short current_dot_number, short visited_count, short price_now, bool visited[MAX_DOT_COUNT]) {
    current_path[visited_count - 1] = current_dot_number;

    if (visited_count == dot_count && distance[current_dot_number][0] > 0) {
        short total_cost = price_now + distance[current_dot_number][0];
        if (total_cost < min_price) {
            min_price = total_cost;
            for (short i = 0; i < dot_count; i++) {
                best_path[i] = current_path[i];
            }
            best_path[dot_count] = 0;
        }
        return;
    }

    for (short i = 0; i < dot_count; i++) {
        if (!visited[i] && distance[current_dot_number][i] > 0) {
            visited[i] = true;
            smth(i, visited_count + 1, price_now + distance[current_dot_number][i], visited);
            visited[i] = false;
        }
    }
}

int main() {
    std::cout << "Enter dots count: ";
    std::cin >> dot_count;
    for (int i = 0; i < dot_count; i++) {
        std::cout << "Enter coordinates of " << i + 1 << " dot: ";
        std::cin >> dots_coodinates[i].x >> dots_coodinates[i].y;
    }
    for (int i = 0; i < dot_count; i++) {
        for (int j = 0; j < dot_count; j++) {
            if (i == j) {
                distance[i][j] = 0;
            } else {
                distance[i][j] = get_distance(dots_coodinates[i], dots_coodinates[j]);
            }
        }
    }
    bool visited[MAX_DOT_COUNT] = {false};
    visited[0] = true;

    smth(0, 1, 0, visited);

    std::cout << "Minimum cost: " << min_price << '\n';
    for (int i = 0; i <= dot_count; i++) {
        Dot p = dots_coodinates[best_path[i]];
        std::cout << "(" << p.x << ", " << p.y << ")";
        if (i < dot_count) {
            std::cout << " -> ";
        }
    }
    std::cout << std::endl;

    return 0;
}