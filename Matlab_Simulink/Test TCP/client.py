import socket
import logging

# Thiết lập cấu hình logging
logging.basicConfig(filename='client.log', level=logging.INFO, format='%(message)s')

# Hàm kiểm tra xem một chuỗi có phải là số không
def is_number(s):
    try:
        float(s)
        return True
    except ValueError:
        return False

# Khởi tạo socket
client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# Kết nối tới server
server_address = ('192.168.66.171', 12345)
client_socket.connect(server_address)

# Nhận dữ liệu từ server và chuyển đổi thành số float
while True:
    data = client_socket.recv(1024).decode()
    if not data:
        break
    numbers = data.split(',')
    for number in numbers:
        if number.strip() and is_number(number.strip()):
            float_number = float(number)
            print("Dữ liệu nhận từ server:", float_number)
            # Ghi giá trị float_number vào log file
            logging.info('%f', float_number)

# Đóng kết nối
client_socket.close()
