#include "translate.h"

int main(int argc, const char* argv[])
{
    error_code_t error_code;
    error_code = translate(argc, argv);
    printf("\nerror_code: %d\n", error_code);
    return 0;
}
