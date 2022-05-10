import matplotlib.pyplot as plt


def node_number(node):
    char_list = list(node)
    char_list.pop()
    char_list.pop(0)
    return int(''.join(char_list))


def readfile(file_name):
    file1 = open(file_name, "r")

    received_packets = 0
    sent_packets = 0
    dropped_packets = 0
    total_delay = 0
    received_bytes = 0
    start_time = 1000000
    end_time = 0
    header_bytes = 20
    sent_time = {}

    events = ['s', 'r', 'D']
    lines = file1.readlines()
    for line in lines:
        tokens = line.split()
        event = tokens[0]
        if event not in events:
            continue
        time_sec = float(tokens[1])
        node = node_number(tokens[2])
        layer = tokens[3]
        packet_id = int(tokens[5])
        packet_type = tokens[6]
        packet_bytes = int(tokens[7])

        if layer == "AGT" and packet_type == "exp":
            if event == "s":
                sent_time[packet_id] = time_sec
                sent_packets += 1
            elif event == "r":
                delay = time_sec - sent_time[packet_id]
                total_delay += delay
                byte_count = packet_bytes - header_bytes
                received_bytes += byte_count
                received_packets += 1

        if packet_type == "exp":
            start_time = min(start_time, time_sec)
            end_time = max(end_time, time_sec)
            if event == "D":
                dropped_packets += 1

    file1.close()
    simulation_time = end_time - start_time
    return {
        "throughput": float("{:.2f}".format((received_bytes * 8) / simulation_time)),
        "average_delay": float("{:.3f}".format(total_delay / received_packets)),
        "delivery_ratio": float("{:.4f}".format(received_packets / sent_packets)),
        "drop_ratio": float("{:.4f}".format(dropped_packets / sent_packets))
    }


def make_plot(y_key, dicts):
    x = [250, 500, 750, 1000, 1250]
    y = []
    for _dict in dicts:
        y.append(_dict[y_key])

    plt.plot(x, y, marker='o', color='b')
    plt.xlabel("Area size")
    plt.ylabel(y_key)
    for idx in range(5):
        plt.annotate('(' + str(x[idx]) + ', ' + str(y[idx]) + ')', (x[idx], y[idx]))
    plt.tight_layout()
    plt.savefig('area_size_vs_' + y_key + '.png')
    plt.clf()


def report():
    dicts = [readfile("trace_area_250.tr"), readfile("trace_area_500.tr"), readfile("trace_area_750.tr"),
             readfile("trace_area_1000.tr"), readfile("trace_area_1250.tr")]
    make_plot("throughput", dicts)
    make_plot("average_delay", dicts)
    make_plot("delivery_ratio", dicts)
    make_plot("drop_ratio", dicts)


report()


# y += 1
# if y >= 427:
#     print(tokens)
#     print(event)
#     print(time_sec)
#     print(node)
#     print(layer)
#     print(packet_id)
#     print(packet_type)
#     print(packet_bytes)
# if y == 440:
#     break
