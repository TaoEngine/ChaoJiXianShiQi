import wmi
import psutil
import json
import serial
from time import sleep

def get_memory():
    # 系统的内存利用率
    free = round(psutil.virtual_memory().free / (1024.0 * 1024.0 * 1024.0), 2)
    total = round(psutil.virtual_memory().total / (1024.0 * 1024.0 * 1024.0), 2)
    memory_use_percent = psutil.virtual_memory().percent
    result = json.dumps({'mod' : '1', 'mem': memory_use_percent, 'mem_p': str(int(memory_use_percent)) + '%', 'mem_t': str(total) + '(' + str(free) + ')GB'})
    return result

if __name__ == '__main__':
    arduino = serial.Serial(port = 'COM3', baudrate = 115200)
    arduino.write(b'OK')
    sleep(3)
    while True:
        #内存
        for i in range(0,30):
            #print(get_memory().encode())
            arduino.write(get_memory().encode())
            sleep(0.5)

        #cpu
        cpuinfo = wmi.WMI()
        ii = 0
        for cpu in cpuinfo.Win32_Processor():
            cpu_name_full = cpu.Name

        for i in range(0,30):
            cpu_name = cpu_name_full[ii:ii+12]
            ii = ii + 1
            if ii >= 30:
                ii = 0
                sleep(3)
            result_cpu = json.dumps({'mod' : '2', 'cpu_n': cpu_name, 'cpu_u': str(int(psutil.cpu_percent())) + '%', 'cpu_up': psutil.cpu_percent()})
            arduino.write(result_cpu.encode())
            sleep(0.5)