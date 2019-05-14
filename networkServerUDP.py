#!/usr/bin/python
#http://www.bogotobogo.com/python/python_network_programming_server_client_file_transfer.php

import socket
from threading import Thread
import time

size = 64*1000
clientIPAddress = '192.168.0.11'

class ThreadedClient(Thread):

    def __init__(self,ip,port,sock, name="th"):
        Thread.__init__(self)
        self.ip = ip
        self.port = port
        self.sock = sock
        self.name = name

    def run(self):
        #filename = "D:\\MS\\Course\\CS553-CC\\Assignment1\\Trial1.txt"
        filename = "Trial1.txt"

        handle = open(filename,'rb')
        while True:
            filedata = handle.read(size)
            while (filedata):
                print(len(filedata))
                self.sock.sendto(filedata,(self.ip,self.port))
                #print("sent:",repr(filedata))
                filedata = handle.read(size)
            if not filedata:
                handle.close()
                #self.sock.close()
                break



def main():
    # Socket programming for connection
    clientSoc = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

    clientHost = clientIPAddress
    #print(serverHost)
    clientPort = 41005
    #clientSoc.bind((clientHost,clientPort))

    thread_range = [1,2,4,8]


    print ('Server listening....')


    while True:
        #serverSoc.listen(8)

        # Establish connection with client.
        #(clientSoc, (clientIP, clientPort)) = serverSoc.accept()
        print ('Got connection from', clientHost, )
        for no_of_threads in thread_range:
            thread_pool = []
            for _ in range(no_of_threads):
                thread = ThreadedClient(clientHost, clientPort, clientSoc)
                thread.start()
                time.sleep(1)
                thread_pool.append(thread)


            for th in thread_pool:
                th.join()


        #clientSoc.close()
        print('Done sending')



if __name__ == '__main__':
    main()
