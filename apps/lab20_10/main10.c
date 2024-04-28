
#include "../../libs/thread_io/thread_io.h."

int main(int argc, char *argv[] ) {
    if (argc != 3) {
        printf("Не достаточно параметров. Требуеться 2 параметра: входной файл, количество строк для показа на странице\n");
        exit(-1);
    }

    outputFileInChunks(argv[1], atoi(argv[2]));
    return 0;
}
