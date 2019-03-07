//  PROI project 1
//  Marcin Białek


#include <iostream>
#include <string>
#include <IntegerQueue.h>
using namespace std;


void drawUserInterface(int);
int getKey();
void handleKey(int, int&);


IntegerQueue firstQueue(16), secondQueue(16);


int main() {
    int pressedKey, selectedOption = 0;

    while(true) {
        drawUserInterface(selectedOption);
        pressedKey = getKey();
        handleKey(pressedKey, selectedOption);
    } 
}



void displayQueueInfo(string name, IntegerQueue& queue) {
    cout << "\033[1m" << name << "\033[0m" << endl;
    cout << "    length: \033[33m" << queue.length() << "\033[0m, ";
    cout << "max length: \033[33m" << queue.maxLength() << "\033[0m, ";
    cout << "is empty: " << (queue.isEmpty() ? "\033[32mtrue" : "\033[31mfalse") << "\033[0m, ";
    cout << "is full: " << (queue.isFull() ? "\033[32mtrue" : "\033[31mfalse") << "\033[0m, " << endl;
    cout << "    content: \033[33m" << queue << "\033[0m" << endl;
}



void displayQueuesInfo() {
    displayQueueInfo("First queue", firstQueue);
    cout << endl;
    displayQueueInfo("Second queue", secondQueue);
    cout << endl << endl;
}



#define MENU_OPTIONS_COUNT 11

const struct { string name, description; } menuOptions[] = {
    { "\033[35mvoid\033[0m firstQueue.enqueue(\033[35mint\033[0m value);", "" },
    { "\033[35mvoid\033[0m secondQueue.enqueue(\033[35mint\033[0m value);", 
        "Appends number at the end of a queue." },

    { "\033[35mvoid\033[0m firstQueue.enqueueOverride(\033[35mint\033[0m value);", "" },
    { "\033[35mvoid\033[0m secondQueue.enqueueOverride(\033[35mint\033[0m value);", 
        "Appends number at the end of a queue. If the queue is full,\n        "
        "overrides the last value." },

    { "\033[35mint\033[0m firstQueue.dequeue();", "" },
    { "\033[35mint\033[0m secondQueue.dequeue();",
        "Gets number from the beginning of a queue." },

    { "firstQueue += secondQueue;", "" },
    { "secondQueue += firstQueue;", 
        "Appends elements from the second queue at the end of the first one." },

    { "cout << firstQueue + secondQueue;", 
        "Displays result of merging both queues." },

    { "cout << firstQueue == secondQueue;", 
        "Compares queues." },

    { "exit();", "" }
};



void displayMenu(int selectedOption) {
    for(int i = 0; i < MENU_OPTIONS_COUNT; i++) {
        cout << "\033[1m" << (i == selectedOption ? ">" : " ") << "\033[0m   ";
        cout << menuOptions[i].name << endl;

        if(!menuOptions[i].description.empty()) {
            cout << "        \033[36m" << menuOptions[i].description;
            cout << "\033[0m" << endl << endl;
        }
    }

    cout << endl << endl;
}



void drawUserInterface(int selectedOption) {
    system("clear");
    displayQueuesInfo();
    displayMenu(selectedOption);
}



int getKey() {
    system("stty raw"); 
    int key = getchar();
    system("stty cooked");
    return key;
}



int getValueToEnqueue() {
    cout << "\033[1mEnter value to enqueue:\033[0;33m" << endl;
    int value;
    cin >> value;
    cout << "\033[0m";
    return value;
}



void displayDeququedValue(int value) {
    cout << "\033[1mDequeued value: \033[0;33m";
    cout << value << "\033[0m" << endl;
    getKey();
} 



void displayMergedQueues() {
    cout << "\033[1mMerged queues:\033[0m" << endl;
    cout << "\033[33m" << (firstQueue + secondQueue) << "\033[0m" << endl;
    getKey();
}



void compareQueues() {
    cout << (firstQueue == secondQueue ? "\033[32mQueues are equal." : "\033[31mQueues are not equal.") << "\033[0m" << endl;
    getKey();
}



void quit() {
    system("clear");
    exit(EXIT_SUCCESS);
}



void handleOption(int option) {
    switch(option) {
        case 0: {
            firstQueue.enqueue(getValueToEnqueue());
            break;
        }
        case 1: {
            secondQueue.enqueue(getValueToEnqueue());
            break;
        }
        case 2: {
            firstQueue.enqueueOverride(getValueToEnqueue());
            break;
        }
        case 3: {
            secondQueue.enqueueOverride(getValueToEnqueue());
            break;
        }
        case 4: {
            displayDeququedValue(firstQueue.dequeue());
            break;
        }
        case 5: {
            displayDeququedValue(secondQueue.dequeue());
            break;
        }
        case 6: {
            firstQueue += secondQueue;
            break; 
        }
        case 7: {
            secondQueue += firstQueue;
            break; 
        }
        case 8: {
            displayMergedQueues();
            break;
        }
        case 9: {
            compareQueues();
            break;
        }
        case 10: {
            quit();
            break;
        }
        default:
            break;
    }
}



void handleKey(int key, int &selectedOption) {
    switch(key) {
        case 65: // Up 
            selectedOption = (selectedOption + MENU_OPTIONS_COUNT - 1) % MENU_OPTIONS_COUNT;
            break;

        case 66: // Down
            selectedOption = (selectedOption + 1) % MENU_OPTIONS_COUNT;
            break;

        case 13: // Enter
            handleOption(selectedOption);
    }
}

