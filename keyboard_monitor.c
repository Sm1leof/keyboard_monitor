#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <linux/input.h>

char key_mapping[KEY_MAX] = {
    0, 0, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b', '\t',
    'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n', 0, 'a', 's',
    'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', 0, '\\', 'z', 'x', 'c', 'v',
    'b', 'n', 'm', ',', '.', '/', 0, '*', 0, ' ', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, '7', '8', '9', '-', '4', '5', '6', '+', '1', '2', '3', '0', '.'
};

int main() {
    int fd;
    struct input_event ev;

    fd = open("/dev/input/event0", O_RDONLY);
    if (fd == -1) {
        perror("Error");
        return 1;
    }

    printf("Listening. Press Ctrl+C to exit.\n");

    while (1) {
        
        ssize_t bytes = read(fd, &ev, sizeof(struct input_event));
            
            if (bytes == -1) {
            perror("Reading error");
            break;
            }

        if (ev.type == EV_KEY && ev.value == 1) {
            
            if (ev.code < KEY_MAX && key_mapping[ev.code] != 0) {
                printf("Key number: %d, Key: %c\n", ev.code, key_mapping[ev.code]);
                printf("\n");
            } 
            
            else {
                printf("Unknown key: %d\n", ev.code);
                printf("\n");
            }
        }
    }

    close(fd);

    return 0;
}