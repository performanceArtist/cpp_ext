# Task

## Summary

Callback(Task) class. Written for a game to run certain time-dependent actions, but can be utilizied in many different ways.

## Usage

Constructor has two parameters. First is a function of type 'void' taking one argument - Task pointer. This pointer allows you to change the task object within the callback. Second parameter takes a timeout in milliseconds.

```cpp
Task myClock([](Task* task) {
    std::cout << "One second passed...";
}, 1000);
```

To keep track of your callbacks, you can use public property 'track' and private property 'count' (method 'getCount'). Every time the callback is run, they're both incremented. The idea is to keep 'count' the same, while using 'track' to implement some logic. For instance:

```cpp
Task spawnEnemy([](Task* task) {
    if(task->track < 10) {
        std::cout << task->track << " New enemy!\n";
    } else {
        //increase spawn frequency every 10 calls
        std::cout << "Faster!\n";
        unsigned int tm = task->getTimeout();
        if(tm > 200) task->setTimeout(tm-100);
        task->track = 0;
    }
}, 1000);
```

You can also control task execution by using 'enable' and 'disable' methods (check Task status with 'getStatus' method):

```cpp
Task runTwice([](Task* task) {
    std::cout << task->track << "\n";
    if (task->track >= 2) {
        task->disable();
        std::cout << "Stop";
    }
}, 1000);
```

There is an option to change the callback:

```cpp
Task swap([](Task* task) {
    std::cout << task->track << "\n";
    if (task->track > 5) {
        std::cout << "And now for something completely different...\n";
        task->setCallback([](Task* task) {
            std::cout << "Shazam!\n";
        });
    }
}, 1000);
```

And to add a dependent object pointer, with 'bind' method:

```cpp
std::string myStr = "Hi there!";

Task manage([](Task* task) {
    std::cout << *((std::string*)task->target) << "\n";
}, 1000);

manage.bind(&myStr);
```

That's all there is too it. Although there is also a method 'executeImmediately', but it requires no explanation. You can find aforementioned examples in 'testing.cpp' file. Just copy this folder and plug in the desired task in the loop.

## Notes

Manager class probably needs an improvement. Overall I should decide what architecture would serve it best.