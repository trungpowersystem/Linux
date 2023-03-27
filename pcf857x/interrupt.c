#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <poll.h>

#define INTERRUPT_DEVICE "/sys/class/gpio/gpio46/value"

void handle_interrupt(int fd) {
	char buf;
	lseek(fd, 0, SEEK_SET);
	read(fd, &buf, 1);
	printf("Pin 7 change from 0 to 1!\n");
}

int main(void) {
	int fd;
	struct pollfd pollfds[1];
	int ret;

	fd = open(INTERRUPT_DEVICE, O_RDONLY);
	if (fd < 0) {
		printf("Failed to open device: %s\n", INTERRUPT_DEVICE);
		return -1;
	}

	pollfds[0].fd = fd;
	pollfds[0].events = POLLPRI | POLLERR;
	
	printf("Waiting for interrupt event...\n");

	while(1) {
		int ret = poll(pollfds, 1, -1);
		if (ret < 0) {
			printf("Poll failed with error code %d\n",ret);
			return -1;
		}

		if (pollfds[0].revents & POLLPRI) {
			handle_interrupt(fd);
		}
	}
	close(fd);
	return 0;
}
