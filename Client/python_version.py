
import string
import socket
import os
import sys
import signal



class GoldiloxAPIServerInit():
    """Network class for making a Python daemon (if you're into that sort of thing)."""

    def __init__(self, port: int):
        """Create a listening Goldilox server.

        :param: port: The port number to listen on.
        """
        self.sockfd = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.sockfd.bind(('127.0.0.1', port))
        self.sockfd.listen(5)

    def ServerLoop(self) -> None:
        # I don't know what I want to do here.
        pass


class GoldiloxAPIClientConnection():
    """Network class for connecting to the daemon though Python."""

    def __init__(self, host: str, port: int, node_type=None):
        """Initialize the connection.

        :param: host: hostname of the daemon.
        :param: port: The port number of the
            daemon.
        """
        self.sockfd = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.sockfd.connect((host, port))
        if node_type:
            self.sockfd.send(node_type.encode('utf-8'))
        else:
            self.sockfd.send('API\0'.encode('utf-8'))
        progress = self.sockfd.recv(400).decode('utf-8')
        try:
            assert progress.startswith('API_0K')
        except AssertionError:
            print('Error connecting to valid daemon. Closing connection')
            self.sockfd.close()
            sys.exit(1)
        signal.signal(signal.SIGINT, self.signal_catcher)


    def Send(self, buffer: bytearray) -> None:
        """Send data to the daemon network.

        :param: buffer: The buffered data to be sent.
        """
        size = len(buffer)
        print('buffer to be sent is ', buffer)
        self.sending_number_size(size)
        self.buffered_send(buffer, size)



    def assert_buffer_is_file(self, buffer: bytearray) -> bool:
        """Assert whether we're writing a file or not.

        :param: buffer: The bytearray to be checked.
        :return: True if a file is detected in the buffer
            and False if not,
        """
        for index, character in enumerate(buffer):
            if index == 1024:
                break

            if character == '\x44':
                flag_checker = buffer[index: index + 3]
                if flag_checker == '\x44\x33\x22\x11':
                    return True

        return False


    def Recv(self) -> bytearray:
        """Receive data from the daemon network.

        :return: The received payload from the network.
        """
        size = self.receive_number_size()
        content = self.buffered_recv(size)
        if self.assert_buffer_is_file(content) is True:
            print('Receiving file')
            self.RecvFile(content)
        else:
            return content


    def sending_number_size(self, size: int) -> None:
        """Send the incoming buffer size to the network so it can
        prepare itself.

        :param: size: The size of the incoming buffer.
        """
        number = str(size)
        progress_message = str()

        number = number + '\0'
        self.sockfd.send(number.encode('utf-8'))
        progress_message = self.sockfd.recv(4096).decode('utf-8')

        try:
            assert progress_message.startswith('0K')
        except AssertionError:
            print('Synchrnoization error with daemon. Closing connection.')
            self.sockfd.close()
            sys.exit(1)


    def buffered_send(self, buffer: bytearray, size: int) -> None:
        """Send the payload in chunks to the daemon.

        :param: buffer: The bytearray of data to be send to the
            daemon.
        :param: size: The size of the byptearray to be chunked.
        """
        counter = 0
        sent = int()
        chunk = bytearray()
        chunk_counter = 0


        if len(buffer) < 4096:
            self.sockfd.send(buffer.encode('utf-8'))
            return 

        while counter < size:
            chunk = bytearray(buffer[chunk_counter: chunk_counter + 4096], 'utf8')
            #sockfd.send(chunk.encode('utf-8'))
            self.sockfd.send(chunk)
            chunk_counter += 4096
            counter += 4096


    def buffered_recv(self, size: int) -> None:
        """Receive data from the connected daemon.

        :param: size: The size of data to be received.
        """
        counter = 0
        content = str()

        while counter < size:
            chunk = self.sockfd.recv(4096).decode('utf-8')
            content = content + chunk
            if len(chunk) == 4096:
                counter += 4096
            else:
                break

        return content


    @staticmethod
    def refactor_byte_to_int(number_size: int) -> str:
        """Extract the string number value from the buffer.

        :param: number_size: The number to refactor from a
            bytestream into it's string equivalient.
        :return: The number size extracted from the
            bytestream into an int.
        """
        for index, character in enumerate(number_size):
            if character == '\x00':
                return number_size[:index]
        return number_size


    def receive_number_size(self) -> int:
        """Received the total size of the incoming buffer
        to be recieved by the network.
    
        :return: The number of bytes to be received in the
            buffered_recv method.
        """
        number_size = self.sockfd.recv(4096).decode('utf-8')
        number_size = self.refactor_byte_to_int(number_size)
        self.sockfd.send('OK\0'.encode('utf-8'))
        return int(str(number_size))


    def signal_catcher(self, signal: int, frame: int) -> None:
        """Exit gracefully when the app is interrupted.

        :param: signal: Signal number to exit gracefully.
        :param: frame: Frame number to exit gracefully.
        """
        print('Terminating connection...')
        self.Send('RUSSIANGUILOUTINE')
        self.sockfd.close()
        sys.exit(1)

    @staticmethod
    def write_file(filename: str, data: bytes) -> None:
        """Write data to the file.

        :param: filename: The name of the file to be created.
        :param: data: The contents of the file to be  written.
        """
        fd = open(filename)
        fd.write(data)
        fd.close()


    def FileRecv(self, buffer: bytearray) -> None:
        """Unpack and write file.

        :param: buffre: Bytestream containig filename and
            it's contents.
        """
        filename = str()
        file_content = bytearray()
        for index, character in enumerate(buffer):
            if character == '\x44':
                filename = buffer[:index]
                file_content = buffer[index + 4:]
                self.write_file(filename, file_content)
                return

        print('Error: File not found')
        return 


    def FileSender(self, filename: str) -> None:
        """Send a file to a remote node.

        :param: filename: The name of the file to send.
        """
        try:
            file = open(filename, 'rb')
        except FileNotFoundError:
            print('Error: File not found')
            sys.exit(1)

        file_stats = os.stat(filename)
        file_size = file_stats.st_size
        file_content = file.read()
        file.close()

        buffer = bytes(filename) + '\x44\x33\x22\x11' + bytes(file_content)
        buffer_size = len(filename) + 4 + file_size

        sockfd.send(buffer_size.encode('utf-8'))
        progress = sockfd.recv(400)
        
        self.buffered_send(buffer, buffer_size)
