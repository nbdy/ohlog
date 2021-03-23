#include "ohlog.h"

int main() {
    auto* l = ohlog::Logger::get();

    l->d("This is a log TAG", "This is some debug message");
    l->i("It also supports printf like formatting", "This is %i and that is %f", 420, 69.69);
    l->w("It can also be colorful", "As you have %s above", "seen");
    l->e("I hope you just don't need to log to a file", "But you could also just %s to a file", "pipe the output");

    return 0;
}
