#include "Basics.h"

#include <math.h>

Vector2 Basics::Normalize(Vector2 vec) {
    float _dist = 0.0f;
    Vector2 _tempVector = vec;

    _dist = sqrtf(vec.x * vec.x + vec.y * vec.y);
    if (_dist == 0.0f) {
        return vec;
    }
    _tempVector = { vec.x / _dist, vec.y / _dist };

    return _tempVector;
}

float Basics::Clamp(float value, float min, float max) {
    if (value < min) {
        return min;
    } else if (value > max) {
        return max;
    }
    return value;
}

float Basics::Lerp(float from, float to, float rate) {
    float _difference = to - from;    
    return from + (_difference * rate);
}

bool Basics::Collision(Vector2 pos1, Vector2 pos2, float radius1, float radius2) {
    float _totalDistance = 0.0f;
    Vector2 _distance = { pos1.x - pos2.x, pos1.y - pos2.y };
    _totalDistance = sqrtf((_distance.x * _distance.x) + (_distance.y * _distance.y));

    float _totalRadius = radius1 + radius2;

    if (_totalRadius >= _totalDistance) {
        return true;
    }
    return false;
}
