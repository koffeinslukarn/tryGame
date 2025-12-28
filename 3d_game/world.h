//
// Created by david on 2025-12-28.
//

#ifndef INC_3D_GAME_WORLD_H
#define INC_3D_GAME_WORLD_H

#include <glad/glad.h>


class World {
    public:
        World();
        ~World() = default;
        void update(float deltaTime);
        void draw() const;


    private:
    GLuint m_vao = 0;
    GLuint m_vbo = 0;
    GLuint m_program = 0;


};


#endif //INC_3D_GAME_WORLD_H