#include <linux/hyperv.h>

void vmbus_send_trace(struct pt_regs *ctx, struct vmbus_channel *channel, void *buffer, u32 bufferLen, u64 requestid, enum vmbus_packet_type type, u32 flags) {
	struct icmsg_hdr *icmsghdrp;
	struct heartbeat_msg_data *heartbeat_msg;
	u16 icmsgtype;
	u64 seq_num;
	u8 *hbeat_txf_buf;

	hbeat_txf_buf =	(u8 *)buffer;
	
        icmsghdrp = (struct icmsg_hdr *)&hbeat_txf_buf[sizeof(struct vmbuspipe_hdr)];
	heartbeat_msg = (struct heartbeat_msg_data *)&hbeat_txf_buf[ICMSG_HDR];

	bpf_probe_read_kernel(&icmsgtype, sizeof(icmsghdrp->icmsgtype), &icmsghdrp->icmsgtype);
	bpf_probe_read_kernel(&seq_num, sizeof(heartbeat_msg->seq_num), &heartbeat_msg->seq_num);

	if (icmsgtype == ICMSGTYPE_HEARTBEAT) {
		bpf_trace_printk("Hyper-V heartbeat sent:seq_num = %d", seq_num);
	}
		
}
