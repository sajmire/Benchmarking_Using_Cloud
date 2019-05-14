#http://www.bogotobogo.com/python/python_network_programming_server_client_file_transfer.php

import socket               # Import socket module
from threading import Thread
import time

size = 64*1024
tot_size = 1000000000
serverIPAddress = '192.168.0.11'

class ThreadedClient(Thread):

    def __init__(self,ip,port,sock,name):
        Thread.__init__(self)
        self.ip = ip
        self.port = port
        self.sock = sock
        self.name = name

    def run(self):
        #start_time = time.time()
	global run_size
        run_size = 0
        totalElapsedTime, throughput, latency = 0, 0 ,0
        with open('received_file.txt', 'wb') as handle:
            #print('file opened')
            #print('receiving data...')
            i=0
            while True:
                data,addr = self.sock.recvfrom(size)
                print('data= ', i, len(data))
                #print(data)
                i+=1
		global run_size
                run_size+=len(data)
                if run_size >=tot_size:
                    print("break")
                    break
                handle.write(data)
        #handle.close()
            print('Successfully got the file')
            #self.sock.close()


def main():
    # Create a socket object
    clientSoc = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    # Get local machine name
    clientHost = serverIPAddress
    # Reserve a port for your service.
    clientPort = 41005

    clientSoc.bind((clientHost, clientPort))
    thread_range = [1,2,4,8]

    #while True:
    start_time = time.time()
    for no_of_threads in thread_range:
        thread_pool = []
        for i in range(no_of_threads):
            thread = ThreadedClient(clientHost, clientPort, clientSoc, i)
            thread.start()
            thread_pool.append(thread)
        print("-------------------------------")


        for th in thread_pool:
            th.join()

        end_time = time.time()
        totalElapsedTime = (end_time - start_time)
        throughput = (tot_size/totalElapsedTime)/1000000

        #(2*(tot_size/(1024.0*1024.0)))/(((totalElapsedTime)))
        latency = (size*totalElapsedTime*100)/tot_size


        print("Total: ",totalElapsedTime,"Throughput: ",throughput,"Latency: ",latency)
    #clientSoc.close()
    print('connection closed')



if __name__ == '__main__':
    main()
