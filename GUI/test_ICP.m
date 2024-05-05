% Thi?t l?p k?t n?i TCP/IP t?i m�y ch? (Jetson)
t = tcpip('192.168.1.100', 8888);  % Thay ??i ??a ch? IP v� c?ng t??ng ?ng v?i Jetson

% M? k?t n?i
fopen(t);
disp('Connected to Jetson server.');

% G?i d? li?u ??n m�y ch?
dataToSend = 'Hello from MATLAB!';
fwrite(t, dataToSend);

% Nh?n ph?n h?i t? m�y ch?
dataReceived = fread(t, t.BytesAvailable);
disp(['Received response from Jetson: ', char(dataReceived')]);

% ?�ng k?t n?i
fclose(t);
delete(t);
