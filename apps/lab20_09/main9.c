
#include "../../libs/thread_io/thread_io.h."

int main(int argc, char *argv[] ) {
    if (argc != 4) {
        printf("Не достаточно параметров. Требуеться 3 параметра: входной файл, выходной файл, число N\n");
        exit(-1);
    }

    fileWithSmallerValues(argv[1], argv[2], atoi(argv[3]));
    return 0;
}
