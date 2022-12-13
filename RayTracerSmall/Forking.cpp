//
// Created by osboxes on 12/13/22.
//

#include "Forking.h"
std::vector<pid_t> Forking::m_Childs;

void Forking::CreatingParent()
{
    RayTracer rt;
    int loopNumber = 1;
    int temp = 10;
    int numberOfLoop = temp;
    //parent must keep forking
    for (int i = 0; i < 1; i++) {
        pid_t lForks = vfork();
        if (lForks < 0) {
            printf("Error not creating fork");

        } else if (lForks == 0) {
            std::cout << "Getting a Child" << std::endl;

            m_Childs.emplace_back(lForks);
            rt.LinuxSmoothScaling();


            _exit(0);
        }
        //only gets here if parent
    }

}

