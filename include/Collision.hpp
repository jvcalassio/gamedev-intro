#ifndef __COLLISION__
#define __COLLISION__
#include <algorithm>
#include "Rect.hpp"
#include "Vec2.hpp"


class Collision {
	public:
		// Observação: IsColliding espera ângulos em radianos!
		// Para usar graus, forneça a sua própria implementação de Rotate,
		// ou transforme os ângulos no corpo de IsColliding.
		static inline bool IsColliding(Rect& a, Rect& b, float angleOfA, float angleOfB) {
            Vec2 A[] = {
                Vec2(a.x, a.y + a.h),
                Vec2(a.x + a.w, a.y + a.h),
                Vec2(a.x + a.w, a.y),
                Vec2(a.x, a.y)
            };
            Vec2 B[] = {
                Vec2(b.x, b.y + b.h),
                Vec2(b.x + b.w, b.y + b.h),
                Vec2(b.x + b.w, b.y),
                Vec2(b.x, b.y)
            };

            for (auto& v : A) {
                v = (v - a.center()).rotated(angleOfA) + a.center();
			}

			for (auto& v : B) {
                v = (v - b.center()).rotated(angleOfB) + b.center();
			}

            Vec2 axes[] = {
                (A[0] - A[1]).normalized(), 
                (A[1] - A[2]).normalized(), 
                (B[0] - B[1]).normalized(), 
                (B[1] - B[2]).normalized()
            };

			for (auto& axis : axes) {
				float P[4];

				for (int i = 0; i < 4; ++i) P[i] = A[i].dot(axis);

				float minA = *std::min_element(P, P + 4);
				float maxA = *std::max_element(P, P + 4);

				for (int i = 0; i < 4; ++i) P[i] = B[i].dot(axis);

				float minB = *std::min_element(P, P + 4);
				float maxB = *std::max_element(P, P + 4);

				if (maxA < minB || minA > maxB)
					return false;
			}

			return true;
		}
};

#endif