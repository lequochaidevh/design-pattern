#pragma once

#include <iostream>
#include <string>
#include <mutex>
#define SYNC_THREAD_BY_MUXTEX
//#define MAKE_STATIC_OBJECT

namespace nsSingleton {
    class Database
    {
    private:
        int mRecord;
        std::string mName;

        // Pointer help to create new this->class because contractor side in private level
        static Database* mInstancePtr;

        // Sync clock thread when check mInstance variable
        static std::mutex mLocker;

        // Contractor set in private level to prevent creating new class
        Database(std::string name)
        {
            mName = name;
            mRecord = 0;
        }

    public:

        void editRecord(std::string operation)
        {
            std::cout << "Performing a " << operation <<
                "operation on record " << mRecord <<
                " in database " << mName << std::endl;
        }

        std::string getName()
        {
            return mName;
        }

        #ifdef SYNC_THREAD_BY_MUXTEX
        // Help to create new this->class because contractor side in private level
        static Database* getInstance(std::string name)
        {
            mLocker.lock();// Ensure that checking mInstance have to sync ALL thread
            if (nullptr == mInstancePtr) { // Ensure that just once oject use
                mInstancePtr = new Database(name);
            }
            mLocker.unlock();
            return mInstancePtr;
        }
        #elif MAKE_STATIC_OBJECT
        static Database* getInstance(std::string name)
        {
            static Database mInstance(name);
            return &mInstance;
        }
        #else 
        static Database* getInstance(string name)
        {
            if (nullptr == mInstancePtr) {
                mInstancePtr = new Database(name);
            }
            return mInstancePtr;
        }
        #endif // SYNC_THREAD_BY_MUXTEX          

        static Database* freeInstance() {
            
            mLocker.lock();
            if (nullptr != mInstancePtr) { 
                mInstancePtr = nullptr;
                std::cout << "Free Instance successfully\n";
            }
            mLocker.unlock();
            return mInstancePtr;
        }        
                
    };
    // Create mInstancePtr->nullptr
    Database* Database::mInstancePtr = nullptr;
    
#ifdef SYNC_THREAD_BY_MUXTEX
    // Create clock thread
    std::mutex Database::mLocker;
#endif // SYNC_THREAD_BY_MUXTEX


    void programTest() {
        Database* database;
        database = Database::getInstance("products");
        std::cout << "This is the " << database->getName() << " database." << std::endl;
        database = Database::getInstance("employees");
        std::cout << "This is the " << database->getName() << " database.\n" << std::endl;

        database = Database::freeInstance();// 
        database = Database::getInstance("employees");
        std::cout << "This is the " << database->getName() << " database.\n" << std::endl;

        Database* database_II;
        database_II = Database::freeInstance(); // hacking? -> fix
        database_II = Database::getInstance("products");
        std::cout << "This is the " << database_II->getName() << " database_II.\n" << std::endl;
    }

}
