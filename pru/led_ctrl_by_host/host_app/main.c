
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdbool.h>
#include <poll.h>
#include <inttypes.h>
#include <unistd.h>
#include <errno.h>


#define RPMESG_DEV					"/dev/rpmsg_pru30"
#define PRU0_FIRMWARE				"/sys/class/remoteproc/remoteproc1/firmware"
#define PRU0_STATE					"/sys/class/remoteproc/remoteproc1/state"
#define RPMSG_MESSAGE_SIZE           496
char payload[RPMSG_MESSAGE_SIZE];

#define CMD_LED_ON          23
#define CMD_LED_OFF         24
#define STATUS_OK           1
#define STATUS_NOK          0
/* shared_struct is used to pass data between ARM and PRU */
typedef struct shared_struct{
	uint16_t cmd;
	uint16_t data;
} shared_struct;

static uint8_t is_rpmsg_dev(void)
{
	FILE *ofp;
	ofp = fopen(RPMESG_DEV, "r");

	if (ofp == NULL)
	{
		return 0;
	}
	else
	{
		fclose(ofp);
		return 1;
	}
}

// static uint8_t set_pru0_state(const char* s)
// {
// 	FILE *ofp;
// 	ofp = fopen(PRU0_STATE, "r+");

// 	if (ofp != NULL)
// 	{
// 		fwrite(s, 1, sizeof(s), ofp);
// 		fclose(ofp);
// 		return 1;
// 	}
// 	return 0;
// }

// static uint8_t set_pru0_firmware(const char* fw)
// {
// 	FILE *ofp;
// 	ofp = fopen(PRU0_FIRMWARE, "r+");

// 	if (ofp != NULL)
// 	{
// 		fwrite(fw, 1, sizeof(s), ofp);
// 		fclose(ofp);
// 		return 1;
// 	}
// 	return 0;
// }

static uint16_t send_pru(struct shared_struct* pdata)
{
	if (!is_rpmsg_dev())
	{
		return 0;
	}

	struct pollfd pfds[1];
	pfds[0].fd = open(RPMESG_DEV, O_RDWR);
	if (pfds[0].fd < 0) {
		printf("failed to open %s", RPMESG_DEV);
		return 0;
	}

	/* write data to the payload[] buffer in the PRU firmware. */
	size_t result = write(pfds[0].fd, pdata, sizeof(struct shared_struct));

	/* poll for the received message */
	pfds[0].events = POLLIN | POLLRDNORM;
	int pollResult = 0;

	uint32_t count = 5;
	/* loop while rpmsg_pru_poll says there are no kfifo messages. */
	while (pollResult <= 0 && count--) {
		pollResult = poll(pfds,1,1000);

	}

	/* read voltage and channel back */
	size_t freadResult = read(pfds[0].fd, payload, RPMSG_MESSAGE_SIZE);
	pdata->cmd = ((shared_struct *)payload)->cmd;
	pdata->data = ((shared_struct *)payload)->data;

	close(pfds[0].fd);
	return 1;
}

int main(int argc, char *argv[])
{
	struct shared_struct shared = {0,0};

	if (argc != 2)
	{
		printf("wrong cmd format !!!\n");
		return EXIT_FAILURE;
	}

	if (0 == strcmp(argv[1], "on"))
	{
		printf("turn led on ...\n");
		shared.cmd = CMD_LED_ON;
	}
	else if (0 == strcmp(argv[1], "off"))
	{
		printf("turn led off ...\n");
		shared.cmd = CMD_LED_OFF;
	}
	else
	{
		printf("cmd not found !!!\n");
		return EXIT_FAILURE;
	}

	if(send_pru(&shared))
	{
		printf("pru response cmd %d - data %d\n", shared.cmd, shared.data);
	}
	else
	{
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}



