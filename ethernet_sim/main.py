import json
import random
import select
import socket
import string
import struct
import sys
import time
import traceback

DRIVER_IO_IP = '127.0.0.1'
DRIVER_IO_PORT = 8000
file_format = '../sc1-data-format/format.json'
gps_data = 'gps_dataset/dataset1.json'

types = {'bool': '?', 'float': 'f', 'char': 'c', 'uint8': 'B', 'uint16': 'H', 'uint64': 'Q'}
format_string = '<'

with open(file_format, 'r') as f:
    data_format = json.load(f)
for k in data_format.keys():
    format_string += types[data_format[k][1]]

gps_data = json.load(open(gps_data, 'r'))['data']
gps_data_index = 0

def gen_data(mcu_hv_en: bool, shutdown: bool):
    global gps_data_index
    data = []
    for key in data_format.keys():
        d = data_format[key]
        t = time.gmtime()
        match d[1]:
            case 'bool':
                if key == 'mcu_hv_en':
                    data.append(mcu_hv_en)
                elif d[5].find("Shutdown") != -1 and not shutdown:
                    data.append(False)
                else:
                    data.append(random.getrandbits(1))
            case 'float':
                if key == 'accelerator':
                    data.append(random.random())
                elif key == 'lat':
                    data.append(gps_data[gps_data_index]['latitude'])
                elif key == 'lon':
                    data.append(gps_data[gps_data_index]['longitude'])
                elif key == 'elev':
                    data.append(gps_data[gps_data_index]['elevation'])
                else:
                    data.append(random.random() * 100)
            case 'uint8':
                if key == 'tstamp_sc':
                    data.append(t.tm_sec)
                elif key == 'tstamp_mn':
                    data.append(t.tm_min)
                elif key == 'tstamp_hr':
                    data.append(t.tm_min)
                else:
                    data.append(random.randrange(0, 100))
            case 'uint16':
                data.append(random.randrange(0, 100))
            case 'uint64':
                data.append(int(time.mktime(t)))
            case 'char':
                data.append(bytes(random.choice(string.ascii_letters), 'ascii'))
    gps_data_index = (gps_data_index + 1) % len(gps_data)
    return struct.pack(format_string, *data)

if __name__ == '__main__':
    while True:
        connected = False
        while not connected:
            client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            try:
                client.connect((DRIVER_IO_IP, DRIVER_IO_PORT))
                client.setblocking(False)
                print('Connected')
                connected = True
            except ConnectionRefusedError:
                time.sleep(1)

        mcu_hv_en = True
        shutdown = False
        show_message = True
        try:
            while True:
                if show_message:
                    print(f'Shutdown faults are turned {"off" if not shutdown else "on"} enter S to turn {"off" if shutdown else "on"}')
                    show_message = False
                console_in, _, _ = select.select([sys.stdin], [], [], 0)
                if console_in:
                    key = sys.stdin.readline()
                    if key.find('s') != -1 or key.find('S') != -1:
                        shutdown = not shutdown
                        show_message = True
                d = gen_data(mcu_hv_en, shutdown)
                d = b'<bsr>' + d + b'</bsr>'
                client.send(d)
                readable, _, _ = select.select([client], [], [], 0.1)
                if readable:
                    data = client.recv(1024)  # Adjust the buffer size accordingly
                    print(data)
                    if data == b'mcu_hv_en':
                        print("Received mcu_hv_en signal")
                        mcu_hv_en = True

        except Exception as e:
            traceback.print_exc()
            print("Disconnected")
        finally:
            client.close()
