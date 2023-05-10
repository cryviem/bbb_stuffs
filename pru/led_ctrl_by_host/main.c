#include <stdint.h>
#include <stdio.h>
#include <pru_cfg.h>
#include <pru_intc.h>
#include <rsc_types.h>
#include <pru_rpmsg.h>
#include "resource_table.h"
#include "intc_map_0.h"
 

#define CYCLES_PER_SECOND 200000000 /* 200MHz clock */
#define PR1_PRU0_PRU_R30_2 (1 << 2) /* R30_2 */
 
volatile register uint32_t __R30;   /* GPIO output register */
volatile register uint32_t __R31;

/* Host-0 Interrupt sets bit 30 in register R31 */
#define HOST_INT			((uint32_t) 1 << 30)

/* 
 * The PRU-ICSS system events used for RPMsg are defined in the Linux devicetree
 * PRU0 uses system event 16 (To ARM) and 17 (From ARM)
 * PRU1 uses system event 18 (To ARM) and 19 (From ARM)
 */
#define TO_ARM_HOST			    16
#define FROM_ARM_HOST			17

/*
 * Using the name 'rpmsg-pru' will probe the rpmsg_pru driver found
 * at linux-x.y.z/drivers/rpmsg/rpmsg_pru.c
 */
#define CHAN_NAME			"rpmsg-pru"
#define CHAN_DESC			"Channel 30"
#define CHAN_PORT			30

/*
 * Used to make sure the Linux drivers are ready for RPMsg communication
 * Found at linux-x.y.z/include/uapi/linux/virtio_config.h
 */
#define VIRTIO_CONFIG_S_DRIVER_OK	4

/* payload receives RPMsg message */
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

static void led_on()
{
    __R30 &= ~PR1_PRU0_PRU_R30_2;
}

static void led_off()
{
    __R30 |= PR1_PRU0_PRU_R30_2;
}

void main(void)
{
	struct pru_rpmsg_transport transport;
	uint16_t src, dst, len;
	volatile uint8_t *status;
	struct shared_struct message;

	/* 
	 * Allow OCP master port access by the PRU so the PRU can read 
	 * external memories 
	 */
	CT_CFG.SYSCFG_bit.STANDBY_INIT = 0;


	/* 
	 * Clear the status of the PRU-ICSS system event that the ARM will 
	 * use to 'kick' us
	 */
	CT_INTC.SICR_bit.STS_CLR_IDX = FROM_ARM_HOST;

	/* Make sure the Linux drivers are ready for RPMsg communication */
	status = &resourceTable.rpmsg_vdev.status;
	while (!(*status & VIRTIO_CONFIG_S_DRIVER_OK)) {
		/* Optional: implement timeout logic */
	};

	/* Initialize the RPMsg transport structure */
	pru_rpmsg_init(&transport, &resourceTable.rpmsg_vring0,
		&resourceTable.rpmsg_vring1, TO_ARM_HOST, FROM_ARM_HOST);

	/* 
	 * Create the RPMsg channel between the PRU and ARM user space using 
	 * the transport structure. 
	 */
	while (pru_rpmsg_channel(RPMSG_NS_CREATE, &transport, CHAN_NAME,
			CHAN_DESC, CHAN_PORT) != PRU_RPMSG_SUCCESS) {
		/* Optional: implement timeout logic */
	};

	while (1) {
		/* Check register R31 bit 30 to see if the ARM has kicked us */
		if (!(__R31 & HOST_INT))
			continue;

		/* Clear the event status */
		CT_INTC.SICR_bit.STS_CLR_IDX = FROM_ARM_HOST;

		/* 
		 * Receive available messages.
		 * Multiple messages can be sent per kick. 
		 */
		while (pru_rpmsg_receive(&transport, &src, &dst,
				payload, &len) == PRU_RPMSG_SUCCESS) {

			/* ARM sends a message using shared_struct */
			message.cmd = ((shared_struct *)payload)->cmd;

            switch (message.cmd)
            {
                case CMD_LED_ON:
                led_on();
                message.data = STATUS_OK;
                break;
                case CMD_LED_OFF:
                led_off();
                message.data = STATUS_OK;
                break;
                default:
                message.data = STATUS_NOK;
                break;

            }

			/*
			 * Send reply message to the address that sent
			 * the initial message
			 */
			pru_rpmsg_send(&transport, dst, src, &message,
				sizeof(message));
		}
	}
}

