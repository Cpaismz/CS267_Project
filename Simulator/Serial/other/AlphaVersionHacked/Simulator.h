#ifndef SIMULATOR
#define SIMULATOR

class Simulator {
    public: 
        void init_args();   // TODO: i don't know how this will be done yet
                            // or if a separate function is the right way
                            // could also just be a constructor
        void run();

        // maybe have all the args here in the simulator class?
        int exampleArg;
        int exampleArg2;
}

#endif
