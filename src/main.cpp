#include "../include/MemoryManager.h"
#include <iostream>
using namespace std;

int main() {
    MemoryManager manager;
    bool running = true;

    cout << ">> Dynamic Memory Management for Embedded Systems <<" << endl;

    while (running) {
        cout << "\nSelect an option:\n";
        cout << "1. Allocate Memory\n";
        cout << "2. Deallocate Memory\n";
        cout << "3. Show Memory Statistics\n";
        cout << "4. Run Garbage Collector\n";
        cout << "5. Exit\n";
        cout << "Choice: ";
        
        int choice;
        cin >> choice;

        switch (choice) {
            case 1: {
                cout << "Enter size of memory to allocate (in bytes): ";
                size_t size;
                cin >> size;
                void* ptr = manager.allocate(size);
                if (ptr != nullptr) {
                    cout << "Memory allocated at address: " << ptr << endl;
                }
                break;
            }
            case 2: {
                cout << "Enter address (in hexadecimal) to deallocate (e.g., 0x7ffee1f47d10): ";
                void* ptr;
                cin >> ptr;
                manager.deallocate(ptr);
                break;
            }
            case 3: {
                manager.showStatistics();
                break;
            }
            case 4: {
                manager.runGarbageCollector();
                break;
            }
            case 5: {
                running = false;
                cout << "Exiting program. Running final garbage collection..." << endl;
                manager.runGarbageCollector();
                break;
            }
            default: {
                cout << "Invalid choice! Please select a valid option.\n";
                break;
            }
        }
    }

    return 0;
}
