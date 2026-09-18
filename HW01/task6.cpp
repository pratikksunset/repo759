#include <iostream>
#include <cstdio>

int main(int argc, char* argv[]) {

    int N = std::atoi(argv[1]);

    for (int i = 0; i <=N; i++) {
        printf("%d%s", i, (i==N ?"":" "));
    }
    printf("\n");
    for (int i = N; i >=0; i--) {
        std::cout<<i<<(i==0 ? "" : " ");
    }
    printf("\n");
}