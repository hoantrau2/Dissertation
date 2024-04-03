import socket
import json
import logging

# Tạo một formatter tùy chỉnh
class MyFormatter(logging.Formatter):
    def format(self, record):
        return record.getMessage()

# Cấu hình logging để lưu vào file
logging.basicConfig(filename='client.log', level=logging.INFO)

# Lấy logger của root
logger = logging.getLogger()

# Sử dụng formatter tùy chỉnh
formatter = MyFormatter()
for handler in logger.handlers:
    handler.setFormatter(formatter)

# Hàm chuyển đổi mảng thành một chuỗi
def array_to_string(arr):
    return ','.join(map(str, arr))

# Khởi tạo socket
client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# Kết nối tới server
server_address = ('192.168.66.171', 12346)
client_socket.connect(server_address)

while True:
    # Nhận dữ liệu từ server
    data = client_socket.recv(1024).decode()
    # Kiểm tra nếu không nhận được dữ liệu
    if not data:
        logger.info("Không nhận được dữ liệu từ server. Đóng kết nối.")
        break
    # Phân tích dữ liệu JSON nhận được thành mảng
    data_array = json.loads(data)

    # Ghi mảng dữ liệu vào file log
    logging.info(array_to_string(data_array))

# Đóng kết nối
client_socket.close()
