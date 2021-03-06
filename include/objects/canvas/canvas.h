#pragma once

#include "objects/texture/texture.h"

namespace love
{
    class Canvas : public Texture
    {
        public:
            static love::Type type;

            struct Settings
            {
                int width = 1;
                int height = 1;
            };

            Canvas(const Settings & settings);
            ~Canvas();

            static int canvasCount;

            void Draw(const DrawArgs & args, love::Quad * quad, const Color & color);

    };
}
