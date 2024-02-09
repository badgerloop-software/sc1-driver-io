import json
import random
import socket
import string
import struct
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

def gen_data():
    global gps_data_index
    data = []
    for key in data_format.keys():
        d = data_format[key]
        t = time.gmtime()
        match d[1]:
            case 'bool':
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
        client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        try:
            client.connect((DRIVER_IO_IP, DRIVER_IO_PORT))
            print('connected')
        except ConnectionRefusedError:
            continue
        try:
            while True:
                d = gen_data()
                d = b'<bsr>' + d + b'</bsr>'
                client.send(d)
                time.sleep(0.1)
        except Exception as e:
            traceback.print_exc()
            print("disconnected")
            continue
