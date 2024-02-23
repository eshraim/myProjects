from scapy.all import *

def icmp_reply(ip):
    num_requests = 5
    ip_id_values = []

    for _ in range(num_requests):
        icmp_req = IP(dst=ip) / ICMP()
        reply = sr1(icmp_req, timeout=3)

        if reply:
            ip_id_values.append(reply.id)
            print("Received ICMP Reply. IP-ID:", reply.id)
        else:
            print("No reply received.")

    analyze_ip_id(ip_id_values)

def analyze_ip_id(ip_id_values):
    if all(value == 0 for value in ip_id_values):
        print("D: IP-ID counter observed from replies: zero")
    elif all(ip_id_values[i] < ip_id_values[i + 1] for i in range(len(ip_id_values) - 1)):
        print("D: IP-ID counter observed from replies: incremental")
    else:
        print("D: IP-ID counter observed from replies: random")

def tcp_port_open(ip):
    port = 80
    tcp_syn_request = IP(dst=ip) / TCP(dport=port, flags="S")
    reply = sr1(tcp_syn_request, timeout=3)

    if reply and reply.haslayer(TCP) and reply[TCP].flags == 0x12:
        print("Port 80 is open. Now check IP-ID and SYN Cookies!")
        determine_ip_id_counter(ip)
        determine_syn_cookies(ip)
    else:
        print("Port 80 is not open. Exiting.")

def determine_ip_id_counter(ip):
    num_requests = 5
    ip_id_values = []

    for _ in range(num_requests):
        tcp_syn_request = IP(dst=ip) / TCP(dport=80, flags="S")
        reply = sr1(tcp_syn_request, timeout=3)

        if reply:
            ip_id_values.append(reply.id)
            print("Received TCP-SYN Reply. IP-ID:", reply.id)
        else:
            print("No reply received.")

    analyze_ip_id(ip_id_values)

def determine_syn_cookies(ip):
    tcp_syn_request = IP(dst=ip) / TCP(dport=80, flags="S")
    responses = sr(tcp_syn_request, timeout=120)

    if len(responses[0]) == 1:
        print("E: SYN cookies deployed by service running on TCP port 80: yes")
    else:
        print("E: SYN cookies deployed by service running on TCP port 80: no")
        determine_max_syn_ack_retransmissions(ip)
    determine_os(tcp_syn_request.ttl)

def determine_max_syn_ack_retransmissions(ip):
    port = 80
    tcp_syn_request = IP(dst=ip) / TCP(dport=port, flags="S")
    responses, _ = sr(tcp_syn_request, timeout=5)

    if len(responses) == 2:
        syn_ack_packets = [pkt[1] for pkt in responses if pkt[1].haslayer(TCP) and pkt[1][TCP].flags == 0x12]
        if syn_ack_packets:
            print("F: Max # of SYN-ACK packets retransmitted by service on TCP port 80:", determine_max_retransmissions(syn_ack_packets))
        else:
            print("F: Max # of SYN-ACK packets retransmitted by service on TCP port 80: N/A (No SYN-ACK packets received)")
    else:
        print("F: Max # of SYN-ACK packets retransmitted by service on TCP port 80: N/A (No response received)")

def determine_max_retransmissions(syn_ack_packets):
    ack_numbers = [pkt[TCP].ack for pkt in syn_ack_packets]
    unique_ack_numbers = set(ack_numbers)
    max_retransmissions_count = 0

    for ack_number in unique_ack_numbers:
        count = ack_numbers.count(ack_number) - 1
        if count > max_retransmissions_count:
            max_retransmissions_count = count

    return max_retransmissions_count

def determine_os(ttl):
    if ttl <= 255 and ttl > 244 :
        print("Network Device (e.g., router)")
    elif ttl > 100 and ttl <= 128:
        print("Likely Windows")
    elif ttl > 48 and ttl <= 64:
        print("Likely Linux/MacOS")
    else:
        print("Unknown")


# Test Runs Done Here
ip = 'www.ucalgary.ca'
icmp_reply(ip)
tcp_port_open(ip)
