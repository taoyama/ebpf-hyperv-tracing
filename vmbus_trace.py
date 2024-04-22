#!/usr/bin/python3  
from bcc import BPF

b = BPF(src_file="vmbus_send_trace.bpf.c")
b.attach_kprobe(event="vmbus_sendpacket", fn_name="vmbus_send_trace")
b.trace_print()
