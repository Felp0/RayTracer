//
// Created by osboxes on 12/13/22.
//

#pragma  once
#include <vector>
#include <functional>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "RayTracer.h"
#ifndef RAYTRACER_FORKING_H
#define RAYTRACER_FORKING_H


class Forking {

public:
    static void CreatingParent();
private:
    static std::vector<pid_t> m_Childs;
};


#endif //RAYTRACER_FORKING_H
