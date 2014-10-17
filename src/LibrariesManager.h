#ifndef LIBRARIESMANAGER_H_INCLUDED
#define LIBRARIESMANAGER_H_INCLUDED

class LibrariesManager {
    public:
        LibrariesManager();
        ~LibrariesManager();

        void loadLibraries();
        void releaseLibraries();

    private:
        void loadSFML();
        void releaseSFML();
};

#endif