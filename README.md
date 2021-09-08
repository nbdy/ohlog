# Logger
## Usage
```c++
#include "ohlog.h"

DLOG("This is some debug message");
ILOGA("This is %i and that is %f", 420, 69.69);
ILOGA("As you have %s above", "seen");
ILOGA("But you could also just %s to a file", "pipe the output");
// which outputs
/*
D 2021.09.08 01:01:49 main.cpp: This is some debug message
I 2021.09.08 01:01:49 main.cpp: This is 420 and that is 69.690000
I 2021.09.08 01:01:49 main.cpp: As you have seen above
I 2021.09.08 01:01:49 main.cpp: But you could also just pipe the output to a file
*/
```
## Features
- [X] Logging to stdout
- [X] ~ 100 loc
- [X] No external dependencies
- [X] Logging to file
- [X] Thread safe
