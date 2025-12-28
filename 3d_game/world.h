//
// Created by david on 2025-12-28.
//

#ifndef INC_3D_GAME_WORLD_H
#define INC_3D_GAME_WORLD_H


class World {
    public:
        World();
        ~World() = default;
        void update(float deltaTime);
        void draw();


    private:
    int x = 0;
    int y = 0;
    int z = 0;


};


#endif //INC_3D_GAME_WORLD_H