#pragma once
class Goal {
public:
    float x1, y1; // ¶ã
    float x2, y2; // ‰E‰º

    Goal(float _x1, float _y1, float _x2, float _y2)
        : x1(_x1), y1(_y1), x2(_x2), y2(_y2) {
    }

    bool IsInside(float px, float py) const {
        return (px > x1 && px < x2 && py > y1 && py < y2);
    }
};

