# Logger
## Usage
```c++
#include "ohlog.h"

auto* l = ohlog::Logger::get();
l->d("This is a log TAG", "This is some debug message");
l->i("It also supports printf like formatting", "This is %i and that is %f", 420, 69.69);
l->w("It can also be colorful", "As you have %s above", "seen");
l->e("I hope you just don't need to log to a file", "But you could also just %s to a file", "pipe the output");

// which outputs
/*
{D}	{2021.03.23 21:30:27}	{This is a log TAG} > This is some debug message
{I}	{2021.03.23 21:30:27}	{It also supports printf like formatting} > This is 420 and that is 69.690000
{W}	{2021.03.23 21:30:27}	{It can also be colorful} > As you have seen above
{E}	{2021.03.23 21:30:27}	{I hope you just don't need to log to a file} > But you could also just pipe the output to a file
*/
```
## Features
- [X] Logging to stdout
- [X] < 100 loc
- [X] No external dependencies
- [ ] Logging to files (i would need something non blocking with a queue)
